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

class IoTHubDevice {
public:
    IoTHubDevice(const char* connectionString);
    void start();
    int getDetectStatus();
    int getLightValue();
    bool g_continueRunning;
    //void sync();
    //virtual void sync();
    //long getLastSyncTime();

protected:
    void updateSyncTime(long time);

private:
    const char* connectionString;
    IOTHUBMESSAGE_DISPOSITION_RESULT receive_msg_callback(IOTHUB_MESSAGE_HANDLE message, void* user_context);
    static IOTHUBMESSAGE_DISPOSITION_RESULT receive_msg_callback_static(IOTHUB_MESSAGE_HANDLE message, void* user_context);
    int detectStatus = 0;
    int lightValue = 0;
    long lastTimeSync;
    virtual void sync();
    long getLastSyncTime();
    //size_t g_message_recv_count;

};