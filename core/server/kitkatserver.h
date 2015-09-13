//============================================================================
// Name        : kitkatserver.h
// Author      : Andy
// Version     : 1.0
// Copyright   : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#pragma once
#include <../utilities/sockets/serversocket.h>
#include <string.h>

class KitKatServer{
public:
	KitKatServer(){}
	void BroadCast(const char * ip, int port);
	~KitKatServer(){}
};