//============================================================================
// Name        : serversocket.cc
// Author      : Andy Michel
// Version     : 1.1
// Copyright   : this code is provided "AS IS"
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

#define TAG "ServerSocket - "

ServerSocket::ServerSocket(const char * ip, int port) : KitKatSocket(ip, port)
{}

void ServerSocket::PollForStream()
{
    cout<<TAG<<"Polling for stream at ip ["<<ip<<"] port ["<<port<<"]"<<endl;
    bindToSocket();
        
    socklen_t addrlen = sizeof(serv_addr);
    int buffsize = 64000;
    uchar rawdata[buffsize];
    memset((char *) rawdata, 0, buffsize);
    vector<uchar> buffer;
    int recv;

    for(;;)
    {
        recv = recvfrom(sockfd, rawdata, buffsize, MSG_DONTWAIT, (struct sockaddr *) &serv_addr, &addrlen);
        if(recv > 0)
        {
            cout<<TAG<<"Packet size received from client "<<recv<<endl;        
        }
    }
}

//writes the stream back to a different socket
void ServerSocket::BroadcastStream(const char * ip, int port)
{
    bindToSocket();
    cout<<TAG<<"Broadcasting at ip ["<<ip<<"] port ["<<port<<"]"<<endl;
     
    serv_addr_out  = serv_addr;
    serv_addr_out.sin_addr.s_addr = inet_addr(ip);
    serv_addr_out.sin_port = htons(port);
    vector<int> param = vector<int>(2);
    param[0]=CV_IMWRITE_JPEG_QUALITY;
    param[1]=80;//keeps it under 64kb
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
            cout<<TAG<<"Packet size received from client: "<<recv<<endl;
            buffer.resize(recv);
            memcpy((char *)(&buffer[0]), rawdata, recv);
            sent = sendto(sockfd, (const void *)&buffer[0], buffer.size(), 0, (struct sockaddr*)&serv_addr_out, sizeof(serv_addr_out));
            if (sent < 0)
            {
                cerr<<TAG<<"ERROR writing to udp socket:"<<sent;
                exit(-1);
            }

            cout<<TAG<<"Packet size written: "<<sent<<endl;           
        }
    }
}

ServerSocket::~ServerSocket()
{
    for(unsigned int i = 0; i<opened_socks.size(); i++){
        cout<<TAG<<"closing socket "<<opened_socks.at(i)<<endl;
        close(opened_socks.at(i));
    }
}