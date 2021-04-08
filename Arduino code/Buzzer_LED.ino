void buzzer_off()
{
  digitalWrite(buzzer, LOW);
}
void buzzer_on()
{
  digitalWrite(buzzer, HIGH);
}
void buzzer_normal()
{ 
  if(dem_on_times < (on_times*2))
  { 
    if (millis() >= previousMillis1) 
        { 
          buzzer_status = !buzzer_status;
          digitalWrite(buzzer, buzzer_status);
          previousMillis1 = millis() + interval_on;
          dem_on_times++;
          if(dem_on_times >= (on_times*2))
          {
            previousMillis1 = millis() - interval_on + interval_off;
          }
        }
  }
  else
  {
    if (millis() >= (previousMillis1)) dem_on_times=0;
  }
}
void buzzer_noline()
{ 
  if(dem_on_times < (on_times*2))
  { 
    if (millis() >= previousMillis1) 
        { 
          buzzer_status = !buzzer_status;
          digitalWrite(buzzer, buzzer_status);
          previousMillis1 = millis() + interval_on;
          dem_on_times++;
        }
  }
  else
  {
    if (millis() >= (previousMillis1)) dem_on_times=0;
  }
}
void led_fade()
{
  if (millis() >= previousMillis2) 
  { 
    for(int i = 0; i < NUM_LEDS; i++ )
    {
     leds[i].setRGB(0,255,0);  // Set Color HERE!!!
     leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade: 
    if(brightness == 0 || brightness == 255)
    {
      fadeAmount = -fadeAmount ; 
    }    
  previousMillis2 = millis() + led_fade_time;
  }
}
void led_noline()
{
  if (millis() >= previousMillis2) 
  { 
    for(int i = 0; i < NUM_LEDS; i++ )
    {
     leds[i].setRGB(255,0,0);  // Set Color HERE!!!
     leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade: 
    if(brightness == 0 || brightness == 255)
    {
      fadeAmount = -fadeAmount ; 
    }    
  previousMillis2 = millis() + led_fade_time;
  }
}

void led_start()
{
    for(int i = 0; i < NUM_LEDS; i++)
    {
     leds[i].setRGB(0,0,255);  // Set Color HERE!!!
     FastLED.show();
    }
}

void led_turn()
{
  if (millis() >= previousMillis2) 
  { 
    for(int i = 0; i < NUM_LEDS; i++ )
    {
     leds[i].setRGB(255,255,0);  // Set Color HERE!!!
     leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade: 
    if(brightness == 0 || brightness == 255)
    {
      fadeAmount = -fadeAmount ; 
    }    
  previousMillis2 = millis() + led_fade_time;
  }
}
