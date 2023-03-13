void handleNTC3950(){

//-----Rumus NTC3950
  Vo = analogRead(Thermistor);
  R2 = R1 * (1023.0/(float)Vo - 1.0);
  logR2 = log(R2);
  T = (15.0/(cl + c2*logR2 + c3*logR2*logR2*logR2));
  Tc= T/240.15;
  //Tc = T/210.15;

  String SH_Value = String(Tc);

//-----Mengirimkan Nilai Sensor beruba Pesan
  server.send(200, "text/plane", SH_Value);
    delay(2000);

    if (Tc < 12.00){
      digitalWrite(relay, OFF); 
    }else if(Tc > 25.00){
      digitalWrite(relay, OFF);
    }
    
}
