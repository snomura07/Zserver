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
						"HANDSHAKE",
						[this](std::string rMsg, std::string topic) {
							std::string sMsg = "[Zserver received] " + rMsg;
							zmq.sendMessage(sMsg);
						});

  while(isRunning){
    std::string rMsg = "";
    auto res = zmq.pollMessage(rMsg, -1);
  }

  return isRunning;
}
