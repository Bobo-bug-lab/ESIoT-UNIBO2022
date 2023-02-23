#include "PotImpl.h"
#include "Arduino.h"

PotImpl::PotImpl(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);
}

PotImpl::getValue(){
    return analogRead(pin);
}