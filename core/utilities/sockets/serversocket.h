//============================================================================
// Name        : serversocket.h
// Author      : Andy
// Version     : 1.0
// Copyright   : this code is provided "AS IS"
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#pragma once
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

class ServerSocket{
private:
	int sockfd, portno;
    struct sockaddr_in serv_addr;
    void BindToAddress(const char * ip, int port);  
public:
	ServerSocket(const char * ip, int port);
	void CaptureStream();
	void BroadcastStream(const char * ip, int port);
	~ServerSocket();
};
