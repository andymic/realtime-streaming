//============================================================================
// Name : serversocket.cc
// Author  : Andy
// Version : 1.0
// Copyright  : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include "serversocket.h"
#include <iostream>
#include <unistd.h> //read & write g++
#include <arpa/inet.h>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
using namespace std;
using namespace cv;

ServerSocket::ServerSocket(const char * ip, int port)
{
   cout<<"Starting server...\n"; 
   BindToAddress(ip, port);
}

void ServerSocket::BindToAddress(const char * ip, int port)
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        cerr<<"ERROR opening socket";
        exit(1);
    }

    portno = port; //something above 5000
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);
 
    cout<<"Binding to address: "<<serv_addr.sin_addr.s_addr<< " ";
    cout<<"and port number: "<<portno<<endl;
    cout<<"CMD [netstat -ntp -l] shows process is listening"<<endl;

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        cerr<<"ERROR on binding";
        exit(1);
    }
}

void ServerSocket::CaptureStream()
{
    cout<<"Capturing stream..."<<endl;
    socklen_t addrlen = sizeof(serv_addr);
    int buffsize = 64000;
    uchar rawdata[buffsize];
    int recv;

    for(;;)
    {
        recv = recvfrom(sockfd, rawdata, buffsize, MSG_DONTWAIT, (struct sockaddr *) &serv_addr, &addrlen);
        if(recv < 0)
        {
            //Set to non-blocking therefore -1 is expected while waiting for data or if frame is dropped
            cout<<"Waiting for frame"<<endl;
        }
        else
        {
            cout<<"packet size received from client"<<recv<<endl;            
        }
    }
}

//writes the stream back to a different socket
void ServerSocket::BroadcastStream(const char * ip, int port)
{
    cout<<"Starting broadcast..."<<endl;

    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);
    
    socklen_t addrlen = sizeof(serv_addr);
    int buffsize = 64000;
    uchar rawdata[buffsize];
    memset((char *) rawdata, 0, buffsize);
    vector<uchar> buffer;
    int recv, sent;

    for(;;)
    {
        recv = recvfrom(sockfd, rawdata, buffsize, MSG_DONTWAIT, (struct sockaddr *) &serv_addr, &addrlen);
        if(recv > 0)
        {
            cout<<"Packet size received from client"<<recv<<endl;
            buffer.resize(recv);
            memcpy((char *)(&buffer[0]), rawdata, recv);
            
            sent = sendto(sockfd, (const void *)&buffer[0], buffer.size(), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
            if (sent < 0)
            {
                cerr<<"ERROR writing to udp socket:"<<sent;
                exit(-1);
            }

            cout<<"Packet size written:"<<sent<<endl;           
        }
    }
}


// int ServerSocket::BroadcastStream()
// {
//     cout<<"Broadcasting..."<<endl;
//     socklen_t addrlen = sizeof(serv_addr);
//     int buffsize = 64000;
//     uchar rawdata[buffsize];
//     memset((char *) rawdata, 0, buffsize);
//     vector<uchar> buffer;
//     int recv;
//     char key;
//     namedWindow("Kitkat Server", WINDOW_KEEPRATIO);

//     for(;;)
//     {
//         recv = recvfrom(sockfd, rawdata, buffsize, MSG_DONTWAIT, (struct sockaddr *) &serv_addr, &addrlen);
//         if(recv < 0)
//         {
//             //cerr<<"ERROR reading recvfrom socket"<<endl;
//             //exit(1);
//             //Set to non-blocking therefore -1 is expected while waiting for data or if frame is dropped
//             cout<<"Waiting for frame"<<endl;
//         }
//         else
//         {
//             buffer.resize(recv);
//             memcpy((char *)(&buffer[0]), rawdata, recv);
//             cout<<"packet size received from client"<<recv<<endl;
            
//             Mat img = imdecode(Mat(buffer), CV_LOAD_IMAGE_COLOR);

//             if(img.data == NULL)
//             {
//                 cerr<<"ERROR could not decode rawdata"<<endl;
//                 exit(1);
//             }

//             if (!img.isContinuous())
//             {
//                 img = img.clone();
//             }
//             imshow("Kitkat Server", img);
//             key =(char)waitKey(30);

//             if(key == 'q')
//             {
//                 cout<<"User request [close window]"<<endl;
//                 return -1;
//             }
//         }
//     }
//     return 1;
// }

ServerSocket::~ServerSocket()
{
    close(sockfd);
}