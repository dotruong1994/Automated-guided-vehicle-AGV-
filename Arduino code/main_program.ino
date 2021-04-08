//Khai báo thư viện
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
#include <JC_Button.h>
#include <FastLED.h>

//Khai báo đèn xe
#define NUM_LEDS 28
#define PIN 7
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
int fadeAmount = 5;
int brightness = 0;
int led_fade_time = 10;

//Khai báo sensor dò line
int Sensors[] = {22,23,24,25,26,27,28,29}; // sensor pins {0,1,2,3,4,5,6,7} tren sensor
int ir[8];

//Khai báo PID
float pTerm, iTerm, dTerm;
int error=0;
int previousError=0;
float kp = 2;  //11;0.7 Tốc độ đáp ứng
float ki = 0;     //
float kd = 0;  //11;0.15
float output;
int integral, derivative;

//Khai báo tốc độ động cơ
int motor2Speed = 50; // tốc dộ động cơ phải
int motor1Speed = 50; // tốc độ động cơ trái
int maximumspeed = 80; // max speed PID
int minimumspeed = 5;  // min speed PID
int minimumspeed_giatoc = motor1Speed; // gán speed ngược lại tốc độ
int motor1newSpeed; // biến tốc độ motor1 mới
int motor2newSpeed; // biến tốc độ motor2 mới
long balance = 0.1;

//biến để dành sau này
int value_cross=0;
int value_station=0;
//khai báo mode mặc định
int mode=0;

//biến dành cho bluetooth
char command; 

// định nghĩa các trạng thái sẽ sử dụng 
#define NO_LINE 0
#define FOLLOWING_LINE 1
#define STATION 2
#define SLOW_DOWN 3
#define TURN_AROUND 4
#define TURN_RIGHT 5  
#define VALUE 6  
  
//Khai báo chân còi xe
#define buzzer 19
//Khai báo Driver 1
int alm1 = 40;
int speed1 = 39;
int brk1 = 38;
int en1 = 37;
int d1 = 36;

//Khai báo Driver 2
int alm2 = 45;
int speed2 = 44;
int brk2 = 43;  //R
int en2 = 42;   //R
int d2 = 41;   //R

//Khai báo chân điều xung motor
int motor1pwmPin = 2; //L
int motor2pwmPin = 3; //R

// Khai báo nút nhấn điều khiển xe.
Button start_hdw(31);
Button reset_hdw(30);
Button emo_hdw(32);
Button function1(33);
Button function2(34);
Button function3(35);
Button wifi_signal(46);


/*
 * Khai báo biến đếm thời gian
 */
unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
int interval_on = 1000;
int interval_off = 8000;
byte on_times = 2;
byte dem_on_times = 0;
bool buzzer_status = 0;
byte a = 0;
byte b = 0;

// biến Wifi
String data;
void setup() 
{ 
  Serial.begin(9600);
  Serial2.begin(9600);
  
 //Khai báo pinMode cho các chân điều khiển
  pinMode(alm1, INPUT);
  pinMode(speed1, INPUT);
  pinMode(brk1, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(alm2, INPUT);
  pinMode(speed2, INPUT);
  pinMode(brk2, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
 // Khai báo hiển thị LCD
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("SUPER AGV");
  lcd.setCursor(1,1);
  lcd.print("AE DEPARTMENT!");
  
 // Kiểm tra trạng thái sensor lúc mở máy 
  for (int pin = 0; pin < 8; pin++) 
  {
    int pinNum = Sensors[pin];
    pinMode(pinNum, INPUT);
  }

 // Khởi tạo các chân nút nhấn 
  start_hdw.begin();
  reset_hdw.begin();
  emo_hdw.begin();
  function1.begin();
  function2.begin();
  function3.begin();
  wifi_signal.begin();

 //Khai báo điều khiển đèn xe 
  FastLED.addLeds<WS2813, PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
 
 //Chạy chương trình con khởi tạo 
  enable();
  brake_off();
  chaythang();
  khoidong();
  
}

void loop() 
{ 
  readSensors();
  calculateError();
  switch(mode)
  {
      case NO_LINE:
         previousError=0;    
         Stop_outline();
         break;
      case FOLLOWING_LINE:
         led_fade();  
         pidCalculations();
         changeMotorSpeed();
         previousError=0;
         break;
      case STATION:
         run_extra_station();
         readSensors();
         if ((ir[1] == 1) && (ir[2] == 1) && (ir[3] == 1) && (ir[4] == 1) && (ir[5] == 1) && (ir[6] == 1))
           {
             Stop_station();  
           }
         else if ((ir[1] == 0) && (ir[2] == 0) && (ir[3] == 0) && (ir[4] == 0) && (ir[5] == 0) && (ir[6] == 0))
           {
             _TURN_AROUND_();
           }
         else
           {
              mode = FOLLOWING_LINE;
           }
         break;
      case SLOW_DOWN:
         giamtoc();
         break;         
  }
}
void motorStop()
{
  motor1newSpeed=0;
  motor2newSpeed=0;
  analogWrite(motor1pwmPin,motor1newSpeed);
  analogWrite(motor2pwmPin,motor2newSpeed);
}
