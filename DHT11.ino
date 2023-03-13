void handleDHT11(){
  
 SUHU = dht.readTemperature();  // Membaca Sensor Suhu
 KELM = dht.readHumidity();     // Membaca Sensor Kelembaban

// Mengubah float Menjadi String
String T_Value = String(SUHU);  
String K_Value = String(KELM);

//-----Mengirimkan Pesan berupa nilai sensor ke MQTT
server.send(200, "text/plane", T_Value);
server.send(200, "text/plane", K_Value);

  delay(2000);
}
