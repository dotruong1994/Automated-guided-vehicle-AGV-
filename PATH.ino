void Way_1()
{
  Serial.println("way 1");
   if(value_cross==1)
   {
    led_start();
    motorStop();
    // stop ở đây để chuân bị quay đầu 
    
    while(1){
      //đọc sensor kiểm tra rổ liệu
      motorStop();
      readSensors();
      EMO();
      bool basketStatus = digitalRead(basket_Check);
      if(basketStatus ==0){
        int demcc =0;
        while(demcc<1000){
          led_fade();
          demcc++;
          Serial.println(demcc);
          }
        Serial.println("delay xong rồi break ra");
        demcc =0;
        Serial3.print("\n");
        Serial3.print("have_material");
        Serial3.print("\n");
        _TURN_AROUND_();
        Serial.println("quay đầu ở trạm 1");
        break;
      }
      
      //_TURN_AROUND_();
    }
  }
  //  else if(value_cross==2)
  //  {
  //    run_extra_cross(); //phong hờ
  //    run_extra_cross();
  //   _turnRight_();
  //  }
}
void Way_2()
{
   Serial.println("way 2");
   if(value_cross==2)
   {
      motorStop();
      led_start();
      readSensors();
      EMO();
      calculateError();
      // stop ở đây để chuân bị quay đầu 
      
      while(1){
        //đọc sensor kiểm tra rổ liệu
      bool basketStatus = digitalRead(basket_Check);
        if(basketStatus ==0){
          int demcc =0;
          while(demcc<1000){led_fade();demcc++;Serial.println(demcc);}
          demcc =0;
        Serial3.print("\n");
        Serial3.print("have_material");
        Serial3.print("\n");
          _TURN_AROUND_();
          Serial.println("quay đầu ở trạm 2");
          break;
        }  
       // _TURN_AROUND_();   
      }
  }
  //  else if(value_cross==4)
  //  {
  //    run_extra_cross();
  //   _turnRight_();
  //  }  
}
void Way_3()
{
   if(value_cross==1)
   {
   _turnLeft_();
   }
   else if(value_cross==2)
   {
     run_extra_cross();
    _turnRight_();
   }  
}
