#include "SmartLightingTask.h"
#include "PirImpl.h"
#include "LDImpl.h"
#include "Arduino.h"
#include "WaterLevelTask.h"

// max time the light can be on
#define MAX_TIME_LIGHT_ON 5000

SmartLightingTask::SmartLightingTask(int pin_led,int pin_pir,int pin_light_sensor){
  this->pin_led = pin_led;
  this->pin_pir = pin_pir;
  this->pin_light_sensor = pin_light_sensor;    
}
  
void SmartLightingTask::init(int period){
  //Serial.begin(9600);
  Task::init(period);
  led = new Led(pin_led); 
  pir = new PirImpl(pin_pir);
  light_detector = new LDImpl(pin_light_sensor);
  threshold = 1.0; // light threshold
  state = OFF;
  timer = new Timer();
}
  
void SmartLightingTask::tick(){
  pir->sync();
  light_detector->sync();
  double volt_light_detected;
  if(send_flag()){
   switch (state){    
    case OFF:

      // check if people detected
      if (pir->isDetected()){ 
        Serial.println("pedestain is detected");
        volt_light_detected = light_detector->light_detect();

        // checks light level
        if (volt_light_detected < threshold) {
          Serial.println("bridge light is turning on...");
          time_when_light_turned_on = millis();
          state = SWITCHING_ON;
        }
      }
      break;

    case SWITCHING_ON:
      led->switchOn();
      Serial.println("bridge light is ON");
      state = ON;
      break;

    case ON:
      volt_light_detected = light_detector->light_detect();

      // checks time, light level and if people detected
      if ( timer->check_time_since(time_when_light_turned_on, MAX_TIME_LIGHT_ON) && (!pir->isDetected() || volt_light_detected > threshold) ){
        state = SWITCHING_OFF;
        Serial.println("bridge light is turning off...");
      }
      break;

    case SWITCHING_OFF:
      led->switchOff();
      Serial.println("bridge light is OFF");
      state = OFF;
      break;
    }
  }
}
