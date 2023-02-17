#include <FastLED.h>
#define IN A7 // input analog pin, the one to which the auc is connected
#define DATA_PIN 2
#define CLOCK_PIN 13 
#define NUM_LEDS 30 // number of leds to command on the strip 
#define AMPLIFY 1 // the input will be input^AMPLIFY
int THRSH = 15;


int prev_listen = 0;// will hold the result of the previous call to listen()

int new_listen = 0;// will hold the new result of listen() 

CRGB leds[NUM_LEDS];
CRGB color_template[] = {0xC21ED0/*purple*/,0x0000FF/*blue*/,0xFF4216/*red - orange*/,0xFF7F50/*peach - orange*/,0xFFFF00/*yellow*/,0x3FCD00/*warm green*/,0x00D3FF/*cyan*/};
int to_cycle = sizeof(color_template)/sizeof(color_template[0]); // length of array

int col_flag = 0; // will be in range [0, to_cycle - 1] 
CRGB cur_color;
void setup() {
  FastLED.addLeds<WS2811/*the nodel of led chip*/, DATA_PIN, BRG/*RGB order*/>(leds, NUM_LEDS);
  pinMode(IN, INPUT); // set the input pin as input
  Serial.begin(9600); // start serial so we can later print values for tests
}              
void set_color(int i){// redundant - set leds [0,i-1] to cur_color
  for(int j = 0; j < i + 1; j++){
    leds[j] = cur_color;
    FastLED.show();
  }
}
void make_dance_single(){ // redundant - does make dance but without wave 
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

void make_dance(){ // when called, it will make a wave of color while listening to the input between eaech led and then, only if it wasn't triggered will turn off the leds
  cur_color = color_template[col_flag]; 
  for(int i = 0; i < NUM_LEDS - 1; i++){
    leds[i] = cur_color;
    leds[i+1] = CRGB::Black;
    FastLED.show();
    
    new_listen = listen();
    if(new_listen - prev_listen > THRSH && i > 20){ // if it is mare than 20 leds into the wave and the new listen is over the threshold it will send a wave of a different color over the existing wave
      prev_listen = new_listen;
      col_flag = (col_flag + 1) % to_cycle; // this is how we make sure we don't go out of bounds
      make_dance();
      return;
    }
    prev_listen = new_listen;
  }
  for(int i = 0; i < NUM_LEDS; i++){ // turn off the leds with a wave 
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(3);
  }
  col_flag = (col_flag + 1) % to_cycle; // switch color for next time
}


int listen(){ // will return the mean of for_how_long reads of the aux input tp the power of AMPLIFY
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
