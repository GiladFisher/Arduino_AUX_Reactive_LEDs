#include <FastLED.h>
#define IN A7
//#define THRSH 30000
#define THRSH2 20
#define DATA_PIN 2
#define CLOCK_PIN 13
#define NUM_LEDS 30
#define AMPLIFY 1
int THRSH = 15;


int prev_listen = 0;

int new_listen = 0;

CRGB leds[NUM_LEDS];
//CRGB color_template[3][3] = {{CRGB(255 , 0 , 150 ),CRGB(255 /2 , 0 , 150 /2 ), CRGB(255 /3 , 0 , 150 /3 )}};
CRGB color_template[] = {0x7F00FF,0x0000FF/*,0x800080*/,0xFF0000,0xFF7F50/*,0xFFA500*/,0xFFFF00,0x9ACD32/*,0x00FF00*/,0x00CED1,0x00BFFF};
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
  for(int i = 0; i < NUM_LEDS - 1; i++){
    leds[i] = cur_color;
    leds[i+1] = CRGB::Black;
    FastLED.show();
    
    new_listen = listen();
    if(new_listen - prev_listen > THRSH && i > 20){
      prev_listen = new_listen;
      col_flag = (col_flag + 1) % to_cycle;
      set_color(i);
      make_dance();
      return;
    }
    prev_listen = new_listen;
    // if (listen() > THRSH && i > 20){
    //   col_flag = (col_flag + 1) % to_cycle;
    //   set_color(i);
    //   make_dance();
    //   return;
    // }
  }
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(3);
  }
  col_flag = (col_flag + 1) % to_cycle;
}


int listen(){
  int vals_mean = 0;
  int for_how_long = 80;
  for(int i = 0; i < for_how_long; i++){
    //delay(1);
    vals_mean = vals_mean + (analogRead(IN)/ for_how_long);// / for_how_long);
    // if(pow(vals_mean,AMPLIFY) > THRSH){
    //   Serial.println(pow(vals_mean,AMPLIFY));
    //   return pow(vals_mean,AMPLIFY);
    // }
  }
  Serial.println(pow(vals_mean,AMPLIFY));
  return pow(vals_mean,AMPLIFY);
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
  new_listen = listen();
  if(new_listen - prev_listen > THRSH){
    prev_listen = new_listen;
    make_dance();
    //shiftColorOfAll(); delay(5);
  }
  else if(leds[0] != CRGB( 0, 0, 0)){// if the leds didnt turn of last run
    for(int i = 0; i < NUM_LEDS; i++){
      leds[i] = CRGB::Black;
      FastLED.show(); 
    }
  }
  else{
    prev_listen = new_listen;
  }
   

}
