#pragma once
#include<string>
#include<unordered_map>

namespace bitrpc {
    #define KEY_METHOD      "method"
    #define KEY_PARAMS      "parameters"
    #define KEY_TOPIC_KEY   "topic_key"
    #define KEY_TOPIC_MSG   "topic_msg"
    #define KEY_OPTYPE      "optype"
    #define KEY_HOST        "host"
    #define KEY_HOST_IP     "ip"
    #define KEY_HOST_PORT   "port"
    #define KEY_RCODE       "rcode"
    #define KEY_RESULT      "result"

    enum class MType {
        REQ_RPC = 0,
        RSP_RPC,
        REQ_TOPIC,
        RSP_TOPIC,
        REQ_SERVICE,
        RSP_SERVICE,
    };

    enum class RCode{
        RCODE_OK = 0,
        RCODE_PARES_FAILED,
        RCODE_INVALID_MSG,
        RCODE_DISCONNECTED,
        RCODE_INVALID_PARAMS,
        RCODE_NOT_FOUND_SERVICE,
        RCODE_INVALID_OPTYPE,
        RCODE_NOT_FOUND_TOPIC
    };
    static std::string errReason(RCode code){
        static std::unordered_map<RCode, std::string> err_map = {
            {RCode::RCODE_OK, "成功处理！"},
            {RCode::RCODE_PARES_FAILED, "消息解析失败！"},
            {RCode::RCODE_INVALID_MSG, "无效消息！"},
            {RCode::RCODE_DISCONNECTED, "连接已断开！"},
            {RCode::RCODE_INVALID_PARAMS, "无效的Rpc参数！"},
            {RCode::RCODE_NOT_FOUND_SERVICE, "没有找到对应的服务！"},
            {RCode::RCODE_INVALID_OPTYPE, "无效的操作类型！"},
            {RCode::RCODE_NOT_FOUND_TOPIC, "没有找到对应的主题！"}
        };
        auto it = err_map.find(code);
        if(it == err_map.end()){
            return "未知错误！";
        }
        return it->second;
    }

    enum class RType{
        REQ_SYNC = 0,
        REQ_ASYNC,
        REQ_CLLBACK
    };

    enum class TopicOptype{
        TOPIC_CREATE = 0,
        TOPIC_REMOVE,
        TOPIC_SUBSCRIBE,
        TOPIC_CANCEL,
        TOPIC_PUBLISH
    };

    enum class ServiceOptype{
        SERVICE_REGISTRY,
        SERVICE_DISCOVERY,
        SERVICE_ONLINE,
        SERVICE_OFFLINE
    };
}