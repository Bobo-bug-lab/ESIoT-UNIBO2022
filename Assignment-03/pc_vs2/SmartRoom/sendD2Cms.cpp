#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "iothub.h"
#include "iothub_device_client_ll.h"
#include "iothub_client_options.h"
#include "iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/shared_util_options.h"
#include "iothubtransportmqtt.h"
#include "parson.h"
#include "sendD2Cms.h"
#include "Timer.h"
#include "RoomTask.h"

    DataForNode data;

    IoTHubDeviceSend::IoTHubDeviceSend(const char* connectionString) {
        this->connectionString = connectionString;
    }

    void IoTHubDeviceSend::startService() {
        
        IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = MQTT_Protocol;
        int keepAliveIntervalInSeconds = 20;

        (void)IoTHub_Init();

        //IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;

        (void)printf("Creating IoTHub Device handle for sending msg.......e\r\n");

        // Create the iothub handle here
        this->device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(this->connectionString, protocol);
        if (this->device_ll_handle == NULL)
        {
            (void)printf("Failure creating IotHub device. Hint: Check your connection string.\r\n");
        }
        else{
            //IoTHubDeviceClient_LL_SetOption(device_ll_handle, "keepalive", &keepAliveIntervalInSeconds);

            bool urlDecodeOn = true;
            (void)IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_AUTO_URL_ENCODE_DECODE, &urlDecodeOn);
            (void)IoTHubDeviceClient_LL_SetConnectionStatusCallback(device_ll_handle, connection_status_callback, NULL);
        }

    }

    void IoTHubDeviceSend::sync(){
            //this->rollerStatus++;
            data = getDataForNode();
            std::cout << "light status on send: " << data.lightStatus << std::endl;
            sendD2CMessage(data.lightStatus, data.rollerStatus);
            std::cout << "roller status on send: " << data.rollerStatus << std::endl;
            updateSyncTime(millis());

    }



    IOTHUB_DEVICE_CLIENT_LL_HANDLE IoTHubDeviceSend::endService() {

        IoTHubDeviceClient_LL_Destroy(this->device_ll_handle);

        // Free all the sdk subsystem
        IoTHub_Deinit();

        printf("Press any key to continue");
        (void)getchar();

        return this->device_ll_handle;
    }

    bool IoTHubDeviceSend::getLightSwitchNode() {
        return this->lightSwitchNode;
    }
    int IoTHubDeviceSend::getRollerSliderValueNode() {
        return this->rollerSliderNode;
    }

    void IoTHubDeviceSend::sendD2CMessage(bool light, int roller)
    {
        // Create a JSON payload
        JSON_Value* root_value = json_value_init_object();
        JSON_Object* root_object = json_value_get_object(root_value);

        json_object_set_boolean(root_object, "lightStatus", light);
        json_object_set_number(root_object, "rollerStatus", roller);

        const char* payload = json_serialize_to_string(root_value);

        // Create a message handle
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(payload);
        if (message_handle == NULL)
        {
            printf("Failed to create IoT Hub message from string\n");
            return;
        }

        if (IoTHubMessage_SetCorrelationId(message_handle, "pcsend") != IOTHUB_MESSAGE_OK)
        {
            printf("Failed to set correlation id\n");
        }

        // Send the message
        IoTHubDeviceClient_LL_SendEventAsync(this->device_ll_handle, message_handle, send_confirm_callback, NULL);
        //IoTHubDeviceClient_LL_SendEventAsync(this->device_ll_handle, msg_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
        int retryCount = 0;
        const int maxRetryCount = 3;
        do {
            IoTHubDeviceClient_LL_DoWork(this->device_ll_handle);
            ThreadAPI_Sleep(100);  // 等待一段时间，以便消息有机会发送
            retryCount++;
        } while (retryCount <= maxRetryCount);

        // Clean up resources
        json_value_free(root_value);
    }

    void IoTHubDeviceSend::updateSyncTime(long time) {
        lastTimeSync = time;
    }

    long IoTHubDeviceSend::getLastSyncTime() {
        return lastTimeSync;
    }

    void IoTHubDeviceSend::send_confirm_callback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
    {
        (void)userContextCallback;
    }

    void IoTHubDeviceSend::connection_status_callback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void* user_context)
    {
        (void)reason;
        (void)user_context;
        // This sample DOES NOT take into consideration network outages.
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            (void)printf("The device client is connected to iothub\r\n");
        }
        else
        {
            (void)printf("The device client has been disconnected\r\n");
        }
    }
    
    