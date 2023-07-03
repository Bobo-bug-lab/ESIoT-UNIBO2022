#include <iostream>
#include <cstring>
#include "azure_c_shared_utility/threadapi.h"
#include "iothub_device_client.h"
#include "iothubtransportmqtt.h"
#include "parson.h"

using namespace std;

class IoTHubDevice {
public:
    IoTHubDevice(const char* connectionString) {
        // Save the connection string
        this->connectionString = connectionString;
    }

    void start() {
        // Create an IoT Hub device client using MQTT protocol
        this->deviceHandle = IoTHubDeviceClient_LL_CreateFromConnectionString(this->connectionString, MQTT_Protocol);

        // Set options for the IoT Hub device client
        int keepAliveIntervalInSeconds = 20;
        IoTHubDeviceClient_LL_SetOption(this->deviceHandle, "keepalive", &keepAliveIntervalInSeconds);

        // Set a callback function for C2D messages
        IoTHubDeviceClient_LL_SetMessageCallback(this->deviceHandle, [](IOTHUB_MESSAGE_HANDLE message, void* userContextCallback) -> IOTHUBMESSAGE_DISPOSITION_RESULT {
            // Convert the message to a string
            const char* buffer;
            size_t size;
            if (IoTHubMessage_GetByteArray(message, (const unsigned char**)&buffer, &size) != IOTHUB_MESSAGE_OK)
            {
                cout << "Error: Unable to get the message data.\n";
                return IOTHUBMESSAGE_REJECTED;
            }

            // Parse the message and extract detect_status and light_value
            IoTHubDevice* iotHubDevice = (IoTHubDevice*)userContextCallback;
            iotHubDevice->parseMessage(buffer, size);

            // Acknowledge the message
            return IOTHUBMESSAGE_ACCEPTED;
            }, this);

        // Start the IoT Hub device client
        IoTHubDeviceClient_LL_DoWork(this->deviceHandle);

        // Wait for incoming C2D messages
        while (true)
        {
            IoTHubDeviceClient_LL_DoWork(this->deviceHandle);
            ThreadAPI_Sleep(100);
        }
    }

    int getDetectStatus() {
        return this->detectStatus;
    }

    int getLightValue() {
        return this->lightValue;
    }

private:
    const char* connectionString;
    IOTHUB_DEVICE_CLIENT_LL_HANDLE deviceHandle;
    int detectStatus = 0;
    int lightValue = 0;

    // Function to parse JSON message and extract detect_status and light_value
    void parseMessage(const char* message, size_t size)
    {
        // Parse the JSON message
        JSON_Value* rootValue = json_parse_string(message);
        if (rootValue == NULL)
        {
            cout << "Error: Unable to parse the message.\n";
            return;
        }

        // Get the root object
        JSON_Object* rootObject = json_value_get_object(rootValue);

        // Get the values for detect_status and light_value
        this->detectStatus = (int)json_object_get_number(rootObject, "detect_status");
        this->lightValue = (int)json_object_get_number(rootObject, "light_value");

        // Clean up the JSON message
        json_value_free(rootValue);
    }
};
