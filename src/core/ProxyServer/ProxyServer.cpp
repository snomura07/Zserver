#include <iostream>
#include <string>
#include <thread>
#include <zmq.h>

void invokeProxyServer()
{
	void* context = zmq_ctx_new();
	void* pubSock = zmq_socket(context, ZMQ_XPUB);
	void* subSock = zmq_socket(context, ZMQ_XSUB);

	std::string pubAddress = std::string("tcp://*:5555");
	std::string subAddress = std::string("tcp://*:5556");

	zmq_bind(pubSock, pubAddress.c_str());
	zmq_bind(subSock, subAddress.c_str());
	zmq_proxy(subSock, pubSock, nullptr);

	zmq_close(pubSock);
	zmq_close(subSock);
	zmq_ctx_destroy(context);
}

int main()
{
    invokeProxyServer();

    return 0;
}
