void get_jadwal(){

//-----Menyimpan Nilai Jam dan menit kedalam EEPROM  
   jam_nyala = EEPROM.read(0);
  if (jam_nyala > 23) jam_nyala = 0;
  menit_nyala = EEPROM.read(1);
  if (menit_nyala > 59) menit_nyala = 0;
  jam_mati = EEPROM.read(2);
  if (jam_mati > 23) jam_mati = 0;
  menit_mati = EEPROM.read(3);
  if (menit_mati > 59) menit_mati = 0;
  statusRelay = EEPROM.read(4);
  EEPROM.commit();

}
