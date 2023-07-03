using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;

using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Extensions.Logging;

namespace MyAzureFunc
{
    public class IoTTriggerFunc
    {
        private static HttpClient client = new HttpClient();
        
        [FunctionName("IoTTriggerFunc")]
        public void Run([IoTHubTrigger("EntityPath=iothub-ehub-bobofan-io-24797669-16e28a6b6c", Connection = "ConnectionString")]EventData message, ILogger log)
        {
            log.LogInformation($"C# IoT Hub trigger function processed a message: {Encoding.UTF8.GetString(message.Body.Array)}");
        }
    }
}