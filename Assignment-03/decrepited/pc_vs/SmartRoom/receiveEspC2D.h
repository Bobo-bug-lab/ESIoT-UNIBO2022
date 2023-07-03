#pragma once

#include <iostream>
#include <cstring>
#include "azure_c_shared_utility/threadapi.h"
#include "iothub_device_client.h"
#include "iothubtransportmqtt.h"
#include "parson.h"

class IoTHubDevice {
public:
    IoTHubDevice(const char* connectionString);

    void start();

    int getDetectStatus();

    int getLightValue();

private:
    const char* connectionString;
    IOTHUB_DEVICE_CLIENT_HANDLE deviceHandle;
    int detectStatus = 0;
    int lightValue = 0;

    void parseMessage(const char* message, size_t size);
};
