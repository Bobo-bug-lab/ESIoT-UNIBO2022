#include "LightTask.h"
#include "RollerTask.h"
#include <iostream>
// #include "WaterLevelTask.h"

// max time the light can be on
#define MAX_TIME_LIGHT_ON 5000
DataForLight dataForLight;
DataForNode dataForNode;
DataForRoller dataForRoller;

bool phoneControlSwitch = 0;

LightTask::LightTask(){

}
  
void LightTask::init(int period){
  //Serial.begin(9600);
  Task::init(period);
  led = new Led(); 
  roller = new Roller();
  threshold = 10.0; // light threshold
  state = OFF;
  controlMode = AUTO_MODE;
  timer = new Timer();
}
  
void LightTask::tick(){
  int hour_now = timer->getCurrentHour();
  double volt_light_detected;
  dataForLight = getDataForLight();
    // std::cout << "dashboardSwitch: " << dataForLight.dashboardSwitch << std::endl;
    // std::cout << "detectStatus: " << dataForLight.detectStatus << std::endl; 
    // std::cout << "lightSwitchNode: " << dataForLight.lightSwitchNode << std::endl; 
    // std::cout << "lightValue: " << dataForLight.lightValue << std::endl;
    // std::cout << "rollerSliderValueNode: " << dataForLight.rollerSliderValueNode << std::endl;
  controlMode = switchControlMode(dataForLight.dashboardSwitch,phoneControlSwitch);

  switch (controlMode)
  {
  case PC_MODE:
  
    std::cout << "PC_MODE running " <<std::endl;
    modechar = 's';
    if(dataForLight.lightSwitchNode)  led->switchOn();
      else if (!dataForLight.lightSwitchNode) led->switchOff();
    roller->setValue(dataForLight.rollerSliderValueNode);
    //send order of light status and roller status from Arduino
    //get data of light status and roller status from Arduino
    
    dataForNode.lightStatus = dataForLight.lightSwitchNode;// get status from arduino instead of node, or a flag from arduino
    dataForNode.rollerStatus = dataForLight.rollerSliderValueNode;//these two lines of codes only for testing
    
    //std::cout << "lightStatus on PC: " << dataForNode.lightStatus << std::endl;

    //get light and roller status from the arduino
    break;

  case PHONE_MODE:  //phone give back order only in PHONE_MODE, give back status in all 3 modes.  Only give o

    std::cout << "PHONE_MODE running " <<std::endl;

    // get data of light status and roller status from Arduino
    dataForNode.lightStatus = led->getStatus();
    dataForNode.rollerStatus = roller->getStatus();
    // send data to node-red
    //dataForNode.lightStatus = data from arduino
    //dataForNode.rollerStatus = data from arduino
  
   break;
  
  case AUTO_MODE:
    std::cout << "AUTO_MODE running " <<std::endl;
    switch (state){    
      case OFF:
        // check if people detected
        if (dataForLight.detectStatus){ 
          std::cout << "pedestain is detected"<< std::endl;
          volt_light_detected = dataForLight.lightValue;

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


    break;
  }
}

void LightTask::setDataForRoller(int value){

    dataForRoller.mode = controlMode;
    dataForRoller.manualRollerValue = value;
    dataForRoller.detectStatus = dataForLight.detectStatus;
}

ControlMode LightTask::switchControlMode(bool PC, bool Phone){
   ControlMode mode = AUTO_MODE;
   if (Phone) mode = PHONE_MODE;
   if (PC) mode = PC_MODE;
   //pc(dashbroad)_MODE priority > PHONE_MODE
   return mode;
}

struct DataForNode getDataForNode(){
    return dataForNode;
}

struct DataForRoller getDataForRoller(){
    return dataForRoller;
}

  // void LightTask::setDataForNode(){
  //     dataForNode.dashboardSwitch = this->getDashboardSwitch();
  //     dataForNode.detectStatus = this->getDetectStatus();
  // }
