#include <iostream>
#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>
#include <print.hpp>
#include <msleep.hpp>
#include "Zserver.h"
// #include "Gateway.h"
// #include "Zdata.h"

Zserver::Zserver()
{
  // config.read();

  // base用の設定
  // zmq.registerSession(
  //     "*",
  //     config.master.zserverPort,
  //     ZmqWrapper::zmqPatternEnum::REPLY,
  //     config.master.zserverTopic
  // );
}

Zserver::~Zserver(){}

bool Zserver::run()
{
  bool isRunning = true;
  zmq.registerSession("127.0.0.1",
                      5556,
                      ZmqWrapper::zmqPatternEnum::PUBLISH,
                      "HANDSHAKE"
                    );

  while(isRunning){
    std::string sMsg = "Hello, Zserver!";
    zmq.sendMessage(sMsg);

    msleep(100);
    // std::string request = "";
    // zmq.pollMessage(request, -1);

  }

  return isRunning;
}
