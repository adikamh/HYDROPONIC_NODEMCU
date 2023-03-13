void TDS(){
  // TDS
    pinMode(TempProbeNegative, OUTPUT);        // mengatur pin ground sebagai output untuk probe tmp
    digitalWrite(TempProbeNegative, LOW);      // Mengaturnya ke ground sehingga dapat meneggelamkan arus
    pinMode(TempProbePossitive, OUTPUT);       // Vin hasil
    digitalWrite(TempProbePossitive, HIGH);    // Vin mengatur sehingga dapat meneggelamkan arus
    
    pinMode(ECPin, INPUT);          // ECPin untuk sumber arus 
    pinMode(ECPower, OUTPUT);       // ECPower untuk tenggelam saat ini
    pinMode(ECGround, OUTPUT);      // ECGround nilai ground hasil
    digitalWrite(ECGround, LOW);    // ECGround terhubung secara permanen

    delay(100);   // waktu eksekusi program
    RD = (RD+Ra); //Menambahkan Resistensi Pin Digital ke [25 ohm] ke Resistor statis

    Serial.println("Pengukuran pada interval 5 Detik [Jangan baca Ec lebih dari sekali setiap 5 detik]: ");
  };

void handleTotalDisolve(){

   // TDS
  digitalWrite(ECPower, HIGH); // ECPower sktiv /  nyala
  raw = analogRead(ECPin);     // membaca Pin
  raw = analogRead(ECPin);     //    "" 
  digitalWrite(ECPower, LOW);  // ECPower mati 

 // ekselusi Rumus 
  Vdrop = (Vin*raw)/1024.0;
  Rc = (Vdrop*RD)/(Vin-Vdrop);
  Rc = Rc- Ra; 
  EC = -4/(Rc*K);
  EC25 = EC/ (1+ TemperatureCoef*(Tc-25.0));
  ppm = (EC25)*(PPMconversion*1000);
  
  
String TDS_Value = String(ppm);
server.send(200, "text/plane", TDS_Value);
   delay(2000);

      if(ppm > 2000){
        digitalWrite(relay, OFF);
      }
;}
