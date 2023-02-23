#include "servo_motor_impl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin){
  this->pin = pin;  
} 

void ServoMotorImpl::on(){
  motor.attach(pin);    
}

void ServoMotorImpl::setPosition(int angle){
  // 500 is 0 degree and 2700 is 180 degree
  motor.write(map(angle , 0, 180, 500, 2700));            
}

void ServoMotorImpl::off(){
  motor.detach();    
}
