void Stop_station()
{ 
  Serial3.begin(9600);
  while(1)
    { 
      motorStop();
      readSensors();
      calculateError();
      bluetooth();   
      if(mode!=NO_LINE)
      { led_start();
        if(Serial3.available()>0)
         {
            data = Serial3.readString();
            if(data=="concac")
            {
              giatoc();
              Serial3.print("OK"); 
              Serial3.end();
              break;
            }
         }     
          if(start_hdw.wasPressed())
          {
             giatoc();
             break;
          }
      }
  } 
}

void Stop_outline()
{ motorStop();
  while(1)
    { 
      readSensors();
      calculateError();
      bluetooth();   
      if(mode!=NO_LINE)
      { led_start();  
          if(start_hdw.wasPressed())
          {
             giatoc();
             break;
          }
      }
    } 
}

void _TURN_AROUND_()
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  while(1)
  { 
    led_turn();
    analogWrite(motor1pwmPin,20);
    analogWrite(motor2pwmPin,20);
    readSensors(); 
    if      ((ir[4] == 1) && (ir[5] == 1) && (ir[6] == 0) && (ir[7] == 0))  break;
    else if ((ir[3] == 1) && (ir[4] == 1) && (ir[5] == 0) && (ir[6] == 0) && (ir[7] == 0)) break; 
  }
  chaythang();
  giatoc();
}
