#include <iostream>
#include <vector>
#include <string>
#include <ZmqWrapper/ZmqWrapper.h>
#include <msleep.hpp>
#include <print.hpp>

int main(int argc, char *argv[])
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1",
                        5551,
                        ZmqWrapper::zmqPatternEnum::REQUEST,
                        "GGG"
                      );

    std::string smsg = "ggg";
    zmq.sendMessage(smsg, "GGG");

    auto res = zmq.pollMessage(smsg, -1);
    print("Received message: ", smsg);
    msleep(100);
}
