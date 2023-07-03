#ifndef __LED__
#define __LED__

#include "Light.h"
#include "SerialPort.h"

class Led: public Light { 
public:
  Led();
  void switchOn();
  void switchOff();
  void getLedToArduino();    
  bool getStatus();
 
private:
  bool ledToArduino;
};

#endif
