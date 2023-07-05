#include "RoomTask.h"
#include <iostream>
// #include "WaterLevelTask.h"

// max time the light can be on
#define MAX_TIME_LIGHT_ON 5000
DataForLight dataForLight;
DataForNode dataForNode;

//bool phoneControlSwitch = 0;

RoomTask::RoomTask(){

}
  
void RoomTask::init(int period){
  //Serial.begin(9600);
  Task::init(period);
  led = new Led(); 
  roller = new Roller();
  threshold = 10.0; // light threshold
  state = OFF;
  modeChar = 's';
  controlMode = AUTO_MODE;
  timer = new Timer();
 
}
  
void RoomTask::tick(){
  int hour_now = timer->getCurrentHour();
  double volt_light_detected;
  dataForLight = getDataForLight();
  controlMode = switchControlMode(dataForLight.dashboardSwitch,0);
  //controlMode = switchControlMode(dataForLight.dashboardSwitch,getControlFromSerial());

  switch (controlMode)
  {
  case PC_MODE:
  
    std::cout << "PC_MODE running" <<std::endl;
    modeChar = 'd';
    if(dataForLight.lightSwitchNode != led->getStatus())
    {
      if(dataForLight.lightSwitchNode)  led->switchOn(modeChar);    //execute when changing
        else if (!dataForLight.lightSwitchNode) led->switchOff(modeChar);
    }

    if(dataForLight.rollerSliderValueNode != roller->getValue()) //execute when changing
    {
      roller->setValue(modeChar,dataForLight.rollerSliderValueNode);
    }
    
    //send order of light_status and roller_tatus from Arduino
    //get data of light_status and roller_status from Arduino
    
    //dataForNode.lightStatus = dataForLight.lightSwitchNode;// get status from arduino instead of node, or a flag from arduino
    //dataForNode.rollerStatus = dataForLight.rollerSliderValueNode;//these two lines of codes only for testing

    dataForNode.lightStatus = led->getStatus();
    dataForNode.rollerStatus = roller->getValue();
    
    //std::cout << "lightStatus on PC: " << dataForNode.lightStatus << std::endl;

    //get light and roller status from the arduino
    break;

  case PHONE_MODE:  //phone give back order only in PHONE_MODE, give back status in all 3 modes.
     
    modeChar = 'a';
    std::cout << "PHONE_MODE running " <<std::endl;
    // get data of light status and roller status from Arduino
    dataForNode.lightStatus = led->getStatus();
    dataForNode.rollerStatus = roller->getValue();// data from arduino
    // send data to node-red

   break;
  
  case AUTO_MODE:

    modeChar = 's';
    std::cout << "AUTO_MODE running " <<std::endl;
    
    if( hour_now>=8 && hour_now<19 && dataForLight.detectStatus == 1 && roller->getValue()!=0)    roller->setValue(modeChar,0);
    if( (hour_now>=19||hour_now<8) && dataForLight.detectStatus == 0 && roller->getValue()!=100)   roller->setValue(modeChar,100);

    switch (state){// this is the state for light    
      case OFF:
        std::cout << "Light State OFF"<< std::endl;
        // check if people detected
        if (dataForLight.detectStatus){ 
          std::cout << "People detected"<< std::endl;
          volt_light_detected = dataForLight.lightValue;

          // checks light level
          if (volt_light_detected < threshold) {
            std::cout << "Room light is turning on..."<< std::endl;
            time_when_light_turned_on = millis();
            state = SWITCHING_ON;
          }
        }
        break;

      case SWITCHING_ON:
        led->switchOn(modeChar);
        std::cout << "Room light is ON"<< std::endl;
        state = ON;
        break;

      case ON:
        volt_light_detected = dataForLight.lightValue;

        // checks time, light level and if people detected
        if ( timer->check_time_since(time_when_light_turned_on, MAX_TIME_LIGHT_ON) && (!dataForLight.detectStatus || volt_light_detected > threshold) ){
          state = SWITCHING_OFF;
          std::cout << "Room light is turning off..."<< std::endl;
        }
        break;

      case SWITCHING_OFF:
        led->switchOff(modeChar);
        std::cout << "Room light is OFF"<< std::endl;
        state = OFF;
        break;
      }

    dataForNode.lightStatus = led->getStatus();
    dataForNode.rollerStatus = roller->getValue();// data from arduino
    break;
  }
}

ControlMode RoomTask::switchControlMode(bool PC, bool Phone){
   ControlMode mode = AUTO_MODE;
   if (Phone) mode = PHONE_MODE;
   if (PC) mode = PC_MODE;
   //pc(dashbroad)_MODE priority > PHONE_MODE
   return mode;
}

struct DataForNode getDataForNode(){
    return dataForNode;
}

