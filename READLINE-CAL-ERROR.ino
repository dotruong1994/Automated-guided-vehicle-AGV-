void readSensors()
{
  for (int pin = 0; pin < 8; pin++) 
  {
    int pinNum = Sensors[pin];
    ir[pin] = digitalRead(pinNum);
  }
}
  
  

  //bumper_hdw.read();
  //reset_hdw.read();
  void EMO()
  {
    bool emoValue = digitalRead(emo_hdw);
    if(emoValue==0)
        { 
          Stop_EMO();
        }}
    
    // if(Serial3.available()>0)
    //   {  
          // Serial.println("có available");
          // dulieu = Serial3.readString();
          // if (strcmp(dulieu.c_str(), "turnLeft") == 0) {    
          //     //turn left vào đây
          //     Serial.println("read xong turnleft rồi!");
          //        _turnLeft_();

          //   }
          // if (strcmp(dulieu.c_str(), "turnRight") == 0) {       
          //     //turn right vào đây
          //      Serial.println("read xong turnright rồi!");
          //         run_extra_cross();
          //         _turnRight_();
          //   }
          // if (strcmp(dulieu.c_str(), "stop") == 0) {    

          //     //stop vào đây
          //      Serial.println("read xong stop rồi!");
          //      Stop_station();
          //   }  
          // if (strcmp(dulieu.c_str(), "way1") == 0) {    
          //     //turn left vào đây
          //     Serial.println("read xong chạy way1 rồi ở readsensor!");
          //        value_way = 1;
          //        giatoc();

          //   }
          // if (strcmp(dulieu.c_str(), "way2") == 0) {    
          //     //turn left vào đây
          //     Serial.println("read xong chạy way2 rồi ở readsensor!");
          //       value_way = 2;
          //       giatoc();
          //   } 
          // if (strcmp(dulieu.c_str(), "wifi_disconnect") == 0) {    
          //    Serial.println("Mất mọe wifi rồi");
          //    LCD_wifi_disconnect();
          //   }       
      // }

//     if(bumper_hdw.isPressed())
//        { 
//          Stop_bumper();
//        }   

// ĐANG LỖI VCC CHÁN VL
// void read_RFID(){
//     if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
//     Serial.print("UID tag :");
//     for (byte i = 0; i < rfid.uid.size; i++) {
//       Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
//       Serial.print(rfid.uid.uidByte[i], HEX);
//     }
//     Serial.println();
//     rfid.PICC_HaltA();
//     rfid.PCD_StopCrypto1();
//   }
// }


void calculateError() 
{
  //Determine an error based on the readings
  if      ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0) && (ir[7] == 1)) {mode = FOLLOWING_LINE;error = 14;} 
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 1) && (ir[7] == 1)) {mode = FOLLOWING_LINE;error = 12;}  // lech trai   
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 1) && (ir[6] == 1) && (ir[7] == 1)) {mode = FOLLOWING_LINE;error = 10;}  // lech trai         
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 1) && (ir[7] == 0)) {mode = FOLLOWING_LINE;error = 8;}  // lech tra
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 1) && (ir[6] == 1) && (ir[7] == 0)) {mode = FOLLOWING_LINE;error = 6;}  // lech tra
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 1) && (ir[5] == 1) && (ir[6] == 1)) {mode = FOLLOWING_LINE;error = 3;} // lech trai
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 1) && (ir[6] == 1)) {mode = FOLLOWING_LINE;error = 3;} // lech trai
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 1) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 3;} // lech trai
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 1) && (ir[5] == 1) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 2;} // lech trai
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 1) && (ir[4] == 1) && (ir[5] == 1) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 1;} // lech trai
  //else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 1) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 1;}

  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 1) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 0;}// khong lech
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 1) && (ir[4] == 1) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 0;}// khong lech
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 1) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 0;}// khong lech
  
  //else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 1) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -1;}// lech phai
  else if ((ir[1] == 0) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 1) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -1;}// lech phai
  
  else if ((ir[1] == 0) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -2;}// lech phai
  
  else if ((ir[1] == 0) && (ir[2] == 1) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -3;}
  else if ((ir[1] == 0) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -3;}// lech phai
  else if ((ir[1] == 1) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -3;}// lech phai
  
  else if ((ir[0] == 0) && (ir[1] == 1) && (ir[2] == 1) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -6;}// lech phai

  else if ((ir[0] == 0) && (ir[1] == 1) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -8;}// lech phai
  else if ((ir[0] == 1) && (ir[1] == 1) && (ir[2] == 1) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -10;}// lech phai 
  else if ((ir[0] == 1) && (ir[1] == 1) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -12;}// lech phai
  
  else if ((ir[0] == 1) && (ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -14;}
  //else if ((ir[0] == 1) && ((ir[1] == 1) && (ir[2] == 1)) && ((ir[3] == 1) && (ir[4] == 1)) && ((ir[5] == 1) && (ir[6] == 1)) && (ir[7] == 1)){Serial.println("hết");}
  else if(((ir[0] == 1) && ((ir[1] == 1) && (ir[2] == 1)) && ((ir[3] == 1) && (ir[4] == 1)) && ((ir[5] == 1) && (ir[6] == 1)) && (ir[7] == 1)))
  { 
    Serial.println("vào mode Station lần 1");
    readSensors();
    EMO();
    if   (((ir[0] == 1) && ((ir[1] == 1) && (ir[2] == 1)) && ((ir[3] == 1) && (ir[4] == 1)) && ((ir[5] == 1) && (ir[6] == 1)) && (ir[7] == 1)))
    {
      mode = STATION;error = 0;
      Serial.println("vào mode Station lần 2");
    }
  }
  else if ((ir[0] == 0) && (ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0) && (ir[7] == 0)) 
          {mode = NO_LINE;error = 0;led_noline();digitalWrite(out_line, HIGH);}// stop
 // else {mode = NO_LINE;error = 0;led_noline();}  // vẫn đang cân nhắc
  //TURN_AROUND
//  else if ((ir[1] == 1) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 1) && (ir[5] == 1) && (ir[6] == 1)) {mode = TURN_AROUND;error = 0;}
  //Slow down the speed

  // else if ((ir[0] == 1) && (ir[1] == 1) && (ir[2] == 1)&& (ir[3] == 1)&& (ir[4] == 1) && (ir[6] == 0) && (ir[7] == 0)) {mode = TURN_LEFT;error = 0;} // dán bên trái để giảm tốc
  
  // else if ((ir[4] == 1) && (ir[5] == 1) && (ir[6] == 1) && (ir[7] == 1) && (ir[0] == 0) && (ir[1] == 0)) {mode = TURN_RIGHT;error = 0;}
} 
