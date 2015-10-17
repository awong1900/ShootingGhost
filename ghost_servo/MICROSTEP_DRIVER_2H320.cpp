#include "MICROSTEP_DRIVER_2H320.h"

bool MICROSTEP_DRIVER_2H320::Begin(int pin_en, int pin_dir, int pin_pul) {
  step_en = pin_en;
  step_dir = pin_dir;
  step_pul = pin_pul;
  step_freq = 1000;

  pinMode(step_en, OUTPUT);
  pinMode(step_dir, OUTPUT);
  // pinMode(step_pul, OUTPUT);

  digitalWrite(step_en, HIGH);
  digitalWrite(step_dir, HIGH);

  return true;
}

bool MICROSTEP_DRIVER_2H320::SetStepOnOff(int onoff) {
  digitalWrite(step_en, onoff);

  return true;
}

bool MICROSTEP_DRIVER_2H320::ChangeStepDir() {
  int dir = digitalRead(step_dir);
  if (dir == CLOCKWISE)
    digitalWrite(step_dir, COUNTERCLOCKWISE);
  else
  digitalWrite(step_dir, CLOCKWISE);

  StepStart();

  return true;
}

bool MICROSTEP_DRIVER_2H320::SetStepDir(int dir) {
  int direct;
  if(dir == CLOCKWISE)
    direct = true;
  else if (dir == COUNTERCLOCKWISE)
    direct = false;
  else
    direct = true;

  digitalWrite(step_dir, direct);

  return true;
}

bool MICROSTEP_DRIVER_2H320::SetStepSpeed(int hz) {
  if (hz > 14000)
    hz = 14000;
  step_freq = hz;
  return true;
}

bool MICROSTEP_DRIVER_2H320::StepStart() {
  //todo lowly start
  tone(step_pul, step_freq);
  return true;
};

bool MICROSTEP_DRIVER_2H320::StepStop() {
  SetStepOnOff(true);
  return true;
}
