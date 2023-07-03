//#include <iostream>
//#include <common.h>
//#include <blob.h>
//#include <queue.h>
//#include <table.h>
//#include <credentials.h>
//#include <entity.h>
//#include <httphandler.h>
//#include <storage_account.h>
//#include <table.h>
//#include <was/queue.h>
//#include <was/blob.h>
//#include <was/correlation_vector.h>
//#include <was/table_batch_operation.h>
//#include <was/uri_builder.h>
//#include <was/common.h>
//#include <was/queue_client.h>
//#include <was/table_client.h>
//#include <was/blob_client.h>
//#include <was/storage_exception.h>
//#include <was/lease.h>
//#include <was/append_blob.h>
//#include <was/block_blob.h>
//#include <was/page_blob.h>
//#include <was/retry_policy.h>
//#include <was/logging.h>
//#include <was/storage_outcome.h>
//#include <was/shared_access_signature.h>
//
//// Azure SDK for C++ Azure服务总线客户端头文件
//#include <core.hpp>
//#include <messaging.hpp>
//#include <messaging/service_bus.hpp>
//
//using namespace std;
//using namespace Azure::Messaging::ServiceBus;
//
//int main()
//{
//    // 从环境变量中获取连接字符串，替换为自己的服务总线连接字符串
//    string connectionString = getenv("SB_CONNECTION_STRING");
//    ServiceBusClientOptions options;
//    auto client = ServiceBusClient::CreateFromConnectionString(connectionString, options);
//
//    // 替换为自己的服务总线主题名称
//    string topicName = "mytopic";
//
//    // 创建服务总线主题客户端对象
//    auto topicClient = client.CreateTopicClient(topicName);
//
//    // 创建服务总线消息对象，设置消息内容
//    ServiceBusMessage message("Hello, Azure Service Bus!");
//
//    // 发送消息到服务总线主题
//    auto sendResult = topicClient->SendMessage(message);
//    cout << "Sent message: " << sendResult.GetMessageId() << endl;
//
//    // 关闭服务总线主题客户端对象
//    topicClient->Close();
//
//    // 创建服务总线订阅客户端对象
//    // 替换为自己的服务总线订阅名称
//    string subscriptionName = "mysubscription";
//    auto subscriptionClient = client.CreateSubscriptionClient(topicName, subscriptionName);
//
//    // 接收并处理服务总线订阅的消息
//    auto receiver = subscriptionClient->CreateReceiver();
//    ServiceBusReceivedMessage receivedMessage;
//    while (true)
//    {
//        // 接收消息
//        receivedMessage = receiver.ReceiveMessage();
//        if (receivedMessage != nullptr)
//        {
//            // 处理消息
//            cout << "Received message: " << receivedMessage.GetBody() << endl;
//
//            // 标记消息为已处理
//            receiver.CompleteMessage(receivedMessage);
//        }
//    }
//
//    // 关闭服务总线订阅客户端对象
//    subscriptionClient->Close();
//
//    // 关闭服务总线客户端对象
//    client.Close();
//
//    return 0;
