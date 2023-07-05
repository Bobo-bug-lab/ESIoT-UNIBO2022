#include "Led.h"
#include <windows.h>
#include <iostream>

Led::Led(){
  std::cout << "Led created"<< std::endl;
  this->status = 0;
}

void Led::switchOn(char mode_now){
  //do something
  char messageBody[10] ="\0";
  messageBody[0] = mode_now; // 将单个字符赋值给数组的第一个元素
  messageBody[1] = '\0'; // 确保以空字符结尾
  strcat(messageBody, "L1");
  strcat(messageBody, "\n");

  // Write the string on the serial device
  globalSerial.writeString(messageBody);

  std::cout << "Serial output message: "<< messageBody << std::endl;
  std::cout << "Turn led on"<< std::endl;
}

void Led::switchOff(char mode_now){
  char messageBody[10] = "";
  messageBody[0] = mode_now; // 将单个字符赋值给数组的第一个元素
  messageBody[1] = '\0'; // 确保以空字符结尾
  strcat(messageBody, "L0");
  strcat(messageBody, "\n");

  // Write the string on the serial device
  globalSerial.writeString(messageBody);

  std::cout << "LED Serial output message: "<< messageBody << std::endl;
  std::cout << "Turn led off"<< std::endl;
}

bool Led::getStatus(){
  //do something
  //only vaild when under control of PHONE
  this->status = getLightFromSerial();
  std::cout << "Led get status "<< this->status << std::endl;
  return this->status;
}

