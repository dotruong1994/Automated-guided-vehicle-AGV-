void readSensors() 
{
  for (int pin = 0; pin < 8; pin++) 
  {
    int pinNum = Sensors[pin];
    ir[pin] = digitalRead(pinNum);
  }
  start_hdw.read();
  reset_hdw.read();
  emo_hdw.read();
  function1.read();
  function2.read();
  function3.read();
} 

void calculateError() 
{
  //Determine an error based on the readings
  if      ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0) && (ir[7] == 1)) {mode = FOLLOWING_LINE;error = 6;} 
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 1) && (ir[7] == 1)) {mode = FOLLOWING_LINE;error = 5;}  // lech trai   
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 1) && (ir[6] == 1) && (ir[7] == 1)) {mode = FOLLOWING_LINE;error = 5;}  // lech trai         
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 1) && (ir[7] == 0)) {mode = FOLLOWING_LINE;error = 5;}  // lech tra
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 1) && (ir[6] == 1) && (ir[7] == 0)) {mode = FOLLOWING_LINE;error = 4;}  // lech tra
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 1) && (ir[5] == 1) && (ir[6] == 1)) {mode = FOLLOWING_LINE;error = 3;} // lech trai
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 1) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 3;} // lech trai
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 1) && (ir[5] == 1) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 2;} // lech trai
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 1) && (ir[4] == 1) && (ir[5] == 1) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 1;} // lech trai
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 1) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 1;}

  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 1) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 0;}// khong lech
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 1) && (ir[4] == 1) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 0;}// khong lech
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 1) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = 0;}// khong lech
  
  else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 1) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -1;}
  else if ((ir[1] == 0) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 1) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -1;}// lech phai
  
  else if ((ir[1] == 0) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -2;}// lech phai
  
  else if ((ir[1] == 0) && (ir[2] == 1) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -3;}// lech phai
  else if ((ir[1] == 1) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -3;}// lech phai
  
  else if ((ir[0] == 0) && (ir[1] == 1) && (ir[2] == 1) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -4;}// lech phai

  else if ((ir[0] == 0) && (ir[1] == 1) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -5;}// lech phai
  else if ((ir[0] == 1) && (ir[1] == 1) && (ir[2] == 1) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -5;}// lech phai
  
  else if ((ir[0] == 1) && (ir[1] == 1) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -5;}// lech phai
  
  else if ((ir[0] == 1) && (ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0)) {mode = FOLLOWING_LINE;error = -6;}

  else if ((ir[0] == 0) && (ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0) && (ir[7] == 0)) {mode = NO_LINE;error = 0;led_noline();}// stop
  
  //TURN_AROUND
  else if ((ir[1] == 1) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 1) && (ir[5] == 1) && (ir[6] == 1)) {mode = TURN_AROUND;error = 0;}
  //Slow down the speed
  else if ((ir[0] == 1) && (ir[1] == 1) && (ir[2] == 1)&& (ir[3] == 1) && (ir[6] == 0) && (ir[7] == 0)) {mode = SLOW_DOWN;error = 0;}
//else if ((ir[4] == 1) && (ir[5] == 1) && (ir[6] == 1) && (ir[7] == 1) && (ir[0] == 0) && (ir[1] == 0)) {mode = TURN_RIGHT;error = 0;}

  else if(((ir[0] == 1) && ((ir[1] == 0) || (ir[2] == 0)) && ((ir[3] == 1) || (ir[4] == 1))) ||
          ((ir[2] == 1) && ((ir[3] == 0) || (ir[4] == 0)) && ((ir[5] == 1) || (ir[6] == 1))) || 
          ((ir[4] == 1) && (ir[5] == 0) && (ir[7] == 1)) ||
          ((ir[0] == 1) && ((ir[1] == 0) || (ir[2] == 0)) && ((ir[3] == 1) || (ir[4] == 1)) && ((ir[5] == 0) || (ir[6] == 0)) && (ir[7] == 1)))
  { 
    readSensors();
    if   (((ir[0] == 1) && ((ir[1] == 0) || (ir[2] == 0)) && ((ir[3] == 1) || (ir[4] == 1))) ||
          ((ir[2] == 1) && ((ir[3] == 0) || (ir[4] == 0)) && ((ir[5] == 1) || (ir[6] == 1))) || 
          ((ir[4] == 1) && (ir[5] == 0) && (ir[7] == 1)) ||
          ((ir[0] == 1) && ((ir[1] == 0) || (ir[2] == 0)) && ((ir[3] == 1) || (ir[4] == 1)) && ((ir[5] == 0) || (ir[6] == 0)) && (ir[7] == 1)))
    {
      mode = STATION;error = 0;
    }
  } 
}
