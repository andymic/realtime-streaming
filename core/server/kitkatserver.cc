//============================================================================
// Name        : kitkatserver.cc
// Author      : Andy
// Version     : 1.0
// Copyright   : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include "kitkatserver.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

bool KitKatServer::Listen()
{
	ServerSocket * sc = new ServerSocket();
    sc->Listen();
}