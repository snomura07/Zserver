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

public:
  ZmqWrapper zmq;
};

#endif
