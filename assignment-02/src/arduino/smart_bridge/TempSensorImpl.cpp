#include "TempSensorImpl.h"
#include "Arduino.h"

TempSensorImpl::TempSensorImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);
}

float TempSensorImpl::getTemp(){
    return temp;
}

void TempSensorImpl::sync(){
    int val;
    // reads pir value
    val = analogRead(pin);
    temp = (1.5 * val) / 306.9 * 100;
}
