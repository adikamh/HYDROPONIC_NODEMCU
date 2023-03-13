void changeTime(){
  
  Hour1 = JAM.getHours();   // Memanggil Nilai jam 
  Min = JAM.getMinutes();   // Memanggil Nilai Menit

//-----Mengubah Jam dan menit menjadi satu nilai
  Waktu = Hour1 * 10000 + Min * 100;
  Nyala = jam_nyala * 10000 + menit_nyala * 100;
  Mati = jam_mati * 10000 + menit_mati * 100;
delay(1000);

//-----Logika Jadwal
if (jam_nyala == jam_mati && menit_nyala == menit_mati) {
    digitalWrite(relay, ON);
    Serial.println("Input nilai tidak sesuai!!");
}

  if (Nyala < Mati) {

    if (Waktu >= Nyala && Waktu < Mati) { //Start
      digitalWrite(relay, OFF);
      Serial.println("Pompa nyala");
      isHandleToggleRunning = false;
}
    else if (Waktu >= Mati) {
      digitalWrite(relay, ON);
      Serial.println("Pompa mati");
      isHandleToggleRunning = true;
}
    else {
      digitalWrite(relay, ON);
      
  }
}
  
  if (Nyala > Mati) {
    if (Waktu >= Nyala && Waktu >= 2359) {   //Start
      digitalWrite(relay, OFF);
}
    else if (Waktu < Mati ) {
      digitalWrite(relay, OFF);
}
    else if (Waktu >= Mati && Waktu < Nyala) {
      digitalWrite(relay, ON);
  }
}
  if (statusRelay ==  ON){
    EEPROM.write(4, statusRelay);
    EEPROM.commit();
  }
  else if(statusRelay == OFF){
    EEPROM.write(4, statusRelay);
    EEPROM.commit();
}
if(relay == OFF){
  isHandleToggleRunning = true;
  }
}
