void read_safety_Sensors() {
  for (int pin_st = 0; pin_st < 3; pin_st++) {
    int pin_st_Num = safety_Sensors[pin_st];
    ir_st[pin_st] = digitalRead(pin_st_Num);
  }
  // emo_hdw.read();
  //bumper_hdw.read();
  // start_hdw.read();
  //reset_hdw.read();
  bool emoValue = digitalRead(emo_hdw);

  if (emoValue == 0) {
    Stop_EMO();
  }
  //       if(bumper_hdw.isPressed())
  //        {
  //          Stop_bumper();
  //        }
}

void Stop_EMO() {
  motorStop();
  Serial3.print("EMO_in");
  Serial3.print("\n");
  while (1) {
    led_noline();
    bool resetValue = digitalRead(reset_hdw);
    bool emoValue = digitalRead(emo_hdw);
    int khoa;
    readSensors();
    calculateError();
    if (mode == NO_LINE) {
      Stop_outline();
      return;
    }
    if (emoValue == 1) {
      if (resetValue == 0) {
        if (mode != NO_LINE) {
          digitalWrite(out_line, LOW);
          led_start();
          Serial.println("emo_done");
          while (1) {
            bool startValue = digitalRead(start_hdw);
            if (startValue == 0) {
              if (value_way != 0) {
                mode = FOLLOWING_LINE;
                error = 0;
                giatoc();
                Serial3.print("EMO_out");
                return;
              }
            }
            if (digitalRead(function_3) == 0) { 
              mode = FOLLOWING_LINE;
              error = 0;
              giatoc();
              Serial3.print("EMO_out");
              Serial.println("run_after_emo");
              return;
            }
          }
        }
      }
    }
  }
}


void safety_stop() {
  if ((ir_st[0] == 1) && (ir_st[1] == 1) && (ir_st[2] == 1)) {
    motorStop();
  }
}



void safety_status_check() {
  if ((ir_st[0] == 1) && (ir_st[1] == 1)) {
    delay(50);  // lech trai
  }
  if ((ir_st[0] == 1) && (ir_st[1] == 1)) {
    mode = MOTOR_WAITING;
    led_noline();
  }
}

void giamtoc_safety() {
  chaythang();
  int i = 1;
  while (i <= 30) {
    led_fade();
    readSensors();
    calculateError();
    read_safety_Sensors();
    if (mode == NO_LINE) {
      break;
    }
    if (millis() >= previousMillis) {
      motor2Speed = minimumspeed_giatoc_safety - i;  //-15;
      motor1Speed = minimumspeed_giatoc_safety - i;  //-15;
      i++;
      previousMillis = millis() + 100;
    }
    if ((ir_st[0] == 1) && (ir_st[1] == 1) && (ir_st[2] == 1)) {
      motor_Wait();
    }
    pidCalculations();
    changeMotorSpeed();
  }
  //  read_safety_Sensors();
  if ((ir_st[0] == 0) && (ir_st[1] == 0) && (ir_st[2] == 0)) {
    giatoc_safety();
  }
}
