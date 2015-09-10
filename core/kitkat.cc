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

#define img_path "/home/andy/Pictures/rockon.jpg"
#define vid_path "/home/andy/Videos/dfs.avi"

using namespace std;

void LaunchServer()
{
	cout<<"Kitkatserver starting..."<<endl;
	KitKatServer * s = new KitKatServer();
	s->Listen();
}

void LaunchClient()
{
	KitKatClient * k = new KitKatClient();
	// for(int i=0; i<100; i++)
	// {

	// 	k->SendMessage("0", 5001, "Test message from client");
	// 	this_thread::sleep_for (chrono::seconds(1));
	// }
    k->SendVideoToServer("0", vid_path, 5001);
    //k->ReadVideo(vid_path);
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