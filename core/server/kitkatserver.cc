//============================================================================
// Name        : kitkatserver.cc
// Author      : Andy Michel
// Version     : 1.1
// Copyright   : this code is provided "AS IS"
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include "kitkatserver.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <fstream>
#include <string.h>
#include <cstring>
#include <vector>
#include <iostream>

#define TAG "KitKatServer - "

KitKatServer::KitKatServer(const char * ip, int port)
{
    std::cout<<TAG<<"starting...\n";
	server_sock = new ServerSocket(ip, port);
}

void KitKatServer::PollForStream(){
    server_sock->PollForStream();
}

void KitKatServer::BroadCast(const char * ip, int port)
{    
    server_sock->BroadcastStream(ip, port);
}

KitKatServer::~KitKatServer(){
    delete server_sock;
}