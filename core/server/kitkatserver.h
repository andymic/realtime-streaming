//============================================================================
// Name        : kitkatserver.h
// Author      : Andy Michel
// Version     : 1.1
// Copyright   : this code is provided "AS IS"
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#pragma once
#include <../utils/sockets/serversocket.h>
#include <string.h>

class KitKatServer{
private:
	ServerSocket * server_sock;
public:
	KitKatServer(const char * ip, int port);
	void PollForStream();
	void BroadCast(const char * ip, int port);
	~KitKatServer();
};