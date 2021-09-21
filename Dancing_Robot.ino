#include <Servo.h>
#include <FastLED.h>
#define NUM_LEDS 64
#define DATA_PIN 2
#include <Servo.h>
      int E1 = 5;     //M1 Speed Control  
      int E2 = 6;     //M2 Speed Control  
      int M1 = 4;    //M1 Direction Control  
      int M2 = 7;    //M1 Direction Control  
      int color_cnt = 0;
      CRGB leds[NUM_LEDS];
  
Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin




      // the setup function runs once when you press reset or power the board  
      void setup() {  
        FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
        for(int i = 0;i < NUM_LEDS;i ++){
          leds[i] = CRGB::Black;
        }
        myservo.attach(9);
          pinMode(LED_BUILTIN, OUTPUT);
        // initialize pins for the motor driver  
        int i;  
        for (i = 4; i <= 7; i++)  
          pinMode(i, OUTPUT);  
      
  
        // goes forward for 0.5s  
        advance(255, 255);  
        delay(500);  
        stop();  
        delay(4500); 

         
        delay(500);  
        stop();  
        delay(2000);  
  
        // does a big circle to the left for 3s  
        advance(100, 150);  
        delay(1000);  
        stop();  
        delay(3000);  
      
  
        // does a nmall  circles to the right for 3s  
        advance(255, 100);  
        delay(1500);  
        stop();  
        delay(3000);  
      }  
           
void turn1() {
      val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
      val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
      myservo.write(val);                  // sets the servo position according to the scaled value
      delay(15);                           // waits for the servo to get there
}
void turn2() {
      val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
      val = map(val, 0, 1023, 0, 90);     // scale it to use it with the servo (value between 0 and 180)
      myservo.write(val);                  // sets the servo position according to the scaled value
      delay(15);                           // waits for the servo to get there
}

void stop(void)                    //Stop  
{  
        digitalWrite(E1, LOW);  
        digitalWrite(E2, LOW);  
}  
void advance(char a, char b)         //Move forward  
{  
        analogWrite (E1, a);     //PWM Speed Control  
        digitalWrite(M1, HIGH);  
        analogWrite (E2, b);  
        digitalWrite(M2, HIGH);  
}  
void back_off (char a, char b)         //Move backward  
{  
        analogWrite (E1, a);  
        digitalWrite(M1, LOW);  
        analogWrite (E2, b);  
        digitalWrite(M2, LOW);  
}  
void turn_L (char a, char b)            //Turn Left  
{  
        analogWrite (E1, a);  
        digitalWrite(M1, LOW);  
        analogWrite (E2, b);  
        digitalWrite(M2, HIGH);  
}  
      void turn_R (char a, char b)            //Turn Right  
      {  
        analogWrite (E1, a);  
        digitalWrite(M1, HIGH);  
        analogWrite (E2, b);  
        digitalWrite(M2, LOW);  
      }  
      
      void dance1() {  
        analogWrite(E1, 240);   // turn the LED on (HIGH is the voltage level)  
        digitalWrite(M1, LOW);  
        delay(1000) ;                      // wait for a second  
        digitalWrite(M1, HIGH);  
        delay(1000) ;  
        analogWrite(E1, 0);   // turn the LED on (HIGH is the voltage level)  
      }  
      
  
      void dance2() {  
        analogWrite(E1, 120);   // turn the LED on (HIGH is the voltage level)  
        digitalWrite(M1, LOW);  
        delay(1000) ;                      // wait for a second  
        digitalWrite(M1, HIGH);  
        delay(1000) ;  
        analogWrite(E1, 0);   // turn the LED on (HIGH is the voltage level)  
      } 
 
void loop() {  
//        for(int i = 0;i <64;i ++){
//          leds[i] = CRGB::Black;
//        }
        
        //delay(30); 
        
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        advance(0, 150);  
        turn1();
        delay(875);
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW 
        color_set();
        FastLED.show(); 
        turn2(); 
        stop();  
        analogWrite(E1, 0);
        delay(875);  
      
  
        analogWrite(E1, 120);
        digitalWrite(LED_BUILTIN, HIGH);  
        advance(150, 0);  
        turn1();
        color_set();
        FastLED.show(); 
        delay(875); 
        digitalWrite(LED_BUILTIN, LOW); 
        turn2();
        stop();  
        analogWrite(E1, 0);
        delay(875);  
}
void color_set(){
        if(color_cnt % 5 == 0){
          for(int i = 0; i < NUM_LEDS;i ++){
            leds[i] = CRGB::Blue;
          }
        }
        else if(color_cnt % 5 == 1){
          for(int i = 0; i < NUM_LEDS;i += 2){
            leds[i] = CRGB::Yellow;}
        }
        else if(color_cnt % 5 == 2){
          for(int i = 0; i < NUM_LEDS;i ++){
            leds[i] = CRGB::Purple;}
      }
        else if(color_cnt % 5 == 3){
          for(int i = 0; i < NUM_LEDS;i += 2){
            leds[i] = CRGB::Green;}
        }
        else{
          for(int i = 0; i < NUM_LEDS;i ++){
            leds[i] = CRGB::Red;}
        }
        color_cnt ++;
}
