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

void Zserver::callback(std::string msg, std::string topic)
{
	print("Received message: ", msg, " on topic: ", topic);
	std::string sMsg = "[Zserver received] " + msg;
	zmq.sendMessage(sMsg, topic);
}

bool Zserver::run()
{
	print("Zserver is running...");

	bool isRunning = true;

	for(int i=0; i<10; i++){
		zmq.registerSession("*",
							5550+i,
							ZmqWrapper::zmqPatternEnum::REPLY,
							"PRIVATE_SESSION"+std::to_string(i),
							std::bind(&Zserver::callback, this, std::placeholders::_1, std::placeholders::_2)
							);
	}

  while(isRunning){
    std::string rMsg = "";
    auto res = zmq.pollMessage(rMsg, -1);
	print("res: ", res);
  }

  return isRunning;
}
