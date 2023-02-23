#include "SonarImpl.h"
#include "Arduino.h"

SonarImpl::SonarImpl(int pin_trigger, int pin_echo, int pin_temp){
  this->pin_trigger = pin_trigger;
  this->pin_echo = pin_echo;
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_echo, INPUT);
  float vs = 0;
  temp_sensor = new TempSensorImpl(pin_temp);
} 
  
  //calculate distance
double SonarImpl::calcDistance(){
  temp_sensor->sync();
  vs = 331.5 + 0.6 * temp_sensor->getTemp();

  /* send impulse */
  digitalWrite(pin_trigger,LOW);
  delayMicroseconds(3);
  digitalWrite(pin_trigger,HIGH);
  delayMicroseconds(5);
  digitalWrite(pin_trigger,LOW);
  
  /* receive echo */
  long tUS = pulseInLong(pin_echo, HIGH);

  double t = tUS / 1000.0 / 1000.0 / 2;
  distance = t*vs;
  return distance;
}

void SonarImpl::sync(){
  // reads Sonar value
  distance = calcDistance();
  updateSyncTime(millis());
}
