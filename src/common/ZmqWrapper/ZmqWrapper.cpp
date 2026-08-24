#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <zmq.h>
#include "ZmqWrapper.h"

ZmqWrapper::ZmqWrapper(){}

ZmqWrapper::~ZmqWrapper()
{
    for (const auto& pair : sessionMap) {
        if (pair.second.socket) {
            int linger = 0;
            zmq_setsockopt(pair.second.socket, ZMQ_LINGER, &linger, sizeof(linger));
            zmq_close(pair.second.socket);
        }
    }

    for (const auto& pair : sessionMap) {
        if (pair.second.context) {
            zmq_ctx_destroy(pair.second.context);
        }
    }
}

void ZmqWrapper::registerSession(std::string ip, int port, zmqPatternEnum pattern, std::string topic)
{
    std::string address = "tcp://" + ip + ":" + std::to_string(port);

    sessionMap[topic].context = zmq_ctx_new();
    sessionMap[topic].socket  = zmq_socket (sessionMap[topic].context, pattern);
    sessionMap[topic].topic   = topic;

    if(pattern == SUBSCRIBE){
        zmq_setsockopt(sessionMap[topic].socket, ZMQ_SUBSCRIBE, topic.c_str(), topic.length());
    }

    if(ip == "*"){
        zmq_bind(sessionMap[topic].socket, address.c_str());
    }
    else{
        zmq_connect(sessionMap[topic].socket, address.c_str());
    }
}

void ZmqWrapper::registerSession(std::string ip, int port, zmqPatternEnum pattern, std::string topic, const CallbackFunction& callback)
{
    std::string address = "tcp://" + ip + ":" + std::to_string(port);

    sessionMap[topic].context  = zmq_ctx_new();
    sessionMap[topic].socket   = zmq_socket (sessionMap[topic].context, pattern);
    sessionMap[topic].topic    = topic;
    sessionMap[topic].callback = callback;

    if(pattern == SUBSCRIBE){
        zmq_setsockopt(sessionMap[topic].socket, ZMQ_SUBSCRIBE, topic.c_str(), topic.length());
    }

    if(ip == "*"){
        zmq_bind (sessionMap[topic].socket, address.c_str());
    }
    else{
        zmq_connect(sessionMap[topic].socket, address.c_str());
    }
}

int ZmqWrapper::pollMessage(std::string &msg, int timeout)
{
    std::vector<zmq_pollitem_t> items;
    {
        for(const auto& pair : sessionMap) {
            zmq_pollitem_t item = { pair.second.socket, 0, ZMQ_POLLIN, 0 };
            items.push_back(item);
        }
    }
    auto res = zmq_poll (items.data(), items.size(), timeout);

    // timeout
    if(res == 0){
        return -1;
    }
    // poll error
    if(res < 0){
        return -1;
    }

    for(const auto& item : items) {
        if (item.revents & ZMQ_POLLIN) {
            zmq_msg_t message;
            zmq_msg_init(&message);
            if (zmq_msg_recv(&message, item.socket, 0) == -1) {
                std::cerr << "Failed to receive message." << std::endl;
                zmq_msg_close(&message);
                return -1;
            }
            std::string data(static_cast<char*>(zmq_msg_data(&message)), zmq_msg_size(&message));
            zmq_msg_close(&message);

            auto delimiter_pos = data.find('$');
            if (delimiter_pos != std::string::npos) {
                std::string topic = data.substr(0, delimiter_pos);
                std::string message_content = data.substr(delimiter_pos + 1);
                msg = message_content;

                if (auto it = sessionMap.find(topic); it != sessionMap.end()) {
                    if (it->second.callback) {
                        it->second.callback(msg, topic);
                    }
                } else {
                    // std::cerr << "Callback function not found for topic: " << topic << std::endl;
                }
            }
            else {
                std::cerr << "Delimiter not found in received message." << std::endl;
            }
        }
    }

    return 0;
}

int ZmqWrapper::sendMessage(std::string msg, std::string topic)
{
    std::string taggedMsg = topic + '$' + msg;
    int len = zmq_send(sessionMap[topic].socket, taggedMsg.c_str(), taggedMsg.size(), 0);

    if (len == -1) {
        // std::cerr << "Failed to send message." << std::endl;
        return -1;
    }

    return 0;
}
