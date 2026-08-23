#include <iostream>
#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>
#include <print.hpp>
#include <msleep.hpp>
#include "Zserver.h"

Zserver::Zserver()
{
}

Zserver::~Zserver(){}

bool Zserver::run()
{
  print("Zserver is running...");

  bool isRunning = true;
  zmq.registerSession("*",
                      5550,
                      ZmqWrapper::zmqPatternEnum::REPLY,
                      "HANDSHAKE"
                    );

  while(isRunning){
    std::string rMsg = "";
    auto res = zmq.pollMessage(rMsg, -1);
    print("Received message: ", rMsg);

    std::string sMsg = "[Hello, Zserver] " + rMsg;
    zmq.sendMessage(sMsg);
  }

  return isRunning;
}
