#include <Arduino.h>
#include "MICROSTEP_DRIVER_2H320.h"
int servo_en = 4;
int servo_di = 5;
int servo_sp = 6;

int left_button = 2;
int right_button = 3;

MICROSTEP_DRIVER_2H320 step;

void setup() {
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  step.Begin(4,5,6);
  step.StepStart();
}

void loop() {
  if (digitalRead(left_button) == HIGH || digitalRead(right_button) == HIGH) {
    step.ChangeStepDir();
  }
}
