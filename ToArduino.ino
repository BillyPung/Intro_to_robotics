#include <Servo.h>

#define SIZE( a ) sizeof( a ) / sizeof( a[0] )

int ledpin1 = A6;                   //设置系统启动指示灯1
int ledpin2 = A7;                   //设置系统启动指示灯2
int ENA = 5;                        //L298使能A
int ENB = 6;                        //L298使能B
int INPUT2 = 7;                     //电机接口1
int INPUT1 = 8;                     //电机接口2
int INPUT3 = 12;                    //电机接口3
int INPUT4 = 13;                    //电机接口4
int Key1_times;                     //按键1销抖时间
int Key2_times;                     //按键2销抖时间
boolean MoterStatusLED = true;      //电机指示灯状态标示
boolean ServoStatusLED = true;      //舵机指示灯状态标示

/*
  LCD  Arduino2560 PIN
  PIN1 = GND
  PIN2 = 5V
  RS(CS) = A12;                        //液晶屏RS引脚
  RW(SID)= A11;                        //液晶屏RW引脚
  E(CLK) = A13;                        //液晶屏E引脚
  PIN15 PSB = GND;
*/

#define INIT         0               //液晶显示屏初始化显示模式
#define NORMAL       0               //液晶显示屏显示正常模式
#define FOLLOW       1               //液晶显示屏显示跟随模式
#define AVOID        2               //液晶显示屏显示红外避障模式
#define WAVEAVOID    3               //液晶显示屏显示超声波避障模式
static int Level = 0;                //定义菜单级别
static int Mode = 0;                 //定义菜单模式
int Refresh = 0;                     //液晶屏刷新标志

int adjust = 1;                      //定义电机标志位
int Echo = A5;                       // 定义超音波信号接收脚位
int Trig = A4;                       // 定义超音波信号发射脚位
int Input_Detect_LEFT = A13;         //定义小车循迹左侧红外
int Input_Detect_RIGHT = A14;        //定义小车循迹右侧红外
int Input_Detect = A1;               //定义小车前方红外
int Input_Detect_TrackLeft = A2;     //定义小车跟随左侧红外
int Input_Detect_TrackRight = A3;    //定义小车跟随右侧红外
int Carled = A0;                     //定义小车车灯接口
int Cruising_Flag = 0;               //模式切换标志
int Pre_Cruising_Flag = 0 ;          //记录上次模式
int Left_Speed_Hold = 255;           //定义左侧速度变量
int Right_Speed_Hold = 255;          //定义右侧速度变量

Servo servo1;                       // 创建舵机#1号
Servo servo2;                       // 创建舵机#2号
Servo servo3;                       // 创建舵机#3号
Servo servo4;                       // 创建舵机#4号
Servo servo5;                       // 创建舵机#5号
Servo servo6;                       // 创建舵机#6号
Servo servo7;                       // 创建舵机#7号
Servo servo8;                       // 创建舵机#8号

byte angle1 = 70;                    //舵机#1初始值
byte angle2 = 60;                    //舵机#2初始值
byte angle3 = 60;                    //舵机#3初始值
byte angle4 = 60;                    //舵机#4初始值
byte angle5 = 60;                    //舵机#5初始值
byte angle6 = 60;                    //舵机#6初始值
byte angle7 = 60;                    //舵机#7初始值
byte angle8 = 60;                    //舵机#8初始值

int buffer[3];                       //串口接收数据缓存
int rec_flag;                        //串口接收标志位
int serial_data;                     //串口数据零时存储
unsigned long Costtime;              //串口超时计数
int IR_R;                            //跟随右侧红外状态标志
int IR_L;                            //跟随左侧红外状态标志
int IR;                              //中间红外状态标志
int IR_TL;                           //巡线左侧红外状态标志
int IR_TR;                           //巡线右侧红外状态标志

//pin1&pin2 is right side, 2 high is forward. likewise, 4 high is forward.

#define MOTOR_GO_FORWARD  {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}      //车体前进                              
#define MOTOR_GO_BACK     {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}      //车体后退
#define MOTOR_GO_RIGHT    {digitalWrite(INPUT1,HIGH);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,HIGH);}      //车体右转
#define MOTOR_GO_LEFT     {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,HIGH);digitalWrite(INPUT3,HIGH);digitalWrite(INPUT4,LOW);}      //车体左转
#define MOTOR_GO_STOP     {digitalWrite(INPUT1,LOW);digitalWrite(INPUT2,LOW);digitalWrite(INPUT3,LOW);digitalWrite(INPUT4,LOW);}        //车体停止


void setup()
{
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INPUT1, OUTPUT);
  pinMode(INPUT2, OUTPUT);
  pinMode(INPUT3, OUTPUT);
  pinMode(INPUT4, OUTPUT);
  pinMode(Input_Detect_LEFT, INPUT);
  pinMode(Input_Detect_RIGHT, INPUT);
  pinMode(Input_Detect_TrackLeft, INPUT);
  pinMode(Input_Detect_TrackRight, INPUT);
  pinMode(Carled, OUTPUT);
  pinMode(Input_Detect, INPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT);
  digitalWrite(20, HIGH);
  digitalWrite(21, HIGH);

  servo1.attach(11);                      //定义舵机1控制口
  servo2.attach(2);                       //定义舵机2控制口
  servo3.attach(4);                       //定义舵机3控制口
  servo4.attach(3);                       //定义舵机4控制口
  servo5.attach(A8);                      //定义舵机5控制口
  servo6.attach(A9);                      //定义舵机6控制口
  servo7.attach(9);                       //定义舵机7控制口
  servo8.attach(10);                      //定义舵机8控制口

  Serial.begin(9600);
  Serial.println("Starting...");
}



void loop()
{
  Serial.println("setting speed...");
  analogWrite(ENB, 100);
  analogWrite(ENA, 100);
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
  }
   if (data == "W"){
    MOTOR_GO_FORWARD
    delay(1000);
    }
   else if (data == "S"){
    MOTOR_GO_BACK
    delay(1000);
   }
   else if (data == "A"){
    MOTOR_GO_LEFT
    delay(1000);
   }
   else if (data == "D"){
    MOTOR_GO_RIGHT
    delay(1000);
   }
   else if (data == "STOP"){
    MOTOR_GO_STOP
    delay(1000);'

    
   }
   else{
    Serial.println("IOERROR!!!")
   }
  
  
}
