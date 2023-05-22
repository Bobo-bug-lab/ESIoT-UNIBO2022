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
#include "getC2Dms.h"
#include "Timer.h"

struct DataForLight dataforlight;

    IoTHubDevice::IoTHubDevice(const char* connectionString) {
        // Save the connection string
        this->connectionString = connectionString;
        //this->g_message_recv_count = 0;
        this->g_continueRunning = 1;
        this->dashboardSwitch = false;
        this->lightSwitchNode = false;
    }

    void IoTHubDevice::startService() {
        //this->lastTimeSync = 0;
        IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = MQTT_Protocol;
        int keepAliveIntervalInSeconds = 20;

        (void)IoTHub_Init();

        //IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;

        (void)printf("Creating IoTHub Device handle for receiving msg.......\r\n");

        // Create the iothub handle here
        this->device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(this->connectionString, protocol);
        if (this->device_ll_handle == NULL)
        {
            (void)printf("Failure creating IotHub device. Hint: Check your connection string.\r\n");
        }
        else{

            IoTHubDeviceClient_LL_SetOption(device_ll_handle, "keepalive", &keepAliveIntervalInSeconds);

            bool urlDecodeOn = true;
            (void)IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_AUTO_URL_ENCODE_DECODE, &urlDecodeOn);
        }

    }

    void IoTHubDevice::sync(){

            if (IoTHubDeviceClient_LL_SetMessageCallback(this->device_ll_handle, receive_msg_callback_static, this) != IOTHUB_CLIENT_OK)
            {
                (void)printf("ERROR: IoTHubClient_LL_SetMessageCallback..........FAILED!\r\n");
            }
            else
            {

                    IoTHubDeviceClient_LL_DoWork(this->device_ll_handle);


            } 
            updateSyncTime(millis());

    }



    IOTHUB_DEVICE_CLIENT_LL_HANDLE IoTHubDevice::endService() {

        IoTHubDeviceClient_LL_Destroy(this->device_ll_handle);

        // Free all the sdk subsystem
        IoTHub_Deinit();

        printf("Press any key to continue");
        (void)getchar();

        return this->device_ll_handle;
    }

    bool IoTHubDevice::getDetectStatus() {
        return this->detectStatus;
    }
    int IoTHubDevice::getLightValue() {
        return this->lightValue;
    }
    bool IoTHubDevice::getDashboardSwitch() {
        return this->dashboardSwitch;
    }
    bool IoTHubDevice::getLightSwitchNode() {
        return this->lightSwitchNode;
    }
    int IoTHubDevice::getRollerSliderValueNode() {
        return this->rollerSliderNode;
    }

    IOTHUBMESSAGE_DISPOSITION_RESULT IoTHubDevice::receive_msg_callback(IOTHUB_MESSAGE_HANDLE message, void* user_context)
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

                        printf("Received Message\r\nMessage ID: %s\r\n Correlation ID: %s\r\n Data: <<<%s>>>\r\n", messageId, correlationId, (char*)buff_msg);

                        if(strcmp(correlationId, "esp8266") == 0){
                            this->detectStatus = json_object_dotget_number(root, "detect_status");
                            this->lightValue = json_object_dotget_number(root, "light_value");
                        }
                        else if(strcmp(correlationId, "node-red") == 0){
                            if(json_object_dotget_boolean(root, "dashboardSwitch") == true){
                                this->dashboardSwitch = true;
                            }
                            else this->dashboardSwitch = false;
                            if(json_object_dotget_boolean(root, "lightSwitch") == true){
                                this->lightSwitchNode = true;
                            }
                            else this->lightSwitchNode = false;
                            //this->dashboardSwitch = json_object_dotget_boolean(root, "dashboardSwitch");
                            //this->lightSwitchNode = json_object_dotget_boolean(root, "lightSwitch");
                            this->rollerSliderNode = json_object_dotget_number(root, "rollerSlider");                            
                        }
                        else{
                            (void)printf("Unknown message source! Correlation ID: %s\r\n", correlationId);
                        }
                        //printf("detect_status: %d\r\n", this->detectStatus);
                        //printf("light_value: %d\r\n", this->lightValue);

                            std::cout << "Detect Status: " << this->getDetectStatus() << std::endl;
                            std::cout << "Light Value: " << this->getLightValue() << std::endl;
                            std::cout << "dashboardSwitch: " << this->getDashboardSwitch() << std::endl;
                            std::cout << "lightSwitch: " << this->getLightSwitchNode() << std::endl;
                            std::cout << "rollerSlider: " << this->getRollerSliderValueNode() << std::endl;
                    }

                    json_value_free(json);
                }
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

        //updateSyncTime(millis());

        return IOTHUBMESSAGE_ACCEPTED;

    }

    IOTHUBMESSAGE_DISPOSITION_RESULT IoTHubDevice::receive_msg_callback_static(IOTHUB_MESSAGE_HANDLE message, void* user_context) {
        IoTHubDevice* device = static_cast<IoTHubDevice*>(user_context);
        return device->receive_msg_callback(message, user_context);
    }

    void IoTHubDevice::updateSyncTime(long time) {
        lastTimeSync = time;
    }

    long IoTHubDevice::getLastSyncTime() {
        return lastTimeSync;
    }

    void IoTHubDevice::setDataForLight(){
        dataforlight.dashboardSwitch = this->getDashboardSwitch();
        dataforlight.detectStatus = this->getDetectStatus();
        dataforlight.lightSwitchNode = this->getLightSwitchNode();
        dataforlight.lightValue = this->getLightValue();
    }

    struct DataForLight getDataForLight(){
        return dataforlight;
    }