#include "LightTask.h"
using namespace std;

LightTask::LightTask() {

}

void LightTask::init(int period) {
    //Serial.begin(9600);
    Task::init(period);
    IoTDevice = new IoTHubDevice("HostName=bobofan-iothub.azure-devices.net;DeviceId=pc;SharedAccessKey=7erHmTK/12my6evlrkn8YJiHF3hDlrr6TkTFHN6EQh0=");
    timer = new Timer();
    IoTDevice->startService();
}

void LightTask::tick() {

    IoTDevice->sync();
    cout << "Current Hour: " << timer->getCurrentHour() << endl;
    cout << "Detect Status: " << IoTDevice->getDetectStatus() << endl;
    cout << "Light Value: " << IoTDevice->getLightValue() << endl;
    cout << "dashboardSwitch: " << IoTDevice->getDashboardSwitch() << endl;
    cout << "lightSwitch: " << IoTDevice->getLightSwitchNode() << endl;
    cout << "rollerSlider: " << IoTDevice->getRollerSliderValueNode() << endl;

    
}
    

