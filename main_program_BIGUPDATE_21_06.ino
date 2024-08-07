//Khai báo thư viện
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <FastLED.h>
#include <string.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN);

//Khai báo đèn xe
#define NUM_LEDS 28
#define PIN 7
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
int fadeAmount = 5;
int brightness = 0;
int led_fade_time = 10;
int value_way = 0;


//Khai báo sensor dò line
volatile int Sensors[] = { 22, 23, 24, 25, 26, 27, 28, 29 };  // sensor pins {0,1,2,3,4,5,6,7} tren sensor
volatile int ir[8];

//Khai báo sensor an toàn
volatile int safety_Sensors[] = { 8, 9, 18 };  // đổi chân 10 thành chân 18
volatile int ir_st[3];
volatile int safety_var = 0;

volatile int safety_var_bumper = 0;

//Khai báo PID
float pTerm, iTerm, dTerm;
int error = 0;
int previousError = 0;
float kp = 4;  //11;0.7 Tốc độ đáp ứng
float ki = 0;  //
float kd = 2;  //11;0.15
float output;
int integral, derivative;

volatile int speedSet = 150;
//Khai báo tốc độ động cơ
volatile int motor2Speed = speedSet;          // tốc dộ động cơ phải
volatile int motor1Speed = speedSet;          // tốc độ động cơ trái
int maximumspeed = speedSet;                  // max speed PID
int minimumspeed = 5;                   // min speed PID
int minimumspeed_giatoc = motor1Speed;  // gán speed ngược lại tốc độ
int minimumspeed_giatoc_safety = motor1Speed;
int motor1newSpeed;  // biến tốc độ motor1 mới
int motor2newSpeed;  // biến tốc độ motor2 mới
bool lockvalue =0;
//biến để dành sau này
int value_cross = 0;
int value_station = 0;
//khai báo mode mặc định
int mode = 0;

//biến dành cho bluetooth
char command;

// định nghĩa các trạng thái sẽ sử dụng
#define NO_LINE 0
#define FOLLOWING_LINE 1
#define STATION 2
#define SLOW_DOWN 3
#define SLOW_DOWN_SAFETY 4
#define MOTOR_WAITING 5
#define TURN_LEFT 6
#define TURN_RIGHT 7

//Khai báo chân còi xe
#define buzzer 16
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
int d2 = 41;    //R

//Khai báo chân điều xung motor
int motor1pwmPin = 2;  //L
int motor2pwmPin = 3;  //R
// Khai báo nút nhấn điều khiển xe.
int check;
unsigned long delay_time;
// Button bumper_hdw(19);


#define basket_Check 48  // sensor kiểm tra rổ liệu
#define start_hdw 31  // sensor kiểm tra rổ liệu
#define reset_hdw 30  // sensor kiểm tra rổ liệu
#define emo_hdw   32
#define function_1 33 
#define function_2 34
#define function_3 35 
 // sensor kiểm tra rổ liệu
 #define out_line 51
//#define reset_relay 50
/*
 * Khai báo biến đếm thời gian
 */
unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long doi_wifi;
int interval_on = 1000;
int interval_off = 8000;
byte on_times = 2;
byte dem_on_times = 0;
bool buzzer_status = 0;
byte a = 0;
byte b = 0;


// biến Wifi
String dulieu;
void setup() {
  Serial.begin(115200);
  //Serial2.begin(9600);
  Serial3.begin(115200);
  SPI.begin();  // SPI cho module RFID
  rfid.PCD_Init();
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
  pinMode(49, OUTPUT);
  pinMode(out_line, OUTPUT);
  digitalWrite(out_line, LOW);
  pinMode(basket_Check,INPUT_PULLUP);
  pinMode(start_hdw,INPUT_PULLUP);
  pinMode(reset_hdw,INPUT_PULLUP);
  pinMode(emo_hdw,INPUT_PULLUP);
  pinMode(function_1,INPUT_PULLUP);
  pinMode(function_2,INPUT_PULLUP);
  pinMode(function_3,INPUT_PULLUP);
  // Khai báo hiển thị LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("SUPER AGV");
  lcd.setCursor(1, 1);
  lcd.print("AE DEPARTMENT!");

  // Kiểm tra trạng thái sensor lúc mở máy
  for (int pin = 0; pin < 8; pin++) {
    int pinNum = Sensors[pin];
    pinMode(pinNum, INPUT);
  }

  for (int pin_st = 0; pin_st < 3; pin_st++) {
    int pin_st_Num = safety_Sensors[pin_st];
    pinMode(pin_st_Num, INPUT_PULLUP);
  }
  // Khởi tạo các chân nút nhấn
  // bumper_hdw.begin();


  //Khai báo điều khiển đèn xe
  FastLED.addLeds<WS2813, PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  //Chạy chương trình con khởi tạo
  enable();  // cho 2 biến en của driver về LOW
              //dis_enable();
  brake_off();
  chaythang();  // set chân dir của driver
  led_wifi_start();
  checkWIFI();
  khoidong();
  
}

void loop() 
{
  readSensors();
  EMO();
  calculateError();
  read_safety_Sensors();
  safety_status_check();
  switch (mode) 
  {
    case NO_LINE:
      Serial3.print("NO_LINE");
      previousError = 0;
      Stop_outline();
      //buzzer_noline();
      break;
    case FOLLOWING_LINE:
      led_fade();
      pidCalculations();
      changeMotorSpeed();
      previousError = 0;
      //buzzer_normal();
      break;
    case STATION:
      value_cross++;
      Serial3.print("cross");
      Serial3.print(value_cross);
      Serial3.print("\n");
      Serial.println("vào case STATION");
      Serial.println(value_cross);
      run_extra_station();
      readSensors();
      EMO();
      if ((ir[0] == 1)&&(ir[5] == 0)&&(ir[6] == 0)&&(ir[7] == 0)) {
        // Serial.println("vào trạm");
        Stop_station();
        // chỗ này viết thêm chạy phát nữa mới quay đầu
      } else {
        run_extra_cross();
        if (value_way == 1) {
          Way_1();
        } else if (value_way == 2) {
          Way_2();
        } else if (value_way == 3) {
          Way_3();
        }
      }
      break;
    // case SLOW_DOWN:
    //   giamtoc();
    //   break;

    // case SLOW_DOWN_SAFETY:
    //   giamtoc_safety();
    //   break;

    case MOTOR_WAITING:
      Serial3.print("MOTOR_WAITING");
      motor_Wait();
      break;

    // case TURN_LEFT:
    //   run_extra_turn();
    //   _turnLeft_();
    //   break;

    // case TURN_RIGHT:
    //   run_extra_turn();
    //   _turnRight_();
    //   break;
  }
}
