#include <FastLED.h>
#define IN A5
#define THRSH 2
#define DATA_PIN 2
#define CLOCK_PIN 13
#define NUM_LEDS 30


CRGB leds[NUM_LEDS];
//CRGB color_template[3][3] = {{CRGB(255 , 0 , 150 ),CRGB(255 /2 , 0 , 150 /2 ), CRGB(255 /3 , 0 , 150 /3 )}};
CRGB color_template[] = {0x7F00FF,0x0000FF,0x800080,0xFF0000,0xFF7F50,0xFFA500,0xFFFF00,0x9ACD32,0x00FF00,0x00CED1,0x00BFFF};
int to_cycle = sizeof(color_template)/sizeof(color_template[0]);

int col_flag = 0;
CRGB cur_color;
void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS);
  pinMode(IN, INPUT);
  Serial.begin(9600);
}              
void set_color(int i){
  for(int j = 0; j < i + 1; j++){
    leds[j] = cur_color;
    FastLED.show();
  }
}
void make_dance_single(){
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
    if(i > 0);
  }

  
}

void make_dance(){
  cur_color = color_template[col_flag];
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = cur_color;
    FastLED.show();
    if (listen() > THRSH && i > 15){
      //turn_off();
      col_flag = (col_flag + 1) % to_cycle;
      set_color(i);
      make_dance();
      return;
    }
  }
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(6);
  }
  col_flag = (col_flag + 1) % to_cycle;
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

void shiftColorOfAll(){
  col_flag = (col_flag + 1) % to_cycle;
  cur_color = color_template[col_flag];
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = cur_color;
  }
  FastLED.show();
}

void loop() {
  if(listen() > THRSH){
    make_dance();
    //shiftColorOfAll(); delay(5);
  }

}
