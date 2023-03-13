void reconnect (){

  while(!client.connected()){
    
    Serial.println("Menghubungkan ke mqtt..");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("                    ");
    lcd.setCursor(3,0);
    lcd.print("Hub MQTT..");
    digitalWrite(LEDMQTT, HIGH);
    delay(500);
    digitalWrite(LEDMQTT, LOW);
    delay(500);
    
  String clientq;
  clientq += "ADIKA-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientq += macToStr(mac);
  clientq += "-";
  clientq += String(micros() & 0xff, 16);
  Serial.print("Menghubungkan ke: ");
  Serial.print(mqtt_server);
  Serial.print(" dan ");
  Serial.print(clientq);

  if(client.connect((char*) clientq.c_str())){
   Serial.println("Terhubung");
   lcd.setCursor(3,1);
   lcd.print("Terhubung");
   digitalWrite(LEDMQTT, HIGH);
   client.subscribe("/jadwal");
   PUBLISH();
  }else{
    Serial.println("");
    Serial.print("gagal terhubung, Mengulang");
    digitalWrite(LEDMQTT, HIGH);
    delay(500);
    digitalWrite(LEDMQTT, HIGH);
    delay(500);
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("Gagal MQTT");
    Serial.print(client.state());
    Serial.println("Mengulang 5 detik");
    delay(5000);
  
    
  }
  
  }
}
