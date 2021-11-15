#include <FastLED.h>
/* Leds */
#define DATA_PIN 2
#define NUM_LEDS 2
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

//Color shifter
#define COLOR_SHIFT_INTERVAL 1
uint8_t minG = 0;
uint8_t minB = 0;
byte gbShiftMode = 0;
uint8_t G = 255;
uint8_t B = 255;
unsigned long lastColorShift = 0;

CRGB leds[NUM_LEDS];

void colorShifter(){
  if(millis() - lastColorShift >= COLOR_SHIFT_INTERVAL){
    switch (gbShiftMode){
      case 0:
        G -= 1;
        if (G == minG)
        gbShiftMode = 1;
        break;
      case 1:
        G += 1;
        if (G == 255)
          gbShiftMode = 2;
        break;
      case 2:
        B -= 1;
        if (B == minB)
        gbShiftMode = 3;
        break;
      case 3:
        B += 1;
        if (B == 255)
        gbShiftMode = 0;
        break;
      default:
        ;
    }
  lastColorShift = millis();
  fill_solid(leds, NUM_LEDS, CRGB(0, G, B));
  }
}

void setup(){
  pinMode(A5, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  
}
void loop(){
  int value = analogRead(A5)/4;
  
  if (value < 6)
    value = 0;
  if (value > 252)
    value = 255;
    
  analogWrite(3, value);
  Serial.println(value);

  colorShifter();
  FastLED.show(); 
  
}
