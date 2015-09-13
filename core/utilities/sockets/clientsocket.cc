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
using namespace std;
ClientSocket::ClientSocket(const char * addr, int port)
{
    server = gethostbyname(addr);
    portno = port;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); /* Create a socket point http://man7.org/linux/man-pages/man2/socket.2.html*/
    if(server == NULL)
    {
        cerr<<"ERROR, host not found";
        exit(1);
    }
    if (sockfd < 0)
    {
        cerr<<"ERROR opening socket";
        exit(1);
    }
    memset((char *) &serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
}
/*UNUSED SOCK_DGRAM*/
bool ClientSocket::Connect()
{
    // if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    // {
        //  cerr<<"ERROR connecting";
        //  return false;
    // }
    return true;
}
/*UNUSED SOCK_DGRAM*/
int ClientSocket::SendMessage(const char * buffer)
{
    /* Send message to the server */
    int mes = write(sockfd, buffer, strlen(buffer));
    if (mes < 0)
    {
        cerr<<"ERROR writing to socket";
        return (false);
    }
    return (true);
}
/*UNUSED SOCK_DGRAM*/
int ClientSocket::ReadResponse()
{
    char buffer[256];
    memset(buffer, '\0', 256);
    int res = read(sockfd, buffer, 255);
    if(res < 0)
    {
        cerr<<"ERROR while trying to read from socket";
        return (false);
    }
    else
    {
        cout<<buffer<<endl;
    }
    return (true);
}

int ClientSocket::SendStream(Mat mat, int mat_size)
{
    if (!mat.isContinuous())
    {
        mat = mat.clone();
    }
    const int updmax = 64000;
    vector<uchar> buff = vector<uchar>(updmax);
    vector<int> param = vector<int>(2);
    param[0]=CV_IMWRITE_JPEG_QUALITY;
    param[1]=80;//keeps it under 64kb
    //opencv compression
    imencode(".jpg",mat,buff,param);
    cout<<"coded file size(jpg)"<<buff.size()<<endl;
    int mes = 0;

    mes = sendto(sockfd, (const void *)&buff[0], buff.size(), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (mes < 0)
    {
        cerr<<"ERROR writing to udp socket:"<<mes;
        return (false);
    }
    cout<<"Packet size sent :"<<mes<<endl;
    return (true);
}
ClientSocket::~ClientSocket()
{
    close(sockfd);
}