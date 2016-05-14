//============================================================================
// Name        : kitkatclient.h
// Author      : Andy Michel
// Version     : 1.1
// Copyright   : this code is provided "AS IS"
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