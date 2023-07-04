#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "iothub.h"
#include "iothub_device_client_ll.h"
#include "iothub_client_options.h"
#include "iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/shared_util_options.h"
#include "iothubtransportmqtt.h"
#include "parson.h"
#include "Timer.h"

class IoTHubDevice {
public:
    IoTHubDevice(const char* connectionString);
    void startService();
    void sync();
    IOTHUB_DEVICE_CLIENT_LL_HANDLE endService();
    //IOTHUB_DEVICE_CLIENT_LL_HANDLE sync();
    bool getDetectStatus();
    double getLightValue();
    bool getDashboardSwitch();
    bool getLightSwitchNode();
    int getRollerSliderValueNode();
    bool g_continueRunning;
    long getLastSyncTime();

protected:
    void updateSyncTime(long time);

private:
    const char* connectionString;
    IOTHUBMESSAGE_DISPOSITION_RESULT receive_msg_callback(IOTHUB_MESSAGE_HANDLE message, void* user_context);
    static IOTHUBMESSAGE_DISPOSITION_RESULT receive_msg_callback_static(IOTHUB_MESSAGE_HANDLE message, void* user_context);
    bool detectStatus = 0;
    double lightValue = 0;
    bool dashboardSwitch = 0;
    bool lightSwitchNode = 0;
    int rollerSliderNode = 0;
    long lastTimeSync;
    IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;  
    void setDataForLight();
    //void setDataForRoller();
    //size_t g_message_recv_count;

};

struct DataForLight getDataForLight();
//struct DataForRoller getDataForRoller();

struct DataForLight {
    bool detectStatus = 0;
    int lightValue = 0;
    bool dashboardSwitch = 0;
    int lightSwitchNode = 0;
    int rollerSliderValueNode = 0;
};

// struct DataForRoller {
//     bool detectStatus = 0;
//     bool dashboardSwitch = 0;
//     int rollerSliderValueNode = 0;
// };
    //cout << "Detect Status: " << IoTDevice->getDetectStatus() << endl;
    //cout << "Light Value: " << IoTDevice->getLightValue() << endl; 这两个来自esp

    //cout << "dashboardSwitch: " << IoTDevice->getDashboardSwitch() << endl; 来自
    //Node cout << "lightSwitch: " << IoTDevice->getLightSwitchNode() << endl;

    //Node cout << "rollerSlider: " << IoTDevice->getRollerSliderValueNode() << endl;
