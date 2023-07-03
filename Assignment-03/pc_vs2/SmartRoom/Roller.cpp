#include "Roller.h"
#include <windows.h>
#include <iostream>

Roller::Roller(){
  std::cout << "Roller created"<< std::endl;
}

void Roller::setValue(int value){
  //do something

  std::cout << "Setting roller value: "<< value << std::endl;
}

int Roller::getStatus(){
  //do something
  //only vaild when under control of PHONE
  std::cout << "Roller get status"<< std::endl;
  return 1;
}

int Roller::getRollerToArduino(){
  return this->rollerToArduino;
}

