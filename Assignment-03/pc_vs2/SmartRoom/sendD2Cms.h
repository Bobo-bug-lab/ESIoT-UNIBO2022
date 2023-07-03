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


class IoTHubDeviceSend {
public:
    IoTHubDeviceSend (const char* connectionString);
    void startService();
    void sync();
    IOTHUB_DEVICE_CLIENT_LL_HANDLE endService();
    //IOTHUB_DEVICE_CLIENT_LL_HANDLE sync();
    bool getLightSwitchNode();
    int getRollerSliderValueNode();
    void sendD2CMessage(bool light, int roller);
    bool g_continueRunning;
    long getLastSyncTime();
    bool lightSendTest = 0;
    int rollerSendTest = 0;

protected:
    void updateSyncTime(long time);

private:
    const char* connectionString;
    static void send_confirm_callback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback);
    static void connection_status_callback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void* user_context);
    //static IOTHUBMESSAGE_DISPOSITION_RESULT send_confirm_callback_static(IOTHUB_MESSAGE_HANDLE message, void* user_context);  
    bool detectStatus = 0;
    int lightValue = 0;
    bool dashboardSwitch = 0;
    bool lightSwitchNode = 0;
    int rollerSliderNode = 0;
    long lastTimeSync;
    bool lightStatus = 0;
    int rollerStatus = 0;
    IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;

};

//static void send_confirm_callback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback);
//static void connection_status_callback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void* user_context);


