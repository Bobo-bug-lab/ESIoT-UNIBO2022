using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;

using System;
using Microsoft.Azure.Devices;
using Newtonsoft.Json;
using System.Text;
using System.Configuration;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Net.Http;
using Microsoft.Extensions.Logging;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Rest;

namespace MyAf
{
    public class Function1
    {
        private static readonly ServiceClient _serviceClient = ServiceClient.CreateFromConnectionString("HostName=bobofan-iothub.azure-devices.net;SharedAccessKeyName=iothubowner;SharedAccessKey=QcR4qbxQNdytJGwKCyib2MNeF+77HFv7I6GkbNCKfYc=");
        private string sourceDeviceId, targetDeviceId;
        //private const string pcString = "HostName=bobofan-iothub.azure-devices.net;DeviceId=pc;SharedAccessKey=7erHmTK/12my6evlrkn8YJiHF3hDlrr6TkTFHN6EQh0=";
        //private const string espString = "HostName=bobofan-iothub.azure-devices.net;DeviceId=esp8266;SharedAccessKey=Peu+kM0TUssgYbd3Wra7vt9T0SBfZEeomQnLp8Z+6fw=";

        //private const string rednodeString;

        private static HttpClient client = new HttpClient();
        
        [FunctionName("Function1")]
        public async Task RunAsync([IoTHubTrigger("messages/events", Connection = "ConnectionString")] EventData message, ILogger log)
        {

            //log.LogInformation($"Azure functions start running... (routing messages through azure iot hub)");
            var sourceDeviceId = message.SystemProperties["iothub-connection-device-id"].ToString();
            var messageString = Encoding.UTF8.GetString(message.Body.Array);
            log.LogInformation($"C# function triggered to process a message: {messageString}");
            log.LogInformation($"Device ID: {sourceDeviceId}");


            switch (sourceDeviceId)
            {
                case "esp8266":
                    Console.WriteLine("Monday");
                    // go to both PC and node-red
                    break;
                case "pc":
                    Console.WriteLine("Sunday");
                    break;
                case "nodered":
                    Console.WriteLine("Sunday");
                    break;
                default:
                    log.LogInformation($"No valid input");
                    break;
            }

            try
            {
                string targetDeviceId = "pc";
                var c2dMessage = new Message(Encoding.ASCII.GetBytes(messageString));

                // Send the message to the device with the corresponding device ID
                await _serviceClient.SendAsync(targetDeviceId, c2dMessage);

                log.LogInformation($"C2D message sent to device with ID: {targetDeviceId}");
            }
            catch (Exception ex)
            {
                log.LogError($"Exception caught: {ex.Message}");
            }
        }
    }
}