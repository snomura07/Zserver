#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <ZmqWrapper/ZmqWrapper.h>
#include <msleep.hpp>
#include <print.hpp>

int main(int argc, char *argv[])
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1",
                        5549,
                        ZmqWrapper::zmqPatternEnum::REQUEST,
                        "PRIVATE_SESSION9"
                      );

    zmq.registerSession("127.0.0.1",
                    5555,
                    ZmqWrapper::zmqPatternEnum::SUBSCRIBE,
                    "ZSERVER_PUB_SESSION"
                    );

    std::thread pollThread([&zmq](){
        while(true){
            std::string rMsg = "";
            auto res = zmq.pollMessage(rMsg, -1, "ZSERVER_PUB_SESSION");
            print("Received message: ", rMsg);
        }
    });

    std::string smsg = "mokemoke";
    print("Sending message: ", smsg);
    zmq.sendMessage(smsg, "PRIVATE_SESSION9");

    print("Polling for response...");
    auto res = zmq.pollMessage(smsg, -1, "PRIVATE_SESSION9");
    print("Received message: ", smsg);
    msleep(100);

    pollThread.join();
}
