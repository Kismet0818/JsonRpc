#include "message.hpp"
#include "net.hpp"
#include "dispatcher.hpp"

void onRpcRequest(const bitrpc::BaseConnection::ptr& conn, bitrpc::RpcRequest::ptr& msg) {
    std::cout << "收到了Rpc请求：" << msg->method() << std::endl;
    std::string body = msg->serialize();
    std::cout << body <<std::endl;
    auto rpc_rsp = bitrpc::MessageFactory::create<bitrpc::RpcResponse>();
    rpc_rsp->setId("11111");
    rpc_rsp->setMType(bitrpc::MType::RSP_RPC);
    rpc_rsp->setRCode(bitrpc::RCode::RCODE_OK);
    rpc_rsp->setResult(33);
    conn->send(rpc_rsp);
}
void onTopicRequest(const bitrpc::BaseConnection::ptr& conn, bitrpc::TopicRequest::ptr& msg) {
    std::cout << "收到了Topic请求：";
    std::string body = msg->serialize();
    std::cout << body <<std::endl;
    auto rpc_rsp = bitrpc::MessageFactory::create<bitrpc::TopicResponse>();
    rpc_rsp->setId("22222");
    rpc_rsp->setMType(bitrpc::MType::RSP_TOPIC);
    rpc_rsp->setRCode(bitrpc::RCode::RCODE_OK);
    conn->send(rpc_rsp);
}

int main()
{
    auto dispatcher = std::make_shared<bitrpc::Dispatcher>();
    dispatcher->registerHandler<bitrpc::RpcRequest>(bitrpc::MType::REQ_RPC, onRpcRequest);  //注册映射关系
    dispatcher->registerHandler<bitrpc::TopicRequest>(bitrpc::MType::REQ_TOPIC, onTopicRequest);  //注册映射关系

    auto server = bitrpc::ServerFactory::create(9090);
    auto message_cb = std::bind(&bitrpc::Dispatcher::onMessage, dispatcher.get(),
        std::placeholders::_1, std::placeholders::_2);
    server->setMessageCallback(message_cb);
    server->start();

    return 0;
}