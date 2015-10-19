#include <Arduino.h>
#include "MICROSTEP_DRIVER_2H320.h"
#include <Adafruit_NeoPixel.h>
#include "matrix.h"

#define STATE_START       0x00
#define STATE_STAND       0x01
#define STATE_LOW_SPEED   0x02
#define STATE_HIGH_SPEED  0x03
#define STATE_WINNER      0x04

#define SPEED_LOW   5000
#define SPEED_HIGH  10000

#define SHOOTING_NUMBER 1
#define NUMPIXELS 256

int state = STATE_START;
int old_state = STATE_START;
int shooting_count = 0;

int step_en = 4;
int step_dir = 5;
int step_freq = 6;

int left_button = 2;
int right_button = 3;
int shooting_button1 = A1;
int shooting_button2 = A2;

int led_display = 7;
int reset_button = 8;

MICROSTEP_DRIVER_2H320 step;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, led_display, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(shooting_button1, INPUT_PULLUP);
  pinMode(shooting_button2, INPUT_PULLUP);
  step.Begin(step_en,step_dir,step_freq);
  pixels.begin();
  pixels.setBrightness(50);
}

void loop() {
  if (digitalRead(left_button) == HIGH || digitalRead(right_button) == HIGH) {
    // delay(70);
    // if(digitalRead(left_button) == HIGH || digitalRead(right_button) == HIGH)
      step.ChangeStepDir();
      delay(300);
  }

  if (digitalRead(reset_button == HIGH)) {
      delay(70);
      if (digitalRead(reset_button == HIGH))
        // state = STATE_START;
        ;
  }



  if(state == STATE_STAND || state == STATE_LOW_SPEED || state == STATE_HIGH_SPEED) {
    if (digitalRead(shooting_button1) == HIGH || digitalRead(shooting_button2) == HIGH) {
        // delay(10);
        // if (digitalRead(shooting_button1 == HIGH) || digitalRead(shooting_button2 == HIGH)) {
          shooting_count++;
          Serial.print("shooting_count ");Serial.println(shooting_count);
          checkShootingCount();
          cry();
          delay(100);
        // }
    }
  }

  Serial.print("state ");Serial.println(state);
  switch (state) {
    case STATE_START:
      start_shooting_ghost();
      break;
    case STATE_STAND:
      ghost_stand();
      break;
    case STATE_LOW_SPEED:
      ghost_low_speed();
      break;
    case STATE_HIGH_SPEED:
      ghost_high_speed();
      break;
  }
}

void start_shooting_ghost() {
  step.StepStop();
  state = STATE_STAND;
  shooting_count = 0;

  matrix_clear_all();
  matrix_cry();
  matrix_display();

  delay(1000);
  matrix_clear_all();
  matrix_smile();
  matrix_display();
}

void ghost_stand() {
  step.StepStop();
}

void ghost_low_speed() {
  // step.StepStop();
  // step.SetStepSpeed(SPEED_LOW);
  // step.StepStart();
}

void ghost_high_speed() {
  // step.StepStop();
  // step.SetStepSpeed(SPEED_HIGH);
  // step.StepStart();
}

void checkShootingCount() {
  if(shooting_count == SHOOTING_NUMBER) {
    shooting_count = 0;
    changeState();
  }
}

void changeState() {
  if (state == STATE_STAND) {
    state = STATE_LOW_SPEED;
    step.SetStepSpeed(SPEED_LOW);
    step.StepStart();
  }
  else if (state == STATE_LOW_SPEED) {
    state = STATE_HIGH_SPEED;
    // step.StepStop();
    step.SetStepSpeed(SPEED_HIGH);
    step.StepStart();
  }
  else if (state == STATE_HIGH_SPEED) {
    state = STATE_STAND;
    step.StepStop();
  }
  else
    state = STATE_START;
}

// matrix display -----------//
void matrix_smile(){
  for(long i=0;i<26;i++){
    pixels.setPixelColor(MATRIX_SMILE[i], pixels.Color(0,150,0));
  }
}

void matrix_cry(){
  for(long i=0;i<26;i++){
    pixels.setPixelColor(MATRIX_CRY[i], pixels.Color(150,0,0));
  }
}

//display

//1. clearall
void matrix_clear_all() {
  for(long i=0;i<255;i++){
    pixels.setPixelColor(i, 0);
  }
}
//2. line smile or cry

//3. smile score
void matrix_score_first_number() {
  for(long i=0;i<26;i++){
    pixels.setPixelColor(MATRIX_CRY[i], pixels.Color(150,0,0));
  }
}
void matrix_score(int score) {

}
//3. line winner

//4. display
void matrix_display() {
  pixels.show();
}

void cry() {
  matrix_clear_all();
  matrix_cry();
  matrix_display();

  delay(500);
  matrix_clear_all();
  matrix_smile();
  matrix_display();
}
