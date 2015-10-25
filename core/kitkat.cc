//============================================================================
// Name        : kitkat.cc
// Author      : Andy
// Version     : 1.0
// Copyright   : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include <../client/kitkatclient.h>
#include <../server/kitkatserver.h>
#include <thread>
#include <chrono> 
#include <string>

#define vid_path "/home/andy/Videos/Moving Takahashi-HD.mp4"

using namespace std;

const char * ip = "127.0.0.1";
int port_cp = 5134, port_bd = 5136;

void LaunchServer()
{

	cout<<"Kitkatserver starting..."<<endl;
	KitKatServer * s = new KitKatServer(ip, port_cp);
	s->BroadCast(ip, port_bd);
}

void LaunchClient()
{
	KitKatClient * k = new KitKatClient();
    k->SendVideoToServer(ip, port_cp, vid_path);
}
int main( int argc, char** argv )
{
	string arg = argv[1];

	if(arg =="server")
		LaunchServer();
	else if(arg =="client")
     	LaunchClient();
    else
    	cout<<"Please specify whether to start server or client"<<endl;

    return 0;
}