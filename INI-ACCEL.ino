void khoidong() {
  Serial.println("let's go");
  Serial3.begin(115200);
  Serial3.print("mega_connected");
  Serial3.print("\n");
  Serial3.print("clear");
  Serial3.print("\n");
  Serial3.print("standby");
  while (1) {
    motorStop();
    readSensors();
    EMO();
    bool startValue = digitalRead(start_hdw);
    calculateError();
    //bluetooth();
    if (mode != NO_LINE) {
      led_start();
      if (Serial3.available() > 0) {
        dulieu = Serial3.readString();
        if (strcmp(dulieu.c_str(), "way1") == 0) {
          Serial.println("read xong chạy way1 rồi!");
          value_way = 1;
          Serial3.print("running");
          giatoc();
          break;
        }
        if (strcmp(dulieu.c_str(), "way2") == 0) {
          Serial.println("read xong chạy way2 rồi!");
          value_way = 2;
          Serial3.print("running");
          giatoc();
          break;
        }
      }
      
      if (startValue == 0) {
        if (value_way != 0)
        {
          giatoc();
          break;
        }
      }

      if(digitalRead(function_3) == 0)
      {
        giatoc();
        break;
      }

      if (check == 0) {
        if (digitalRead(function_1) == 0 || digitalRead(function_2) == 0) {
          delay_time = millis();
          check = 1;
        }
      }

      if (check == 1)
      {
        if (millis() - delay_time > 2000)
        {
          if (digitalRead(function_1) == 0)
          {
            Serial3.print("function_1");
            Serial3.print("\n");
            Serial3.print("running");
            value_way = 1;
            giatoc();
            check = 0;
            break;
          }

          if (digitalRead(function_2) == 0)
          {
            Serial3.print("function_2");
            Serial3.print("\n");
            Serial3.print("running");
            value_way = 2;
            giatoc();
            check = 0;
            break;
          }

        }
      }
    }
  }
}

void giatoc() {
  Serial3.print("\n");
  Serial3.print("start");
  Serial3.print("\n");
  chaythang();
  int i = 0;
  while (i <= minimumspeed_giatoc) {
    led_fade();
    readSensors();
    EMO();
    calculateError();
    read_safety_Sensors();
    safety_status_check();

    if (mode == NO_LINE) {
      break;
    }
    if (mode == MOTOR_WAITING) {
      motor_Wait();
      break;
    }
    if (mode == STATION) {
      run_extra_gia_toc();
      giatoc_station();
      break;
    }
    if (millis() >= previousMillis) {
      motor2Speed = i;  //-15;
      motor1Speed = i;  //-15;
      i++;
      previousMillis = millis() + 20;
    }
    pidCalculations();
    changeMotorSpeed();
    //      emo_hdw.read();
    //      if(emo_hdw.wasPressed())
    //        {
    //          Stop_EMO();
    //        }
    //      bumper_hdw.read();
    //      if(bumper_hdw.wasPressed())
    //        {
    //          Stop_bumper();
    //        }
  }
}

void giatoc_station() {
  chaythang();
  int i = 20;
  while (i <= minimumspeed_giatoc) {
    led_fade();
    readSensors();
    EMO();
    calculateError();
    read_safety_Sensors();
    safety_status_check();
    if (mode == NO_LINE) {
      break;
    }
    if (mode == MOTOR_WAITING) {
      motor_Wait();
      break;
    }
    if (mode == STATION) {
      Stop_station();
      break;
    }
    if (millis() >= previousMillis) {
      motor2Speed = i;  //-15;
      motor1Speed = i;  //-15;
      i++;
      previousMillis = millis() + 10;
    }
    pidCalculations();
    changeMotorSpeed();
    //      emo_hdw.read();
    //      if(emo_hdw.wasPressed())
    //        {
    //          Stop_EMO();
    //        }
    //      bumper_hdw.read();
    //      if(bumper_hdw.wasPressed())
    //        {
    //          Stop_bumper();
    //        }
  }
}



void giatoc_safety() {
  chaythang();
  int i = 20;
  while (i <= minimumspeed_giatoc_safety) {
    led_fade();
    readSensors();
    EMO();
    calculateError();
    if (mode == NO_LINE) {
      break;
    }
    if (millis() >= previousMillis) {
      motor2Speed = i;  //-15;
      motor1Speed = i;  //-15;
      i++;
      previousMillis = millis() + 100;
    }
    pidCalculations();
    changeMotorSpeed();
  }
}

void giatocTurn() {
  chaythang();
  int i = 0;
  while (i <= minimumspeed_giatoc) {
    led_fade();
    readSensors();
    EMO();
    calculateError();
    read_safety_Sensors();
    safety_status_check();
    if (mode == NO_LINE) {
      break;
    }
    if (mode == MOTOR_WAITING) {
      motor_Wait();
      break;
    }
    if (mode == STATION) {
      run_extra_gia_toc();
      giatoc_station();
      break;
    }
    if (millis() >= previousMillis) {
      motor2Speed = i;  //-15;
      motor1Speed = i;  //-15;
      i++;
      previousMillis = millis() + 100;
    }
    pidCalculations();
    changeMotorSpeed();
    //      emo_hdw.read();
    //      if(emo_hdw.wasPressed())
    //        {
    //          Stop_EMO();
    //        }
    //      bumper_hdw.read();
    //      if(bumper_hdw.wasPressed())
    //        {
    //          Stop_bumper();
    //        }
  }
}





void giamtoc() {
  chaythang();
  int i = 1;
  while (i <= 120) {
    led_fade();
    readSensors();
    EMO();
    calculateError();
    if (mode == NO_LINE) {
      break;
    }
    if (millis() >= previousMillis) {
      motor2Speed = minimumspeed_giatoc - i;  //-15;
      motor1Speed = minimumspeed_giatoc - i;  //-15;
      i++;
      previousMillis = millis() + 50;
    }
    pidCalculations();
    changeMotorSpeed();
  }
}

// void checkWIFI(){
//   Serial.println("Chờ wifi kết nối");
//   led_wifi_start();
//   while(1)
//   {
//     if(Serial3.available()>0)
//       {
//         Serial.println("wait");
//         dulieu = Serial3.readString();
//         if (strcmp(dulieu.c_str(), "connected") == 0) {
//             Serial.println("Có wifi rồi nha!");

//             break;
//           }
//       }
//   }
// }


void checkWIFI() {
  while (1) {
    if (Serial3.available() > 0) {
      dulieu = Serial3.readString();
      String c = "connected";
      if (dulieu == c) {
        Serial.println("Có wifi rồi nha!");
        break;
      }
    }
    if (millis() - doi_wifi > 3000) {
      doi_wifi = millis();
      Serial3.print("connecting");
      Serial.println("Chờ wifi kết nối");
    }
  }
  digitalWrite(49, HIGH);
  delay(500);
  digitalWrite(49, LOW);
}
