#include "TestTask.h"

#define MAX_TIME_LIGHT_ON 5000

using namespace std;

TestTask::TestTask() {

}

void TestTask::init(int period) {
    //Serial.begin(9600);
    Task::init(period);
    //pir = new Pir();
    //air = new Air();
    IoTDevice = new IoTHubDevice("HostName=bobofan-iothub.azure-devices.net;DeviceId=pc;SharedAccessKey=7erHmTK/12my6evlrkn8YJiHF3hDlrr6TkTFHN6EQh0=");
    timer = new Timer();
    //IoTDevice->lastTimeSync = timer->getCurrentTime();
    IoTDevice->startService();
}

void TestTask::tick() {
    //pir->sync();
    //air->sync();
    IoTDevice->sync();
    cout << "Current Hour: " << timer->getCurrentHour() << endl;
    cout << "Detect Status: " << IoTDevice->getDetectStatus() << endl;
    cout << "Light Value: " << IoTDevice->getLightValue() << endl;

    
}
    

