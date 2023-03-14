void TampilanLCD(){

//-----Tampilan LCD IP WEB.LOCAL
lcd.clear();
lcd.setCursor(0,0);
lcd.print("WEB:");
lcd.print(WiFi.localIP());

//-----Tampilan LCD StatusPompa ON/OFF
  if(digitalRead(relay)== ON){
    lcd.setCursor(0,1);
    lcd.print("Status Pompa:OFF");
  }else if(digitalRead(relay)==OFF){
    lcd.setCursor(0,1);
    lcd.print("Status Pompa: ON");
  }delay(5000);

//-----Tampilan LCD jadwal pompa nyala dan mati
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Pompa ON : ");
lcd.print(jam_nyala);
lcd.print(":");
lcd.print(menit_nyala);
lcd.setCursor(0,1);
lcd.print("Pompa OFF: ");
lcd.print(jam_mati);
lcd.print(":");
lcd.print(menit_mati);
    delay(5000);
    
//-----Tampilan LCD DHT11
lcd.clear();
if (isnan(KELM) || isnan(SUHU)){
  lcd.setCursor(1,0);
  lcd.print("Kode/Rangkaian");
  lcd.setCursor(1,1);
  lcd.print("sensor salah!!");
  return;
}else{
lcd.setCursor(0,0);
lcd.print("Suhu     :");
lcd.print(SUHU);
lcd.print("C");
lcd.setCursor(0,1);
lcd.print("Humiditas:");
lcd.print(KELM);
lcd.print("%");
    delay(5000);
}

//-----Tampilan LCD NTC3950/Sensor suhu air
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Suhuair: ");
lcd.print(Tc);
lcd.print("C");
lcd.setCursor(0,1);
lcd.print("PPM    : ");
lcd.print(ppm);
lcd.print("%");
    delay(5000);

//-----Tampilan LCD JAM      
lcd.clear();
lcd.setCursor(2,0);
lcd.print("Jam Sekarang");
lcd.setCursor(5,1);
lcd.print(Hour1);
lcd.print(":");
lcd.print(Min);
    delay(1000);
}
