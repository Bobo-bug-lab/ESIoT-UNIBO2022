#ifndef __ROLLER__
#define __ROLLER__

#include <cstring>
#include "serialib.h"
#include "globalSerial.h"
#include "SerialTask.h"

class Roller { 
public:
  Roller();
  void setValue(char mode_now, int value); 
  int getValue();

private:
  int value;
 
};

#endif
