void bluetooth()
{
  if(Serial2.available() > 0)
  { 
    command = Serial2.read(); 
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
     case 'S':
      Stop();
      break;
     case 'G':
      forwardleft();
      break;
     case 'I':
      forwardright();
      break;      
     case 'V':
      buzzer_on();
      break;  
    }
  } 
}

void forward()
{ 
  chaythang();
  if (millis() >= previousMillis) 
  { a++;
    if(a>=150) a=150;
    previousMillis = millis() + 20;
  }
  analogWrite(motor2pwmPin,a+1);
  analogWrite(motor1pwmPin,a);
}

void back()
{
  chaylui();
  analogWrite(motor2pwmPin,20);
  analogWrite(motor1pwmPin,20);
}

void left()
{ chaythang();
  a=0;
  analogWrite(motor1pwmPin,2);
  analogWrite(motor2pwmPin,35);
}

void right()
{ chaythang();
  a=0;
  analogWrite(motor1pwmPin,35);
  analogWrite(motor2pwmPin,2);
} 

void Stop()
{ a=0;
  analogWrite(motor1pwmPin,0);
  analogWrite(motor2pwmPin,0);
  buzzer_off();
}
void forwardleft()
{ 
  chaythang();
  analogWrite(motor1pwmPin,a/3);
}
void forwardright()
{ 
  chaythang();
  analogWrite(motor2pwmPin,a/3);
}
