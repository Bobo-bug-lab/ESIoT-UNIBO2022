#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include "iothub.h"
#include "iothub_device_client_ll.h"
#include "iothub_client_options.h"
#include "iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/shared_util_options.h"
#include "iothub_client.h"
#include "iothubtransportmqtt.h"
#include "parson.h"

/* Paste in the your iothub connection string  */
//static const char* connectionString = "your device connectionstring";

//#define MESSAGE_COUNT        3
static bool g_continueRunning = true;
static size_t g_message_recv_count = 0;

using namespace std;

class IoTHubClient {
public:
    IoTHubClient(const char* connectionString) {
        // Save the connection string
        this->connectionString = connectionString;
    }

    void start() {
        // Create an IoT Hub client using MQTT protocol
        IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = MQTT_Protocol;

        this->device_ll_handle = IoTHubClient_LL_CreateFromConnectionString(this->connectionString, protocol);
        if (device_ll_handle == NULL)
        {
            (void)printf("Failure creating IotHub device. Hint: Check your connection string.\r\n");
        }

        else
        {
            // Set options for the IoT Hub client
            int keepAliveIntervalInSeconds = 20;
            IoTHubDeviceClient_LL_SetOption(this->device_ll_handle, "keepalive", &keepAliveIntervalInSeconds);

            // Set a callback function for C2D messages
            IoTHubDeviceClient_LL_SetMessageCallback(this->device_ll_handle, [](IOTHUB_MESSAGE_HANDLE message, void* userContextCallback) -> IOTHUBMESSAGE_DISPOSITION_RESULT {
                // Convert the message to a string
                const char* buffer;
                size_t size;
                if (IoTHubMessage_GetByteArray(message, (const unsigned char**)&buffer, &size) != IOTHUB_MESSAGE_OK)
                {
                    cout << "Error: Unable to get the message data.\n";
                    return IOTHUBMESSAGE_REJECTED;
                }

                // Parse the message and extract detect_status and light_value
                IoTHubClient* iotHubClient = (IoTHubClient*)userContextCallback;
                iotHubClient->parseMessage(buffer, size);

                // Acknowledge the message
                return IOTHUBMESSAGE_ACCEPTED;
                }, this);

            // Start the IoT Hub client
            IoTHubDeviceClient_LL_DoWork(this->device_ll_handle);

            // Wait for incoming C2D messages
            while (true)
            {
                IoTHubDeviceClient_LL_DoWork(this->device_ll_handle);
                ThreadAPI_Sleep(100);
            }
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
    IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;
    int detectStatus = 0;
    int lightValue = 0;

    static IOTHUBMESSAGE_DISPOSITION_RESULT receive_msg_callback(IOTHUB_MESSAGE_HANDLE message, void* user_context)
    {
        (void)user_context;
        const char* messageId;
        const char* correlationId;

        // Message properties
        if ((messageId = IoTHubMessage_GetMessageId(message)) == NULL)
        {
            messageId = "<unavailable>";
        }

        if ((correlationId = IoTHubMessage_GetCorrelationId(message)) == NULL)
        {
            correlationId = "<unavailable>";
        }

        IOTHUBMESSAGE_CONTENT_TYPE content_type = IoTHubMessage_GetContentType(message);
        if (content_type == IOTHUBMESSAGE_BYTEARRAY)
        {
            const unsigned char* buff_msg;
            size_t buff_len;

            if (IoTHubMessage_GetByteArray(message, &buff_msg, &buff_len) != IOTHUB_MESSAGE_OK)
            {
                (void)printf("Failure retrieving byte array message\r\n");
            }
            else
            {
                (void)printf("Received Binary message\r\nMessage ID: %s\r\n Correlation ID: %s\r\n Data: <<<%.*s>>> & Size=%d\r\n", messageId, correlationId, (int)buff_len, buff_msg, (int)buff_len);
            }
        }
        else
        {
            const char* string_msg = IoTHubMessage_GetString(message);
            if (string_msg == NULL)
            {
                (void)printf("Failure retrieving byte array message\r\n");
            }
            else
            {
                (void)printf("Received String Message\r\nMessage ID: %s\r\n Correlation ID: %s\r\n Data: <<<%s>>>\r\n", messageId, correlationId, string_msg);
            }
        }
        const char* property_value = "property_value";
        const char* property_key = IoTHubMessage_GetProperty(message, property_value);
        if (property_key != NULL)
        {
            printf("\r\nMessage Properties:\r\n");
            printf("\tKey: %s Value: %s\r\n", property_value, property_key);
        }
        g_message_recv_count++;

        return IOTHUBMESSAGE_ACCEPTED;

    }

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