void run_extra_station()   // chạy thêm khi đang ở trạm
{
  analogWrite(motor1pwmPin,speedSet);  
  analogWrite(motor2pwmPin,speedSet);
  Serial.println("run_extra_station");
  delay(130);
}

void run_extra_turn()     // chạy thêm để rẽ cho chuẩn
{
  analogWrite(motor1pwmPin,speedSet);  
  analogWrite(motor2pwmPin,speedSet);
  Serial.println("run_extra_turn");
  delay(200);
}


void run_extra_gia_toc()    // gia tốc riêng khi xe dừng đúng ngay trạm
{
  analogWrite(motor1pwmPin,speedSet);  
  analogWrite(motor2pwmPin,speedSet);
  Serial.println("run_extra_gia_toc");
  delay(100);
}


void run_extra_cross()      // chạy thêm để check xem cross nào, cái này phải chuẩn
{ 
  analogWrite(motor1pwmPin,speedSet);  
  analogWrite(motor2pwmPin,speedSet);
  Serial.println("run_extra_cross");
  delay(300);
}