#include <Adafruit_NeoPixel.h>
#include "matrix.h"

#define PIN            8
#define NUMPIXELS      256

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  pixels.begin();
  pixels.setBrightness(10);
}

void loop() {
  print_smile();
  delay(1000);
  print_cry();
  delay(1000);
}


void print_in_use(){
  for(long i=0;i<255;i++){
    pixels.setPixelColor(i, 0);
  }
  for(long i=0;i<78;i++){
    pixels.setPixelColor(MATRIX_IN_USE[i], pixels.Color(150,0,0));
  }

  pixels.show();
}

void print_free(){
  for(long i=0;i<255;i++){
    pixels.setPixelColor(i, 0);
  }
  for(long i=0;i<67;i++){
    pixels.setPixelColor(MATRIX_FREE[i], pixels.Color(0,150,0));
  }
  pixels.show();
}

void print_smile(){
  for(long i=0;i<255;i++){
    pixels.setPixelColor(i, 0);
  }
  for(long i=0;i<26;i++){
    pixels.setPixelColor(MATRIX_SMILE[i], pixels.Color(0,150,0));
  }

  pixels.show();
}

void print_cry(){
  for(long i=0;i<255;i++){
    pixels.setPixelColor(i, 0);
  }
  for(long i=0;i<26;i++){
    pixels.setPixelColor(MATRIX_CRY[i], pixels.Color(150,0,0));
  }

  pixels.show();
}
