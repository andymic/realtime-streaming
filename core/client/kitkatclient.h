//============================================================================
// Name        : kitkat.cc
// Author      : Andy
// Version     : 1.0
// Copyright   : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#pragma once
#include <../utils/sockets/clientsocket.h>
#include <string.h>

class KitKatClient{
private:
	bool FileExist(const char *filename);
	ClientSocket * client_sock;
public:
	KitKatClient(){}
	int ShowImage(const char * path);
	int ReadVideo(const std::string & filename);
	void SendVideoToServer(const char * addr, int port, const std::string & filepath);
	void ReadStreamFromServer(const char * ip, int port);
	void SendMessage(const char * adr, int port, const char * message);
	~KitKatClient();
};