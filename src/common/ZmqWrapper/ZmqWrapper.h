#ifndef INCLUDED_ZMQWRAPPER
#define INCLUDED_ZMQWRAPPER

#include <string>
#include <zmq.h>
#include <map>
#include <functional>

class ZmqWrapper
{
public:
    enum zmqPatternEnum{
        REQUEST = ZMQ_REQ,
        REPLY   = ZMQ_REP,
        SUBSCRIBE = ZMQ_SUB,
        PUBLISH = ZMQ_PUB
    };

    using CallbackFunction = std::function<void(std::string, std::string)>;

public:
    ZmqWrapper();
    ~ZmqWrapper();

    void registerSession(std::string ip,
                         int port,
                         zmqPatternEnum pattern,
                         std::string topic);

    void registerSession(std::string ip,
                         int port,
                         zmqPatternEnum pattern,
                         std::string topic,
                         const CallbackFunction& callback);

    int pollMessage(std::string &msg, int timeout);

    int sendMessage(std::string msg);

    void* context;
    void* socket;
    std::string topic;

private:
    std::map<std::string, CallbackFunction> callbackMap;
};

#endif
