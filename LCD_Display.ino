void LCD_display_speed()
{
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("SUPER AGV");
  lcd.setCursor(1,1);
  lcd.print("Speed:");
}
void LCD_wifi_disconnect()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WIFI_disconnect");
}


