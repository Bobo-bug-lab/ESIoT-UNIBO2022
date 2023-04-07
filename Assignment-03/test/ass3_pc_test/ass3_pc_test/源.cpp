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
//// Azure SDK for C++ Azure�������߿ͻ���ͷ�ļ�
//#include <core.hpp>
//#include <messaging.hpp>
//#include <messaging/service_bus.hpp>
//
//using namespace std;
//using namespace Azure::Messaging::ServiceBus;
//
//int main()
//{
//    // �ӻ��������л�ȡ�����ַ������滻Ϊ�Լ��ķ������������ַ���
//    string connectionString = getenv("SB_CONNECTION_STRING");
//    ServiceBusClientOptions options;
//    auto client = ServiceBusClient::CreateFromConnectionString(connectionString, options);
//
//    // �滻Ϊ�Լ��ķ���������������
//    string topicName = "mytopic";
//
//    // ����������������ͻ��˶���
//    auto topicClient = client.CreateTopicClient(topicName);
//
//    // ��������������Ϣ����������Ϣ����
//    ServiceBusMessage message("Hello, Azure Service Bus!");
//
//    // ������Ϣ��������������
//    auto sendResult = topicClient->SendMessage(message);
//    cout << "Sent message: " << sendResult.GetMessageId() << endl;
//
//    // �رշ�����������ͻ��˶���
//    topicClient->Close();
//
//    // �����������߶��Ŀͻ��˶���
//    // �滻Ϊ�Լ��ķ������߶�������
//    string subscriptionName = "mysubscription";
//    auto subscriptionClient = client.CreateSubscriptionClient(topicName, subscriptionName);
//
//    // ���ղ�����������߶��ĵ���Ϣ
//    auto receiver = subscriptionClient->CreateReceiver();
//    ServiceBusReceivedMessage receivedMessage;
//    while (true)
//    {
//        // ������Ϣ
//        receivedMessage = receiver.ReceiveMessage();
//        if (receivedMessage != nullptr)
//        {
//            // ������Ϣ
//            cout << "Received message: " << receivedMessage.GetBody() << endl;
//
//            // �����ϢΪ�Ѵ���
//            receiver.CompleteMessage(receivedMessage);
//        }
//    }
//
//    // �رշ������߶��Ŀͻ��˶���
//    subscriptionClient->Close();
//
//    // �رշ������߿ͻ��˶���
//    client.Close();
//
//    return 0;
