#include "message.hpp"

int main()
{
    // bitrpc::RpcRequest::ptr rrp = bitrpc::MessageFactory::create<bitrpc::RpcRequest>();
    // Json::Value param;
    // param["num1"] = 11;
    // param["num2"] = 22;
    // rrp->setMethod("Add");
    // rrp->setParams(param);
    // std::string str = rrp->serialize();
    // std::cout << str << std::endl;

    // bitrpc::BaseMessage::ptr bmp = bitrpc::MessageFactory::create(bitrpc::MType::REQ_RPC);
    // bool ret = bmp->unserialize(str);
    // if(ret == false) {
    //     return -1;
    // }
    // ret = bmp->check();
    // if(ret == false) {
    //     return -1;
    // }
    // bitrpc::RpcRequest::ptr rrp2 = std::dynamic_pointer_cast<bitrpc::RpcRequest>(bmp);
    // std::cout << rrp2->method() <<std::endl;
    // std::cout << rrp2->params()["num1"].asInt() << std::endl;
    // std::cout << rrp2->params()["num2"].asInt() << std::endl;

    // bitrpc::TopicRequest::ptr trp = bitrpc::MessageFactory::create<bitrpc::TopicRequest>();
    // trp->setTopicKey("news");
    // trp->setOptype(bitrpc::TopicOptype::TOPIC_PUBLISH);
    // trp->setTopicMsg("Hello World");
    // std::string str = trp->serialize();
    // std::cout << str << std::endl;

    // bitrpc::BaseMessage::ptr bmp = bitrpc::MessageFactory::create(bitrpc::MType::REQ_TOPIC);
    // bool ret = bmp->unserialize(str);
    // if(ret == false) {
    //     return -1;
    // }
    // ret = bmp->check();
    // if(ret == false) {
    //     return -1;
    // }
    // bitrpc::TopicRequest::ptr trp2 = std::dynamic_pointer_cast<bitrpc::TopicRequest>(bmp);
    // std::cout << trp2->topicKey() <<std::endl;
    // std::cout << (int)trp2->optype() <<std::endl;
    // std::cout << trp2->topicMsg() <<std::endl;

    // bitrpc::ServiceRequest::ptr trp = bitrpc::MessageFactory::create<bitrpc::ServiceRequest>();
    // trp->setMethod("Add");
    // trp->setOptype(bitrpc::ServiceOptype::SERVICE_REGISTRY);
    // trp->setHost(bitrpc::Address("127.0.0.1", 9090));
    // std::string str = trp->serialize();
    // std::cout << str << std::endl;

    // bitrpc::BaseMessage::ptr bmp = bitrpc::MessageFactory::create(bitrpc::MType::REQ_SERVICE);
    // bool ret = bmp->unserialize(str);
    // if(ret == false) {
    //     return -1;
    // }
    // ret = bmp->check();
    // if(ret == false) {
    //     return -1;
    // }
    // bitrpc::ServiceRequest::ptr trp2 = std::dynamic_pointer_cast<bitrpc::ServiceRequest>(bmp);
    // std::cout << trp2->method() << std::endl;
    // std::cout << (int)trp2->optype() << std::endl;
    // std::cout << trp2->host().first << std::endl;
    // std::cout << trp2->host().second << std::endl;

    // bitrpc::RpcResponse::ptr trp = bitrpc::MessageFactory::create<bitrpc::RpcResponse>();
    // trp->setRCode(bitrpc::RCode::RCODE_OK);
    // trp->setResult(33);
    // std::string str = trp->serialize();
    // std::cout << str << std::endl;

    // bitrpc::BaseMessage::ptr bmp = bitrpc::MessageFactory::create(bitrpc::MType::RSP_RPC);
    // bool ret = bmp->unserialize(str);
    // if(ret == false) {
    //     return -1;
    // }
    // ret = bmp->check();
    // if(ret == false) {
    //     return -1;
    // }
    // bitrpc::RpcResponse::ptr trp2 = std::dynamic_pointer_cast<bitrpc::RpcResponse>(bmp);
    // std::cout << (int)trp2->rcode() << std::endl;
    // std::cout << trp2->result().asInt() << std::endl;

    // bitrpc::TopicResponse::ptr trp = bitrpc::MessageFactory::create<bitrpc::TopicResponse>();
    // trp->setRCode(bitrpc::RCode::RCODE_OK);
    // std::string str = trp->serialize();
    // std::cout << str << std::endl;

    // bitrpc::BaseMessage::ptr bmp = bitrpc::MessageFactory::create(bitrpc::MType::RSP_TOPIC);
    // bool ret = bmp->unserialize(str);
    // if(ret == false) {
    //     return -1;
    // }
    // ret = bmp->check();
    // if(ret == false) {
    //     return -1;
    // }
    // bitrpc::TopicResponse::ptr trp2 = std::dynamic_pointer_cast<bitrpc::TopicResponse>(bmp);
    // std::cout << (int)trp2->rcode() << std::endl;

    bitrpc::ServiceResponse::ptr trp = bitrpc::MessageFactory::create<bitrpc::ServiceResponse>();
    trp->setRCode(bitrpc::RCode::RCODE_OK);
    trp->setMethod("Add");
    trp->setOptype(bitrpc::ServiceOptype::SERVICE_DISCOVERY);
    std::vector<bitrpc::Address> addrs;
    addrs.push_back(bitrpc::Address("127.0.0.1", 9090));
    addrs.push_back(bitrpc::Address("127.0.0.1", 9091));
    trp->setHost(addrs);
    std::string str = trp->serialize();
    std::cout << str << std::endl;

    bitrpc::ServiceResponse::ptr trp2 = bitrpc::MessageFactory::create<bitrpc::ServiceResponse>();
    bitrpc::BaseMessage::ptr bmp = bitrpc::MessageFactory::create(bitrpc::MType::RSP_SERVICE);
    bool ret = bmp->unserialize(str);
    if(ret == false) {
        return -1;
    }
    ret = bmp->check();
    if(ret == false) {
        return -1;
    }
    bitrpc::ServiceResponse::ptr trp2 = std::dynamic_pointer_cast<bitrpc::ServiceResponse>(bmp);
    std::cout << (int)trp2->rcode() << std::endl;
    std::cout << (int)trp2->optype() << std::endl;
    std::cout << trp2->method() << std::endl;
    std::vector<bitrpc::Address> addrs1 = trp2->hosts();
    for(auto &addr : addrs1)
    std::cout << addr.first << ":" << addr.second << std::endl;
    return 0;
} 