//============================================================================
// Name        : serversocket.h
// Author      : Andy
// Version     : 1.0
// Copyright   : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#pragma once
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

class ServerSocket{
private:
	int sockfd, portno;
    struct sockaddr_in serv_addr, cli_addr;
    void BindToAddress();  
    void EchoClient(int socket);
    void BroadcastStream(int socket);
public:
	ServerSocket();
	void Listen();
	~ServerSocket();
};

// int main()
// {
// 	ServerSocket * sc = new ServerSocket();
// 	sc->Listen();
//   return 0;
// }