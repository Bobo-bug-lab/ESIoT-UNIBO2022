#include "SerialTask.h"
#include "SerialTask.h"

using namespace std;

DataForRoller data;

RollerTask::RollerTask() {

}

void RollerTask::init(int period) {
    //Serial.begin(9600);
    Task::init(period);
    roller = new Roller();
    timer = new Timer();
    data = getDataForRoller();
    ControlMode controlMode = AUTO_MODE;
}

void RollerTask::tick() {
    //尚未写好 roller->sync();
    int hour_now = timer->getCurrentHour();
    data = getDataForRoller();
    if (data.manualMode) {mode = CONTROL_MODE;}
    else mode = AUTO_MODE;
    switch (mode)
    {
    case AUTO_MODE:
        if( hour_now>=8 && hour_now<19 && data.detectStatus == 1 && roller->getStatus()!=0)    roller->setValue(0);
        if( (hour_now>=19||hour_now<8) && data.detectStatus == 0 && roller->getStatus()!=100)   roller->setValue(100);
        break;
    
    case PC_MODE:
        roller->setValue(data.manualRollerValue);
        break;

    case CONTROL_MODE:
        roller->setValue(data.manualRollerValue);
        break;
    }

}


    

