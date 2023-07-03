#include "Led.h"
#include <windows.h>
#include <iostream>

Led::Led(){
  std::cout << "Led created"<< std::endl;
}

void Led::switchOn(){
  //do something
  this->ledToArduino = 1;
  std::cout << "Turn led on"<< std::endl;
}

void Led::switchOff(){
  //do something
  std::cout << "Turn led off"<< std::endl;
}

bool Led::getStatus(){
  //do something
  //only vaild when under control of PHONE
  std::cout << "Led get status"<< std::endl;
  return 1;
}

bool Led::getLedToArduino(){

  return this->ledToArduino;
}

