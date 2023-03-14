/*PROJECT APLIKASI PERANGKAT HYDROPONIK BERBASIS MQTT
 * OLEH ADIKA MUHAMMAD HAIKAL KELAS XII TKJ 1
 * SMK NEGERI 13 BANDUNG
 */


//-----Library
#include <DHT.h>               // library DHT11
#include <ESP8266WiFi.h>       // library ESP8266WiFI
#include <PubSubClient.h>      // library MQTT
#include <NTPClient.h>         // library untuk Tanggal dan jam pada ESP8266
#include <WiFiUdp.h>           // Library esp8266 terhubung server waktu
#include <LiquidCrystal_I2C.h> // Library untuk LCD 16x2 I2c
#include <ESP8266WebServer.h>  // Library untuk webserver arduino
#include <WiFiClient.h>        // Client WiFi
#include <EEPROM.h>            // Memory
#include "PageIndex.h"         // HTML untuk struktur web

//-----WIFI
#define ssid "AP-RASTEK-RND"    //SSID WiFi yang akan terhubung
#define pass "admin125"         //PASSWORD WiFi yang akan terhubung

//-----MQTT
#define mqtt_server "broker.emqx.io"   //Server MQTT
#define mqtt_user "APHBM123"           // id untuk server
#define mqtt_password "ADMIN123"       // password untuk server

//-----topic  MQTT
#define T_topic  "/suhuLingkungan"  // topic mqtt sensor DHT11
#define SC_topic "/jadwal"          // topic schedule pompa
#define ID_topic "/id"              // topic ID perangkat
#define TA_topic "/suhuAir"         // topic Thermistor sensor suhu air
#define TDS_topic "/tds"            // topic Sensor TDS
#define DK_topic "/deviceKey"       // topic Device key

//-----Sensor DHT, Relay, ON,OFF,LeadBoard
#define DHTPIN D3         // PIN digital untuk Sensor suhu sekitar
#define DHTTYPE DHT11     // definisikan tipe Sensor DHT = DHT11
#define LEDWiFi D6        // PIN digital untuk LEDWIFI ketika terkoneksi
#define LEDMQTT D7        // PIN digital untuk LEDMQTT ketika terhubung
#define relay D0          // PIN digital Relay
#define ON HIGH           // definisikan HIGH sebagai ON
#define OFF LOW           // definisikan LOW sebagai OFF

//-----Variable Object
IPAddress ip(192,168,30,1);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

DHT dht(DHTPIN, DHTTYPE);            
WiFiClient espClient;                
PubSubClient client(espClient);
WiFiUDP ntp;
NTPClient JAM(ntp, "pool.ntp.org");
ESP8266WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//-----NTC3950
int Thermistor = A0;
int Vo;
float logR2, R2, T, Tc, Tf;
float R1 = 10000;
float cl = 1.0092495522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//-----TDS
int RD = 1000;                       // Resistor dengan resistansi 1k Ω
int Ra = D4;                         // Resistansi dari power pin 
int ECPin = D5;                      // Pin yang digunakan untuk Data
int ECGround =0;                     // Pin ground -
int ECPower = 0;                     // pin Vin +
float PPMconversion = 0.7;           // Nilai konversi PPM air
float TemperatureCoef = 0.019;       // Nilai koefisien standar suhu
float K = 2.88;                      // Nilai Konstan Untuk Pengukuran Ec
const int TempProbePossitive = 0;    // Pin Gournd
const int TempProbeNegative = 0;     // Pin Vin

float Temperature = D5;    // Pin Temperature  yaitu GPIO
float EC = 0;              // Pengukuran EC
float EC25 = 0;            // EC ekuivalen pada 25°C
int ppm = 0;               // deklarasi ppm
float raw = 0;             
float Vin = 5;
float Vdrop = 0;
float Rc = 0;
float buffer = 0;

//-----DHT
float SUHU;
float KELM;

//-----Jadwal
int jam_nyala;
int menit_nyala;
int jam_mati;
int menit_mati;

unsigned long Waktu;
unsigned long Hour1;
unsigned long Min;
unsigned long Nyala;
unsigned long Mati;

bool statusRelay = true;              
bool isHandleToggleRunning = false;

