#include "ButtonImpl.h"
#include "Arduino.h"

ButtonImpl::ButtonImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);  
  sync();   
} 
  
bool ButtonImpl::isPressed(){
  // bool p = pressed;
  // delay (100);
  // if (p==pressed) return (p);
  return pressed;

}

void ButtonImpl::sync(){
  pressed = digitalRead(pin) == HIGH;
  updateSyncTime(millis());
}
