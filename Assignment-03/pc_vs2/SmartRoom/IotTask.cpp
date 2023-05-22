#include "IotTask.h"
using namespace std;

IotTask::IotTask() {

}

void IotTask::init(int period) {
    //Serial.begin(9600);
    Task::init(period);
    IoTDeviceReceive = new IoTHubDevice("HostName=bobofan-iothub.azure-devices.net;DeviceId=pc;SharedAccessKey=7erHmTK/12my6evlrkn8YJiHF3hDlrr6TkTFHN6EQh0=");
    IoTDeviceSend = new IoTHubDeviceSend("HostName=bobofan-iothub.azure-devices.net;DeviceId=pcsend;SharedAccessKey=CXMG+euGW7CHqXuSJw1W++VhUabg+UMg56KArB+d43M=");
    timer = new Timer();
    IoTDeviceReceive->startService();
    IoTDeviceSend->startService();
}

void IotTask::tick() {

    IoTDeviceReceive->sync();
    IoTDeviceSend->sync();
    //cout << "Current Hour: " << timer->getCurrentHour() << endl;

    //cout << "Detect Status: " << IoTDevice->getDetectStatus() << endl;
    //cout << "Light Value: " << IoTDevice->getLightValue() << endl; 这两个来自esp

    //cout << "dashboardSwitch: " << IoTDevice->getDashboardSwitch() << endl; 来自
    //Node cout << "lightSwitch: " << IoTDevice->getLightSwitchNode() << endl;

    //Node cout << "rollerSlider: " << IoTDevice->getRollerSliderValueNode() << endl;

    
}


    

