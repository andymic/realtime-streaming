//============================================================================
// Name        : clientsocket.h
// Author      : Andy Michel
// Version     : 1.1
// Copyright   : this code is provided "AS IS"
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include "kitkatsocket.h"
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>

class ClientSocket : public KitKatSocket {
private:
    struct hostent *server;
public:
	ClientSocket(const char * ip, int port);
	int SendStream(cv::Mat mat, int mat_size);
	void OpenSocket();
	void CaptureStream(const char * ip, int port);
	~ClientSocket();
};
