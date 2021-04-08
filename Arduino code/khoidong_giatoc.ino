void khoidong()
{ 
  Serial3.begin(9600);
  while(1)
  { 
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
            Serial.println("readok");
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

void giatoc()
{   
    chaythang();
    int i = 0;
    while(i <= minimumspeed_giatoc)
    { 
      led_fade();
      readSensors();
      calculateError();
      if(mode==NO_LINE)
      {
        break;
      }
      if (millis() >= previousMillis) 
      {
         motor2Speed = i;//-15;
         motor1Speed = i;//-15;
         i++;
         previousMillis = millis() + 100;
      }
      pidCalculations();
      changeMotorSpeed();
    }
}

void giamtoc()
{
  chaythang();
  int i =1;
  while(i<= 30)
  { led_fade();
    readSensors();
    calculateError();
    if(mode==NO_LINE)
    {
      break;
    }
    if (millis() >= previousMillis) 
    {
       motor2Speed = minimumspeed_giatoc- i;//-15;
       motor1Speed = minimumspeed_giatoc- i;//-15;
       i++;
       previousMillis=millis()+200;
    }
    pidCalculations();
    changeMotorSpeed();
  }
}
