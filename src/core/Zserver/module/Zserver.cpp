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
							print("Received message: ", rMsg, " on topic: ", topic);
							std::string sMsg = "[Zserver received1] " + rMsg;
							zmq.sendMessage(sMsg, topic);
						});

	zmq.registerSession("*",
						5551,
						ZmqWrapper::zmqPatternEnum::REPLY,
						"GGG",
						[this](std::string rMsg, std::string topic) {
							print("Received message: ", rMsg, " on topic: ", topic);
							std::string sMsg = "[Zserver received2] " + rMsg;
							zmq.sendMessage(sMsg, topic);
						});

  while(isRunning){
    std::string rMsg = "";
    auto res = zmq.pollMessage(rMsg, -1);
	print("res: ", res);
  }

  return isRunning;
}
