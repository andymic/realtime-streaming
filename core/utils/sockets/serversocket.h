//============================================================================
// Name        : serversocket.h
// Author      : Andy
// Version     : 1.0
// Copyright   : this code is provided "AS IS"
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include "kitkatsocket.h"
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

class ServerSocket : public KitKatSocket{
private:
    struct sockaddr_in serv_addr_out; 
public:
	ServerSocket(const char * ip, int port);
	void PollForStream();
	void BroadcastStream(const char * ip, int port);
	~ServerSocket();
};
