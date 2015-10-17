#ifndef MICROSTEP_DRIVER_2H320_H
#define MICROSTEP_DRIVER_2H320_H
#include <Arduino.h>
#define COUNTERCLOCKWISE  0x00
#define CLOCKWISE         0x01

class MICROSTEP_DRIVER_2H320 {
public:
  bool Begin(int pin_en, int pin_dir, int pin_pul);
  bool SetStepOnOff(int onoff);
  bool ChangeStepDir();
  bool SetStepDir(int dir);
  bool SetStepSpeed(int hz);
  bool StepStart();
  bool StepStop();

private:
  int step_en;
  int step_dir;
  int step_pul;
  int step_freq;
};

#endif //MICROSTEP_DRIVER_2H320_H
