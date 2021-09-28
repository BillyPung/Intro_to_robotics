
#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>
#include <Servo.h>//https://github.com/Jorgen-VikingGod/LEDMatrix

// Change the next defines to match your matrix type and size
#define DATA_PIN            2
#define NUM_LEDS            64
#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B
#define echoPin 4
#define trigPin 5 
// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        8
#define MATRIX_HEIGHT       8
#define MATRIX_TYPE         HORIZONTAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control
int val;
int potpin = 0;
int color_cnt = 0;
long duration; // variable for the duration of sound wave travel
int distance;
Servo myservo;
//CRGB leds[NUM_LEDS];


// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;


uint8_t hue;
int16_t counter;

void setup() {

  
    // put your setup code here, to run once:
    FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(127);
    FastLED.clear(true);
    delay(500);
    FastLED.showColor(CRGB::Red);
    delay(500);
    FastLED.showColor(CRGB::Lime);
    delay(500);
    FastLED.showColor(CRGB::Blue);
    delay(500);
    myservo.attach(9);
    pinMode(LED_BUILTIN, OUTPUT);
    // initialize pins for the motor driver
    int i;
    for (i = 4; i <= 7; i++) {
        pinMode(i, OUTPUT);
    }

}

void loop() {
    // put your main code here, to run repeatedly:
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  rainbow();
  closeToPeople();
}

void closeToPeople() {
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; 
   Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
    if (distance > 200) {
        advance(150, 50);
        delay(30);
        //advance(50, 150);
        turn1();
//        delay(875);
        turn2();
//        delay(875);
        stop();
    } else {
        constrain(distance, 5, 500);
        float speed = map(distance, 5, 500, 255, 30);
        advance(speed, speed);
        delay(300);
    }
}

void led(){

}
void rainbow() {
    int16_t sx, sy, x, y;
    uint8_t h;

    FastLED.clear();

    h = hue;
    if (counter < 1125) {
        // ** Fill LED's with diagonal stripes
        for (x = 0; x < (leds.Width() + leds.Height()); ++x) {
            leds.DrawLine(x - leds.Height(), leds.Height() - 1, x, 0, CHSV(h, 255, 255));
            h += 16;
        }
    } else {
        // ** Fill LED's with horizontal stripes
        for (y = 0; y < leds.Height(); ++y) {
            leds.DrawLine(0, y, leds.Width() - 1, y, CHSV(h, 255, 255));
            h += 16;
        }
    }
    hue += 4;

    if (counter < 125);
    else if (counter < 375)
        leds.HorizontalMirror();
    else if (counter < 625)
        leds.VerticalMirror();
    else if (counter < 875)
        leds.QuadrantMirror();
    else if (counter < 1125)
        leds.QuadrantRotateMirror();
    else if (counter < 1250);
    else if (counter < 1500)
        leds.TriangleTopMirror();
    else if (counter < 1750)
        leds.TriangleBottomMirror();
    else if (counter < 2000)
        leds.QuadrantTopTriangleMirror();
    else if (counter < 2250)
        leds.QuadrantBottomTriangleMirror();

    counter++;
    if (counter >= 2250)
        counter = 0;
    FastLED.show();
}

void advance(char a, char b)         //Move forward  
{
    analogWrite(E1, a);     //PWM Speed Control
    digitalWrite(M1, HIGH);
    analogWrite(E2, b);
    digitalWrite(M2, HIGH);
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
