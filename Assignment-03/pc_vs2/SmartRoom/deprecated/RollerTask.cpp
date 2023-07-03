#include "RollerTask.h"
using namespace std;

DataForRoller data;

RollerTask::RollerTask() {

}

void RollerTask::init(int period) {
    //Serial.begin(9600);
    Task::init(period);
    serialPort = new SerialPort("COM5");
    roller = new Roller();
    timer = new Timer();
    data = getDataForRoller();
    mode = AUTO_MODE;
    modechar = 's';
}

void RollerTask::tick() {
    //尚未写好 roller->sync();
    int hour_now = timer->getCurrentHour();
    data = getDataForRoller();
    mode = data.mode;
    switch (mode)
    {
    case AUTO_MODE:
        modechar = 's';
        if( hour_now>=8 && hour_now<19 && data.detectStatus == 1 && roller->getStatus()!=0)    roller->setValue(0);
        if( (hour_now>=19||hour_now<8) && data.detectStat   us == 0 && roller->getStatus()!=100)   roller->setValue(100);
        break;
    
    case PC_MODE:
        modechar = 'd';
        roller->setValue(data.manualRollerValue);
        break;

    case PHONE_MODE:
        modechar = 'a';
        roller->setValue(data.manualRollerValue);
        break;
    }

}


    

