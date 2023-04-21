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


static const char* connectionString = "HostName=bobofan-iothub.azure-devices.net;DeviceId=pc;SharedAccessKey=7erHmTK/12my6evlrkn8YJiHF3hDlrr6TkTFHN6EQh0=";

#define MESSAGE_COUNT        3
static bool g_continueRunning = true;
static size_t g_message_recv_count = 0;


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

            // Parse JSON message
            JSON_Value* json = json_parse_string((char*)buff_msg);
            if (json == NULL)
            {
                (void)printf("Failure parsing JSON message\r\n");
            }
            else
            {
                // Read detect_status and light_value from JSON message
                JSON_Object* root = json_value_get_object(json);
                if (root == NULL)
                {
                    (void)printf("Failure retrieving JSON root object\r\n");
                }
                else
                {
                    int detect_status = json_object_dotget_number(root, "detect_status");
                    int light_value = json_object_dotget_number(root, "light_value");

                    printf("detect_status: %d\r\n", detect_status);
                    printf("light_value: %d\r\n", light_value);
                }

                json_value_free(json);
            }
        }
    }

    g_message_recv_count++;

    return IOTHUBMESSAGE_ACCEPTED;

}

int main(void)
{
    IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = MQTT_Protocol;
    int keepAliveIntervalInSeconds = 20;

    (void)IoTHub_Init();

    IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;

    (void)printf("Creating IoTHub Device handle\r\n");

    // Create the iothub handle here
    device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(connectionString, protocol);
    if (device_ll_handle == NULL)
    {
        (void)printf("Failure creating IotHub device. Hint: Check your connection string.\r\n");
    }
    else
    {
        // Set any option that are necessary.
        // For available options please see the iothub_sdk_options.md documentation

        IoTHubDeviceClient_LL_SetOption(device_ll_handle, "keepalive", &keepAliveIntervalInSeconds);

        bool urlDecodeOn = true;
        (void)IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_AUTO_URL_ENCODE_DECODE, &urlDecodeOn);



        if (IoTHubDeviceClient_LL_SetMessageCallback(device_ll_handle, receive_msg_callback, NULL) != IOTHUB_CLIENT_OK)
        {
            (void)printf("ERROR: IoTHubClient_LL_SetMessageCallback..........FAILED!\r\n");
        }
        else
        {
            (void)printf("Waiting for message to be sent to device\r\n");
            do
            {
                IoTHubDeviceClient_LL_DoWork(device_ll_handle);

                ThreadAPI_Sleep(10);

            } while (g_continueRunning);
        }

        // Clean up the iothub sdk handle
        IoTHubDeviceClient_LL_Destroy(device_ll_handle);
    }
    // Free all the sdk subsystem
    IoTHub_Deinit();

    printf("Press any key to continue");
    (void)getchar();

    return 0;
}
