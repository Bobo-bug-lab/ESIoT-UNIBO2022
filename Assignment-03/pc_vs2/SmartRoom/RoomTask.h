#pragma once
#include "Task.h"
#include "Led.h"
#include "Roller.h"
#include "Timer.h"
#include "getC2Dms.h"
#include "SerialTask.h"

enum ControlMode { AUTO_MODE, PC_MODE, PHONE_MODE };

class RoomTask: public Task {
  Led* led;
  Roller* roller;
  Timer* timer;
  enum { ON, OFF, SWITCHING_ON, SWITCHING_OFF} state;
  ControlMode controlMode;

private:

  // time when light turned on
  //void setDataForRoller(int value);
  long time_when_light_turned_on;
  char modeChar;

public:

  RoomTask();  
  void init(int period);  
  void tick();
  ControlMode switchControlMode(bool PC, bool Phone);
  double threshold;
  //void setDataForNode();
  
};

struct DataForNode getDataForNode();

struct DataForNode {
    bool phoneControl = 0;
    bool lightStatus = 0;
    int rollerStatus = 0;
};

//struct DataForRoller getDataForRoller();
// struct DataForRoller {
//     ControlMode mode;
//     bool detectStatus = 0;
//     int manualRollerValue = 0;
// };


    // bool detectStatus = 0;
    // int lightValue = 0;
    // bool dashboardSwitch = 0;
    // int lightSwitchNode = 0;
    // int rollerSliderValueNode = 0;