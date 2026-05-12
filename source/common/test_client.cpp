#include "message.hpp"
#include "net.hpp"
#include "dispatcher.hpp"
#include<thread>

void onRpcResponse(const bitrpc::BaseConnection::ptr& conn, bitrpc::RpcResponse::ptr& msg) {
    std::cout << "收到了Rpc响应：";
    std::string body = msg->serialize();
    std::cout << body <<std::endl;
}
void onTopicResponse(const bitrpc::BaseConnection::ptr& conn, bitrpc::TopicResponse::ptr& msg) {
    std::cout << "收到了Topic响应：";
    std::string body = msg->serialize();
    std::cout << body <<std::endl;
}

int main()
{
    auto dispatcher = std::make_shared<bitrpc::Dispatcher>();
    dispatcher->registerHandler<bitrpc::RpcResponse>(bitrpc::MType::RSP_RPC, onRpcResponse);  //注册映射关系
    dispatcher->registerHandler<bitrpc::TopicResponse>(bitrpc::MType::RSP_TOPIC, onTopicResponse);  //注册映射关系

    auto client = bitrpc::ClientFactory::create("127.0.0.1", 9090);
    auto message_cb = std::bind(&bitrpc::Dispatcher::onMessage, dispatcher.get(),
        std::placeholders::_1, std::placeholders::_2);
    client->setMessageCallback(message_cb);
    client->connect();
    
    auto rpc_req = bitrpc::MessageFactory::create<bitrpc::RpcRequest>();
    rpc_req->setId("11111");
    rpc_req->setMType(bitrpc::MType::REQ_RPC);
    rpc_req->setMethod("Add");
    Json::Value param;
    param["num1"] = 11;
    param["num2"] = 22;
    rpc_req->setParams(param);
    client->send(rpc_req);

    auto topic_req = bitrpc::MessageFactory::create<bitrpc::TopicRequest>();
    topic_req->setId("22222");
    topic_req->setMType(bitrpc::MType::REQ_TOPIC);
    topic_req->setOptype(bitrpc::TopicOptype::TOPIC_CREATE);
    topic_req->setTopicKey("news");
    client->send(topic_req);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    client->shutdown();
    return 0;
}