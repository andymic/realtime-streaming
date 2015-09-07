//============================================================================
// Name        : clientsocket.h
// Author      : Andy
// Version     : 1.0
// Copyright   : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#pragma once
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

class ClientSocket{
private:
	int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
public:
	ClientSocket(const char * addr, int port);
	bool Connect();
	int SendMessage(const char * buffer);
	int ReadResponse();
	~ClientSocket(){}
};

int main()
{
	ClientSocket * cs = new ClientSocket("0", 5001);
	cs->Connect();
	cs->SendMessage("This is a test from the client");
	cs->ReadResponse();
  return 0;
}