//-----Memanggil Data mqtt
void callback(char* topic, byte* payload, unsigned int length) { 
  String schedule 
  = "";
  isHandleToggleRunning = false;
  for (unsigned int i=0; i< length; i++) {
    schedule = schedule + (char)payload[i];
  }

  //----- memisahkan nilai jadwal on dengan off
    String subValN = getValue(schedule, ',',0);
    String subValF= getValue(schedule, ',',1);
    
    String subDelON = subValN.substring(2,7);
    String subDelOFF= subValF.substring(1,6);

    String subValONjam   = getValue(subDelON, ':',0);
    String subValONmenit = getValue(subDelON, ':',1);
    String subValOFFjam   = getValue(subDelOFF, ':',0);
    String subValOFFmenit = getValue(subDelOFF, ':',1);
    
    int jam_nyala = subValONjam.toInt();
      int menit_nyala = subValONmenit.toInt();
        int jam_mati = subValOFFjam.toInt();
          int menit_mati= subValOFFmenit.toInt();

//-----menyimpan nilai ON dan OFF pada EEPROM NodeMcu
  EEPROM.write(0, jam_nyala);
  EEPROM.write(1, menit_nyala);
  EEPROM.write(2, jam_mati);
  EEPROM.write(3, menit_mati);
  EEPROM.commit();

//-----Menampilkan nilai ON dan OFF di Serial
    Serial.print("Jam ON: ");
   Serial.println(jam_nyala);
   Serial.print("Menit ON: ");
   Serial.println(menit_nyala);
   
   Serial.print("Jam OFF: ");
   Serial.println(jam_mati);
   Serial.print("Menit OFF: ");
   Serial.println(menit_mati);

  }

void handleRoot(){
  String html = MAIN_page;
  server.send(200, "text/html", html);
}

  void setup(){
Serial.begin(115200);
EEPROM.begin(512);
dht.begin();
client.setServer(mqtt_server, 1883);
client.setCallback(callback);
pinMode(LEDWiFi, OUTPUT);
pinMode(LEDMQTT, OUTPUT);
pinMode(relay, OUTPUT);
lcd.begin();

//------WIFI
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    for (int i = 10; i < 16; i++) {
      digitalWrite(LEDWiFi, HIGH);
      delay(500);
      digitalWrite(LEDWiFi, LOW);
    delay(500);
    Serial.print(".");
    
      Serial.print(".");
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Menghubungkan");
      lcd.setCursor(6,1);
      lcd.print("WiFi");
      delay(1000);
    }
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Terhubung");
    lcd.setCursor(0,1);
    lcd.print(ssid);
    delay(2000);
    digitalWrite(LEDWiFi, HIGH);
  }
 
//-----mengirim pesan ke html
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/readT", handleDHT11);
  server.on("/readK", handleDHT11);
  server.on("/readSH", handleNTC3950);
  server.on("/readTDS", handleTotalDisolve);
  server.begin();
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Web Internal");
  lcd.setCursor(4,1);
  lcd.print("Aktif!!");
  delay(2000);

//-----Memulai server Jam
JAM.begin();
JAM.setTimeOffset(25200); // Server Waktu Indonesia GMT 7
TDS();    // memanggil Fungsi TDS
  
}

String macToStr(const uint8_t* mac) {
  String result;
  for (int i = 0; i<6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
    result += ':';
    
  }
  return result;
  
}

void loop(){
   if (!client.connected()){ // Jika Koneksi Mqtt terputus maka akan Memanggil funsi reconnect kembali
    reconnect();
    }
    lcd.backlight();         // Menyalakan Backligth pada lCD
    client.loop();           // Mengulang Permintaan pesan dari MQTT
    get_jadwal();            // Memanggil Fungsi get_jadwal
    JAM.update();            // Memanggil Server jam agar jam berjalan sesuai waktu
    server.handleClient();   // mengatur request client yang terhubung ke WEBINTERNAL
     if (isHandleToggleRunning == false) {
    changeTime();
  }                          // Logika untuk TOmbol web dengan jadwal tidak nge bug
TampilanLCD();               // Memanggil Fungsi LCD
handleTotalDisolve();        // Memanggil Fungsi handleTotalDisolve
handleNTC3950();             // Memanggil Funsi handleNTC3950 / Thermistor
handleDHT11();               // Memanggil Fungsi handleDHT11

}

//-----mengubah mac IP address menjadi String
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  } 
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
