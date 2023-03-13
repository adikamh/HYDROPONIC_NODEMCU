void handleToggle() {
  isHandleToggleRunning = true;       // Logika agar Tombol dan jadwal tidak terjadi BUG
  String state = server.arg("state"); // Parameter Untuk emmanggil fungsi dari html

//-----Logika Toggle / tombol ON,OFF website
 if(state == "on"){
    digitalWrite(relay, OFF);
        Serial.println("Pompa nyala");
        delay(1000);
  }
  else if (state == "off"){
    digitalWrite(relay, ON);
    isHandleToggleRunning = false;
        Serial.println("Pompa mati");
        delay(1000);
  }else{
    digitalWrite(relay, OFF);
    delay(1000);
  }
if(state == "off"){
  isHandleToggleRunning = false;
}
}
