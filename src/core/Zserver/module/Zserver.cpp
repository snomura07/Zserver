#include <iostream>
#include <string>
#include <vector>
#include <thread>
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
							5540+i,
							ZmqWrapper::zmqPatternEnum::REPLY,
							"PRIVATE_SESSION"+std::to_string(i),
							std::bind(&Zserver::callback, this, std::placeholders::_1, std::placeholders::_2)
							);
	}

	zmq.registerSession("127.0.0.1",
						5556,
						ZmqWrapper::zmqPatternEnum::PUBLISH,
						"ZSERVER_PUB_SESSION"
						);

	std::thread pubThread([this](){
		while(true){
			std::string sMsg = "[Zserver published] Hello from Zserver!";
			zmq.sendMessage(sMsg, "ZSERVER_PUB_SESSION");
			print("Published message: ", sMsg, " on topic: ZSERVER_PUB_SESSION");
			msleep(1000);
		}
	});

	while(isRunning){
		std::string rMsg = "";
		auto res = zmq.pollMessage(rMsg, -1);
		print("res: ", res);
	}

	pubThread.join();
	return isRunning;
}
