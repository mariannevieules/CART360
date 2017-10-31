#include <stdint.h>
#include "TouchScreen.h"
#include <Stepper.h>

/////////////////////////////
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif
/////////////////////////////

//#define YM A0
//#define XP A1
//#define YP A2
//#define XM A3

#define XM A0
#define YP A1
#define XP A2
#define YM A3

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 7);

///////////////////////////// 
#define PIN_LED_1 2
#define PIN_LED_2 3

Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(60, PIN_LED_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(60, PIN_LED_2, NEO_GRB + NEO_KHZ800);
/////////////////////////////
                        
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup() {

/////////////////////////////
  strip_1.begin();
  strip_1.show(); // Initialize all pixels to 'off'

  strip_2.begin();
  strip_2.show();

  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
/////////////////////////////
   
  Serial.begin(9600);
}

void loop() {
  TSPoint p = ts.getPoint();

  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
  
  /*  ____________________________________
   *  |          |           |           |
   *  |  zone 2  |  zone 4   |   zone 6  |
   *  |__________|___________|___________|
   *  |          |           |           |
   *  |  zone 1  |  zone 3   |   zone 5  |
   *  |__________|___________|___________|
  */

  if(p.z > 0) {    
    if((p.x > 0 && p.x < 341) && (p.y < 420)) {
      Serial.println("we are in the first zone !");

      
      animationWithPressure(strip_1.Color(255, 255, 255, 255), 50);
      animationWithPressure(strip_2.Color(255, 255, 255, 255), 50);
    }

    else if((p.x>0&&p.x<341)&&(p.y>419)) {
      Serial.println("we are in the second zone !");
      animationWithPressure(strip_1.Color(255, 255, 255, 255), 50);
      animationWithPressure(strip_2.Color(255, 255, 255, 255), 50);
    }
      
    else if((p.x>340&&p.x<682)&&(p.y<420)) {
      Serial.println("we are in the third zone !");
      animationWithPressure(strip_1.Color(255, 255, 255, 255), 50);
      animationWithPressure(strip_2.Color(255, 255, 255, 255), 50);
    }

    else if((p.x>340&&p.x<682)&&(p.y>419)) {
      Serial.println("we are in the fourth zone !");
      animationWithPressure(strip_1.Color(255, 255, 255, 255), 50);
      animationWithPressure(strip_2.Color(255, 255, 255, 255), 50);
    }

    else if((p.x>682)&&(p.y<420)) {
      Serial.println("we are in the fifth zone !");
      animationWithPressure(strip_1.Color(255, 255, 255, 255), 50);
      animationWithPressure(strip_2.Color(255, 255, 255, 255), 50);
    }

    else if((p.x>682)&&(p.y>419)) {
      Serial.println("we are in the sixth zone !");
      animationWithPressure(strip_1.Color(255, 255, 255, 255), 50);
      animationWithPressure(strip_2.Color(255, 255, 255, 255), 50);
    }
  }

  else {
     Serial.println("there is no pressure at all !");
     animationNoPressure(strip_1.Color(255, 255, 255, 255), 50);
     animationNoPressure(strip_2.Color(255, 255, 255, 255), 50);
  }
}

// Fill the dots one after the other with a color
void animationNoPressure(uint32_t c, uint8_t wait) {  
  for(uint16_t i=0; i<strip_1.numPixels(); i++) {
    if(i<60) { 
      if(i<10) {
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    
      if(i>=10 && i<20) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    
      if(i>=20 && i<30) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    
      if(i>=30 && i<40) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    
      if(i>=40 && i<50) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    
      if(i>=50 && i<=59) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    }
  }

  for(int j=49;j<=59;j++) {
    strip_1.setPixelColor(j, (0,0,0));
    strip_2.setPixelColor(j, (0,0,0));
    strip_1.show();
    strip_2.show();
    delay(wait);
  }

  for(int j=59;j>=49;j--) {
    strip_1.setPixelColor(j, c);
    strip_2.setPixelColor(j, c);
    strip_1.show();
    strip_2.show();
    delay(wait);
  }

  for(uint16_t i=strip_1.numPixels()-1; i>=1;i--) { 
    if(i>=50) {
      strip_1.setPixelColor(i, (0,0,0));
      strip_2.setPixelColor(i, (0,0,0));
      strip_1.setPixelColor(i-10, c);
      strip_2.setPixelColor(i-10, c);
      strip_1.show();
      strip_2.show();
      delay(wait);
    }
      
    if(i<=49 && i>=40) {
      strip_1.setPixelColor(i, (0,0,0));
      strip_2.setPixelColor(i, (0,0,0));
      strip_1.setPixelColor(i-10, c);
      strip_2.setPixelColor(i-10, c);
      strip_1.show();
      strip_2.show();
      delay(wait);
    }

    if(i<=39 && i>=30) {
      strip_1.setPixelColor(i, (0,0,0));
      strip_2.setPixelColor(i, (0,0,0));
      strip_1.setPixelColor(i-10, c);
      strip_2.setPixelColor(i-10, c);
      strip_1.show();
      strip_2.show();
      delay(wait);
    }
    
    if(i<=29 && i>=20) {
      strip_1.setPixelColor(i, (0,0,0));
      strip_2.setPixelColor(i, (0,0,0));
      strip_1.setPixelColor(i-10, c);
      strip_2.setPixelColor(i-10, c);
      strip_1.show();
      strip_2.show();
      delay(wait);
    }

    if(i<=19 && i>=10) {
      strip_1.setPixelColor(i, (0,0,0));
      strip_2.setPixelColor(i, (0,0,0));
      strip_1.setPixelColor(i-10, c);
      strip_2.setPixelColor(i-10, c);
      strip_1.show();
      strip_2.show();
      delay(wait);
    }

    if(i<=9 && i>=0) {
      strip_1.setPixelColor(i, (0,0,0));
      strip_2.setPixelColor(i, (0,0,0));
      strip_1.setPixelColor(i-10, c);
      strip_2.setPixelColor(i-10, c);
      strip_1.show();
      strip_2.show();
      delay(wait);
    }
  }
}

void animationWithPressure(uint32_t c, uint8_t wait) {  
  for(uint16_t i=0; i<strip_1.numPixels(); i++) {
    if(i<60) { 
      if(i<10) {
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    
      if(i>=10 && i<20) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    
      if(i>=20 && i<30) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    
      if(i>=30 && i<40) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    
      if(i>=40 && i<50) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
      
      if(i>=50 && i<=59) {
        strip_1.setPixelColor(i-10, (0,0,0));
        strip_2.setPixelColor(i-10, (0,0,0));
        strip_1.setPixelColor(i, c);
        strip_2.setPixelColor(i, c);
        strip_1.show();
        strip_2.show();
        delay(wait);
      }
    }
  }

  for(int j=49;j<=59;j++) {
    strip_1.setPixelColor(j, (0,0,0));
    strip_2.setPixelColor(j, (0,0,0));
    strip_1.show();
    strip_2.show();
    delay(wait);
  }
}

void movement_motors(int zone, int motor_number, int duration,int rotation_sense) {
  // if we are in the first zone 
    // the first stepper pulls for the duration parameter then stops
    // the second stepper pulls for the duration parameter then stops
    // the third stepper pulls for the duration parameter then stops
    // the fourth stepper pulls for the duration parameter then stops
    // the fifth stepper pulls for the duration parameter then stops
    // the sixth stepper pulls for the duration parameter then stops

  // if we are in the second zone 
    // the third stepper pulls for the duration parameter then stops
    // the first stepper pulls for the duration parameter then stops
    // the fifth stepper pulls for the duration parameter then stops
    // the fourth stepper pulls for the duration parameter then stops
    // the second stepper pulls for the duration parameter then stops
    // the sixth stepper pulls for the duration parameter then stops

  // if we are in the third zone
    // the fourth stepper pulls for the duration parameter then stops
    // the sixth stepper pulls for the duration parameter then stops
    // the third stepper pulls for the duration parameter then stops
    // the fifth stepper pulls for the duration parameter then stops  
    
  // if we are in the fourth zone 
    // the fifth stepper pulls for the duration parameter then stops
    // the third stepper pulls for the duration parameter then stops
    // the second stepper pulls for the duration parameter then stops
    // the first stepper pulls for the duration parameter then stops
    // the second stepper pulls for the duration parameter then stops    
    // the sixth stepper pulls for the duration parameter then stops

  // if we are in the fifth zone
    // the second stepper pulls for the duration parameter then stops
    // the fourth stepper pulls for the duration parameter then stops
    // the first stepper pulls for the duration parameter then stops
    // the fourth stepper pulls for the duration parameter then stops
    // the fifth stepper pulls for the duration parameter then stops

  // if we are in the sixth zone
    // the sixth stepper pulls for the duration parameter then stops
    // the fifth stepper pulls for the duration parameter then stops
    // the second stepper pulls for the duration parameter then stops
    // the third stepper pulls for the duration parameter then stops
}












