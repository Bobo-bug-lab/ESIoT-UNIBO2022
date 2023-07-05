#ifndef __LED__
#define __LED__

#include <cstring>
//#include "Light.h"
#include "serialib.h"
#include "globalSerial.h"
#include "SerialTask.h"


class Led{ 
public:
  Led();
  void switchOn(char mode_now);
  void switchOff(char mode_now);
  bool getStatus();
 
private:
  bool status;
  
};

#endif
