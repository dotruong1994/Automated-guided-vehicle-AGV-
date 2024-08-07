void Stop_station() {
  //Serial3.begin(115200);
  _TURN_AROUND_FUCK();  // không có gia tốc
  //value_way = 0;
  value_cross = 0;
  if (value_way == 1) {
    Serial.println("reset value 1");
    value_way = 0;
    value_cross = 0;
    lockvalue = 0;
    Serial3.print("way1_end");
    Serial3.print("\n");
  }
  if (value_way == 2) {
    Serial.println("reset value 2");
    value_way = 0;
    value_cross = 0;
    lockvalue = 0;
    Serial3.print("way2_end");
    Serial3.print("\n");
  }
  while (1) {
    // Serial.println("station stop");
    motorStop();
    readSensors();
    EMO();
    bool startValue = digitalRead(start_hdw);
    calculateError();
    //bluetooth();
    if (mode != NO_LINE) {
      led_start();

      bool basketStatus = digitalRead(basket_Check);
      if (basketStatus == 1) {
        if (lockvalue == 0) {
          Serial3.print("standby");
          Serial3.print("\n");
          Serial3.print("no_material");
          lockvalue = 1;
        }
        if (Serial3.available() > 0) {
          dulieu = Serial3.readString();
          if (strcmp(dulieu.c_str(), "way1") == 0) {
            Serial.println("read xong chạy way1 rồi ở station!");
            value_way = 1;
            Serial3.print("running");
            giatoc();
            break;
          }
          if (strcmp(dulieu.c_str(), "way2") == 0) {
            Serial.println("read xong chạy way2 rồi ở station!");
            value_way = 2;
            Serial3.print("running");
            giatoc();
            break;
          }
        }
      }
      if (startValue == 0) {
        if (value_way != 0) {
          giatoc();
          break;
        }
      }

      if (digitalRead(function_3) == 0) {
        giatoc();
        break;
      }

      if (check == 0) {
        if (digitalRead(function_1) == 0 || digitalRead(function_2) == 0) {
          delay_time = millis();
          check = 1;
        }
      }
      if (check == 1) {
        if (millis() - delay_time > 2000) {
          if (digitalRead(function_1) == 0) {
            Serial3.print("function_1");
            Serial3.print("\n");
            Serial3.print("running");
            value_way = 1;
            giatoc();
            check = 0;
            break;
          }
          if (digitalRead(function_2) == 0) {
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



void Stop_outline() {
  motorStop();
  int bien_tam = 0;
  while (1) {
    bool startValue = digitalRead(start_hdw);
    bool resetValue = digitalRead(reset_hdw);
    readSensors();
    calculateError();
    read_safety_Sensors();
    safety_stop();
    if (mode != NO_LINE) {
      if (resetValue == 0) {
        digitalWrite(out_line, LOW);
        led_start();
        bien_tam = 1;
          
        Serial.println("OUTLINE_done");
      }
      if (bien_tam == 1) {
        if (startValue == 0) {
          if (value_way != 0) {
            giatoc();
            mode = FOLLOWING_LINE;
            error = 0;
            Serial.println("chay di");
            Serial3.print("HAVE_LINE"); 
            return;
            //break;
          }
        }
        if (digitalRead(function_3) == 0) {
          giatoc();
          mode = FOLLOWING_LINE;
          error = 0;
          Serial.println("chay di");
          Serial3.print("HAVE_LINE");
          Serial.print(mode); 
          return;
        }
      }
    }
  }
}

void _TURN_AROUND_() {
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  while (1) {
    led_turn();
    analogWrite(motor1pwmPin, 25);
    analogWrite(motor2pwmPin, 25);
    readSensors();
    EMO();
    if ((ir[6] == 1) || (ir[7] == 1)) {
      while (1) {
        readSensors();
        EMO();
        if ((ir[3] == 1) || (ir[4] == 1))
          break;
      }
      break;
    }
  }
  Serial3.print("TURN_AROUND");
  Serial3.print("\n");
  chaythang();
  giatoc();
}

void _TURN_AROUND_FUCK() {
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  while (1) {
    led_turn();
    analogWrite(motor1pwmPin, 25);
    analogWrite(motor2pwmPin, 25);
    readSensors();
    EMO();
    if ((ir[6] == 1) || (ir[7] == 1)) {
      while (1) {
        readSensors();
        EMO();
        if ((ir[3] == 1) || (ir[4] == 1))
          break;
      }
      break;
    }
  }
  chaythang();
}


void _turnLeft_() {
  Serial.println("_turnLeft_");
  digitalWrite(d1, LOW);  //LOW
  digitalWrite(d2, LOW);
  while (1) {
    led_turn();
    analogWrite(motor1pwmPin, 15);
    analogWrite(motor2pwmPin, 15);
    readSensors();
    EMO();
    if ((ir[1] == 1) && (ir[0] == 1)) {
      while (1) {
        readSensors();
        EMO();
        if ((ir[3] == 1) && (ir[4] == 1))
          break;
      }
      break;
    }

    //else if ((ir[4] == 1) && (ir[3] == 1) && (ir[2] == 0) && (ir[1] == 0) && (ir[0] == 0)) break;
  }
  chaythang();
  giatocTurn();
}

void _turnRight_() {
  Serial.println("_turnRight_");
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  while (1) {
    led_turn();
    analogWrite(motor1pwmPin, 15);
    analogWrite(motor2pwmPin, 15);
    readSensors();
    EMO();
    if ((ir[6] == 1) || (ir[7] == 1)) {
      while (1) {
        readSensors();
        EMO();
        if ((ir[3] == 1) && (ir[4] == 1))
          break;
      }
      break;
    }
  }
  chaythang();
  giatocTurn();
}




void motorStop() {
  motor1newSpeed = 0;
  motor2newSpeed = 0;
  analogWrite(motor1pwmPin, motor1newSpeed);
  analogWrite(motor2pwmPin, motor2newSpeed);
}

// void motor_Wait() {
//   motorStop();
//   while (1) {
//     led_noline();
//     readSensors();

//     calculateError();
//     read_safety_Sensors();
//     if ((ir_st[0] == 0) && (ir_st[1] == 0) && (ir_st[2] == 0)){

//       break;
//     }
//   }
//   readSensors();
//   calculateError();
//   giatoc();
// }

void motor_Wait() {
  motorStop();
  while (1) {
    led_noline();
    readSensors();
    EMO();
    calculateError();
    read_safety_Sensors();
    if ((ir_st[0] == 0) && (ir_st[1] == 0) && (ir_st[2] == 0)) {
      int demccc = 0;
      // digitalWrite(reset_relay, HIGH);
      while (demccc < 300) {
        demccc++;
        led_noline();
        Serial.println("đợi xí rồi chay");
      }
      // digitalWrite(reset_relay, LOW);
      demccc = 0;
      readSensors();
      EMO();
      calculateError();
      read_safety_Sensors();
      if ((ir_st[0] == 0) && (ir_st[1] == 0) && (ir_st[2] == 0)) break;
    }
  }
  Serial3.print("\n");
  Serial3.print("RELEASE");
  Serial3.print("\n");
  readSensors();
  EMO();
  calculateError();
  giatoc();
}


//void Stop_EMO()
//{ motorStop();
//  while(1)
//  { led_noline();
//    emo_hdw.read();
//    if(emo_hdw.isReleased()){break;}
//  }
//  while(1)
//    {
//      if(safety_var ==1){led_start();}else led_noline();
//      emo_hdw.read();
//      reset_hdw.read();
//      start_hdw.read();
//      bluetooth();
//      if(mode!=NO_LINE)
//      {
//          if(reset_hdw.wasPressed()&&emo_hdw.isReleased()){safety_var =1;Serial.println(safety_var);led_start();}
//          if(start_hdw.wasPressed()&&safety_var ==1)
//             {
//             safety_var =0;
//             giatoc();
//             break;
//             }
//          }
//     }
//}






//void Stop_EMO()
//{ motorStop();
//  safety_var =0;
//  while(1)
//  { led_noline();
//    emo_hdw.read();
//    bumper_hdw.read();
//    Serial.println("Stop emo");
//    if(emo_hdw.isReleased()&& bumper_hdw.isReleased()){break;}
//  }
//  while(1)
//    { Serial.println("kẹt ở emo chờ reset");
//      if(safety_var ==1){led_start();}else led_noline();
//      readSensors();
//      calculateError();
//      bluetooth();
//      if(mode!=NO_LINE)
//      {
//          if(reset_hdw.isPressed())
//          {
//            safety_var =1;led_start();
//            while(1)
//          {   emo_hdw.read();
//              bumper_hdw.read();
//              start_hdw.read();
//              Serial.println("kẹt ở emo chờ start");
//              Serial.println(safety_var);
//              if(start_hdw.isPressed()&&safety_var ==1&&emo_hdw.isReleased()&& bumper_hdw.isReleased())
//                 {
//                 Serial.println("final step");
//                 safety_var =0;
//                 safety_var_bumper =0;
//                 giatoc();
//                 break;
//                 }
//            }
//          }
//       }
//     }
//
//}
//
//void Stop_bumper()
//{ motorStop();
//  safety_var_bumper =0;
//  while(1)
//  { led_noline();
//    bumper_hdw.read();
//    emo_hdw.read();
//    Serial.println("Stop bumper");
//    if( bumper_hdw.isReleased()&&emo_hdw.isReleased()){break;}
//  }
//  while(1)
//    { Serial.println("kẹt ở bumper chờ start");
//      if(safety_var_bumper ==1){led_start();}else led_noline();
//      readSensors();
//      calculateError();
//      bluetooth();
//      if(mode!=NO_LINE)
//      {
//            if(reset_hdw.isPressed())
//            {
//              safety_var_bumper =1;led_start();
//               while(1)
//               {  emo_hdw.read();
//                  bumper_hdw.read();
//                  start_hdw.read();
//                  if(start_hdw.isPressed()&&safety_var_bumper ==1&&emo_hdw.isReleased()&& bumper_hdw.isReleased())
//                     {
//                     safety_var_bumper =0;
//                     safety_var =0;
//                     giatoc();
//                     break;
//                     }
//               }
//            }
//          }
//     }
//
//}

// void Stop_station() {
//   Serial3.begin(9600);
//   _TURN_AROUND_FUCK();  // không có gia tốc
//   //value_way = 0;
//   value_cross = 0;
//   if (value_way == 1) {
//     Serial.println("reset value 1");
//     value_way = 0;
//     value_cross = 0;
//     Serial3.print("way1_end");
//     Serial3.print("\n");
//     Serial3.print("standby");
//     Serial3.print("\n");
//   }
//   if (value_way == 2) {
//     Serial.println("reset value 2");
//     value_way = 0;
//     value_cross = 0;
//     Serial3.print("way2_end");
//     Serial3.print("\n");
//     Serial3.print("standby");
//     Serial3.print("\n");
//   }
//   while (1) {
//     // Serial.println("station stop");
//     motorStop();
//     readSensors();
//     calculateError();
//     //bluetooth();
//     if (mode != NO_LINE) {
//       led_start();
//       bool basketStatus = digitalRead(basket_Check);
//       if (basketStatus == 1) {
//         if (Serial3.available() > 0) {
//           dulieu = Serial3.readString();
//           if (strcmp(dulieu.c_str(), "way1") == 0) {
//             Serial.println("read xong chạy way1 rồi ở station!");
//             value_way = 1;
//             Serial3.print("running");
//             giatoc();
//             break;
//           }
//           if (strcmp(dulieu.c_str(), "way2") == 0) {
//             Serial.println("read xong chạy way2 rồi ở station!");
//             value_way = 2;
//             Serial3.print("running");
//             giatoc();
//             break;
//           }
//         }
//       }


//       if (start_hdw.wasPressed()) {
//         giatoc();
//         break;
//       }
//     }
//   }
// }
