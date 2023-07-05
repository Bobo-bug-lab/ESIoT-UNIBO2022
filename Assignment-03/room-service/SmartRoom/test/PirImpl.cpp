#include "PirImpl.h"
#include "Arduino.h"

#define CALIBRATION_TIME_SEC 1

PirImpl::PirImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT); 


  //give the sensor some time to calibrate
  Serial.print("Calibrating sensor... ");
  for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("PIR SENSOR READY.");

  detected = false;
  sync(); 
  delay(50);
} 
  
  //gets pir status
bool PirImpl::isDetected(){
  return detected;
}

void PirImpl::sync(){
  // reads pir value
  detected = (digitalRead(pin) == HIGH);
  updateSyncTime(millis());
}
