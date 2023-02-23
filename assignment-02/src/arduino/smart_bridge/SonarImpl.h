#ifndef __SONARIMPL__
#define __SONARIMPL__

#include "Sonar.h"
#include "TempSensorImpl.h"

class SonarImpl: public Sonar {
 
public: 
  SonarImpl(int pin_trigger, int pin_echo, int pin_temp);
  void sync();

private:
  double calcDistance();
  int pin_trigger;
  int pin_echo;
  float vs;
  TempSensorImpl* temp_sensor;
};

#endif
