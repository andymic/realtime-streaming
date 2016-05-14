//============================================================================
// Name        : kitkat.cc
// Author      : Andy Michel
// Version     : 1.1
// Copyright   : this code is provided "AS IS"
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include <../client/kitkatclient.h>
#include <../server/kitkatserver.h>
#include <thread>
#include <chrono> 
#include <string>

#define vid_path ""

using namespace std;

const char * receving_ip = "192.x.x.x"; //stream sent android camera
const char * broadcast_ip = "127.0.0.1";

int recv_port = 5134, brd_port = 5136;

void LaunchServer()
{	
	KitKatServer * s = new KitKatServer(receving_ip, recv_port);
	s->BroadCast(broadcast_ip, brd_port);
	delete s;
}

void LaunchClient()
{
	KitKatClient * k = new KitKatClient();
	//k->SendVideoToServer(ip, port_cp, vid_path);
	k->ReadStreamFromServer("127.0.0.1", brd_port);
	delete k;
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