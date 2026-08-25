#ifndef INCLUDED_ZSERVER
#define INCLUDED_ZSERVER

#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>

class Zserver
{
public:
  Zserver();
  ~Zserver();

  bool run();
  void callback(std::string msg, std::string topic);

public:
  ZmqWrapper zmq;
};

#endif
