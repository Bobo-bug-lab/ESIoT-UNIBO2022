#ifndef __ROLLER__
#define __ROLLER__

#include "SerialPort.h"

class Roller { 
public:
  Roller();
  void setValue(int value); 
  int getStatus();
  int getRollerToArduino();

private:
  int rollerToArduino;
 
};

#endif
