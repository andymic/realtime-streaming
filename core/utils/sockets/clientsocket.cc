//============================================================================
// Name : clientsocket.cc
// Author  : Andy
// Version : 1.0
// Copyright  : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include "clientsocket.h"
#include <iostream>
#include <unistd.h> //read & write g++
#include <cstdlib>
#include <arpa/inet.h>
#include <thread>
#include <chrono> 

using namespace std;
using namespace cv;

#define TAG "ClientSocket - "

ClientSocket::ClientSocket(const char * ip, int port) : KitKatSocket(ip, port)
{}

void ClientSocket::OpenSocket(){
    server = gethostbyname(ip);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); /* Create a socket point http://man7.org/linux/man-pages/man2/socket.2.html*/
   
    if(server == NULL){
        cerr<<TAG<<"ERROR, host not found";
        exit(1);
    }
    
    if (sockfd < 0){
        cerr<<TAG<<"ERROR opening socket";
        exit(1);
    }
    
    memset((char *) &serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);
    
    cout<<TAG<<"Opened socket at ip ["<<ip<<"] port ["<<port<<"]"<<endl;
}

int ClientSocket::SendStream(Mat mat, int mat_size)
{
    const int updmax = 64000;
    vector<uchar> buff = vector<uchar>(updmax);
    vector<int> param = vector<int>(2);
    param[0]=CV_IMWRITE_JPEG_QUALITY;
    param[1]=80;//keeps it under 64kb
    int mes = 0;
    
    if (!mat.isContinuous())
    {
        mat = mat.clone();
    }

    imencode(".jpg",mat,buff,param); //opencv compression
    cout<<TAG<<"encoded file size(jpg) "<<buff.size()<<endl;
    mes = sendto(sockfd, (const void *)&buff[0], buff.size(), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    if (mes < 0)
    {
        cerr<<TAG<<"ERROR writing to udp socket:"<<mes;
        return (false);
    }
    
    cout<<TAG<<"Packet size sent :"<<mes<<endl;
    return (true);
}

void ClientSocket::CaptureStream(const char * _ip, int _port){
    this->ip = _ip;
    this->port = _port;
    
    bindToSocket();
    socklen_t addrlen = sizeof(serv_addr);
    int buffsize = 64000;
    uchar rawdata[buffsize];
    memset((char *) rawdata, 0, buffsize);
    vector<uchar> buffer;
    int recv;
    char key;
    bool started = false;
    
        this_thread::sleep_for(chrono::milliseconds(2000));
    return;
    namedWindow("Kitkat Client", WINDOW_KEEPRATIO);
    
    cout<<TAG<<"Polling for stream from server..."<<endl;
    for(;;)
    {
        recv = recvfrom(sockfd, rawdata, buffsize, MSG_DONTWAIT, (struct sockaddr *) &serv_addr, &addrlen);
        if(recv < 0)
        {
            //Set to non-blocking therefore -1 is expected while waiting for data or if frame is dropped
            if(started)
                cout<<TAG<<"Packet dropped..."<<endl;
        }
        else
        {
            started = true;
            cout<<TAG<<"packet size read from server socket "<<recv<<endl; 
            //buffer.reserve(recv);
            buffer.resize(recv);
            memcpy((char *)(&buffer[0]), rawdata, recv);
            
            Mat img = imdecode(Mat(buffer), CV_LOAD_IMAGE_COLOR);

            if(img.data == NULL)
            {
                cerr<<TAG<<"ERROR could not decode rawdata"<<endl;
                exit(1);
            }

            if (!img.isContinuous())
            {
                img = img.clone();
            }
            
            imshow("Kitkat Client", img);
            key =(char)waitKey(30);

            if(key == 'q')
            {
                cout<<TAG<<"User request [close window]"<<endl;
                
                destroyWindow("Kitkat Client");
                exit(1);
            }           
        }
    }
   
}

ClientSocket::~ClientSocket()
{
    for(unsigned int i = 0; i<opened_socks.size(); i++){
        cout<<TAG<<"closing socket "<<opened_socks.at(i)<<endl;
        close(opened_socks.at(i));
    }
}