using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;

using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Extensions.Logging;

namespace MyAf
{
    public class Function1
    {
        private static HttpClient client = new HttpClient();
        
        [FunctionName("Function1")]
        public void Run([IoTHubTrigger("messages/events", Connection = "ConnectionString")] EventData[] eventHubMessages, ILogger log)
        {
            foreach (var message in eventHubMessages)
            {
                log.LogInformation($"C# function triggered to process a message: {Encoding.UTF8.GetString(message.Body)}");
                log.LogInformation($"EnqueuedTimeUtc={message.SystemProperties.EnqueuedTimeUtc}");
            }
        }
    }
}