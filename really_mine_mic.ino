#include <FastLED.h>
#define IN A7
#define THRSH 700
#define DATA_PIN 2
#define CLOCK_PIN 13
#define NUM_LEDS 20

CRGB leds[NUM_LEDS];

int col_flag = 0;
CRGB cur_color;
void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS);
  pinMode(IN, INPUT);
  Serial.begin(9600);
}              
void set_color(int i){
  if(col_flag == 0){
    cur_color = CRGB::Red;
  }
  else if(col_flag == 1){
    cur_color = CRGB::Blue;
  }
  else{
    cur_color = CRGB::Green;
  }
  for(int j = 0; j < i + 1; j++){
    leds[j] = cur_color;
    FastLED.show();
  }
}

void make_dance(){
  if(col_flag == 0){
    cur_color = CRGB::Red;
  }
  else if(col_flag == 1){
    cur_color = CRGB::Blue;
  }
  else{
    cur_color = CRGB::Green;
  }
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = cur_color;
    FastLED.show();
    if (listen() > THRSH){
      //turn_off();
      col_flag = (col_flag + 1) % 3;
      set_color(i);
    }
  }
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(10);
  }
  col_flag = (col_flag + 1) % 3;
}

int listen(){
  int vals_mean = 0;
  for(int i = 0; i < 10; i++){
    delay(2);
    vals_mean = vals_mean + (analogRead(IN) / 10);
  }
  return vals_mean;
}

void turn_off(){
    for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void loop() {
  
  int vals_mean = 0;
  for(int i = 0; i < 20; i++){
    vals_mean = vals_mean + (analogRead(IN) / 20);
  }
  if(vals_mean > THRSH){
    make_dance();
  }
  else{
    Serial.println(vals_mean);
    Serial.print("    ");
    Serial.println(0);
  }
}
