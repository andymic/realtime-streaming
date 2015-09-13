//============================================================================
// Name        : kitkat.cc
// Author      : Andy
// Version     : 1.0
// Copyright   : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#pragma once
#include <../utilities/sockets/clientsocket.h>
#include <string.h>

class KitKatClient{
private:
	bool FileExist(const char *filename);
public:
	KitKatClient(){}
	int ShowImage(const char * path);
	int ReadVideo(const std::string & filename);
	bool SendVideoToServer(const char * addr, int port, const std::string & filepath);
	void SendMessage(const char * adr, int port, const char * message);
	~KitKatClient(){}
};