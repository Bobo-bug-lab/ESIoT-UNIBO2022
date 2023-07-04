#include "Roller.h"
#include <windows.h>
#include <iostream>

Roller::Roller(){
  std::cout << "Roller created"<< std::endl;
  this->value = 0;
}

void Roller::setValue(char mode_now, int value){
  char messageBody[10] ="\0";
  char newValue[4] = "\0"; 
  sprintf(newValue, "%03d", value); // 3 numbers char
  messageBody[0] = mode_now; // 将单个字符赋值给数组的第一个元素
  messageBody[1] = '\0'; // 确保以空字符结尾
  strcat(messageBody, "R");
  strcat(messageBody, newValue);
  strcat(messageBody, "\n");

  // Write the string on the serial device
  globalSerial.writeString(messageBody);

  std::cout << "roller Serial output message: "<< messageBody << std::endl;
  std::cout << "Setting roller value: "<< value << std::endl;

}

int Roller::getValue(){
  //do something
  //vaild in all status
  this->value = getRollerFromSerial();
  std::cout << "Roller get status "<< this->value << std::endl;
  return this->value;
}

