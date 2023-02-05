#include <FastLED.h>
#define IN A5
#define THRSH 6
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
    if (listen() > THRSH && i > 4){
      //turn_off();
      col_flag = (col_flag + 1) % 3;
      set_color(i);
      make_dance();
      return;
    }
  }
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(1);
  }
  col_flag = (col_flag + 1) % 3;
}

int listen(){
  int vals_mean = 0;
  int for_how_long = 4;
  for(int i = 0; i < for_how_long; i++){
    delay(2);
    vals_mean = vals_mean + (analogRead(IN) / for_how_long);
  }
  Serial.println(vals_mean);
  return vals_mean;
}

void turn_off(){
    for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void loop() {
  if(listen() > THRSH){
    make_dance();
  }
}
