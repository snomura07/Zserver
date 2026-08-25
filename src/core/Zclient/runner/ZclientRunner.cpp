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
                        5559,
                        ZmqWrapper::zmqPatternEnum::REQUEST,
                        "PRIVATE_SESSION9"
                      );

    std::string smsg = "mokemoke";
    print("Sending message: ", smsg);
    zmq.sendMessage(smsg, "PRIVATE_SESSION9");

    print("Polling for response...");
    auto res = zmq.pollMessage(smsg, -1);
    print("Received message: ", smsg);
    msleep(100);
}
