void PUBLISH(){

//-----Mengirimkan Nilai Ke MQTT Server
unsigned long currentMillis = millis();
unsigned long fiveMinutes = 5 * 60 * 1000;
static unsigned long lastPublishMillis = 0;
if (currentMillis - lastPublishMillis >= fiveMinutes) {
client.publish(DK_topic,"pwwyo");
client.publish(T_topic, String(SUHU).c_str(), true);  // Nilai Sensot suhu
client.publish(TDS_topic, String(ppm).c_str(), true); // Nilai PPM
client.publish(TA_topic, String(Tc).c_str(), true);   // Nilai Suhu air
lastPublishMillis = currentMillis;
  } else {
    delay(2000);
  }
}
