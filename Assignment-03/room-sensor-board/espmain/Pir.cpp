#include "Pir.h"
#include "Arduino.h"

#define CALIBRATION_TIME_SEC 1

Pir::Pir(int pin){
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
  delay(50);
} 

  //gets pir status
bool Pir::getPir(){
  detected = (digitalRead(pin) == HIGH);
  return detected;
}