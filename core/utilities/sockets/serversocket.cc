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
 
    cout<<"The server address: "<<serv_addr.sin_addr.s_addr<<endl;
    cout<<"The port number: "<<portno<<endl;
    cout<<"CMD [netstat -ntp -l] shows process is listening"<<endl;
    BindToAddress();
}
void ServerSocket::BindToAddress()
{
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        cerr<<"ERROR on binding";
        exit(1);
    }
}

/*UNUSED SOCK_DGRAM*/
int ServerSocket::Listen()
{
    /* Now start listening for the clients, here
    * process will go in sleep mode and will wait
    * for the incoming connection
    */
    // listen(sockfd,5);
    // int clilen = sizeof(cli_addr);
    // int pid, newsockfd;
    // cout<<"The server address: "<<serv_addr.sin_addr.s_addr<<endl;
    // cout<<"The port number: "<<portno<<endl;
    // cout<<"CMD [netstat -ntp -l] shows process is listening"<<endl;
    // while (1)
    // {
        // newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen);
        // if (newsockfd < 0)
        // {
            //  cerr<<"ERROR on accept";
            //  exit(1);
        // }
        // Create child process
        // pid = fork();
        // if (pid < 0)
        // {
            //  cerr<<"ERROR on fork";
            //  exit(1);
        // }
        // if (pid == 0)
        // {
            //  cout<<"Existing Process id: "<<pid<<endl;
            //  int keepAlive = BroadcastStream(newsockfd);
            //  if(keepAlive == -1)
            //  {
                //  cout<<"Keep alive -1...exiting"<<endl;
                //  break;
            //  }
        // }
        // else
        // {
            //  close(newsockfd);
        // }
    // }
    // close(sockfd);
    return 0;
}
int ServerSocket::BroadcastStream()
{
    cout<<"Broadcasting..."<<endl;
    socklen_t addrlen = sizeof(serv_addr);
    int buffsize = 64000;
    uchar rawdata[buffsize];
    memset((char *) rawdata, 0, buffsize);
    vector<uchar> buffer;
    int recv;
    char key;
    namedWindow("Kitkat Server", WINDOW_KEEPRATIO);

    for(;;)
    {
        recv = recvfrom(sockfd, rawdata, buffsize, MSG_DONTWAIT, (struct sockaddr *) &serv_addr, &addrlen);
        if(recv < 0)
        {
            //cerr<<"ERROR reading recvfrom socket"<<endl;
            //exit(1);
            //Set to non-blocking therefore -1 is expected while waiting for data or if frame is dropped
            cout<<"Waiting for frame"<<endl;
        }
        else
        {
            buffer.resize(recv);
            memcpy((char *)(&buffer[0]), rawdata, recv);
            cout<<"packet size received from client"<<recv<<endl;
            
            Mat img = imdecode(Mat(buffer), CV_LOAD_IMAGE_COLOR);

            if(img.data == NULL)
            {
                cerr<<"ERROR could not decode rawdata"<<endl;
                exit(1);
            }

            if (!img.isContinuous())
            {
                img = img.clone();
            }
            imshow("Kitkat Server", img);
            key =(char)waitKey(30);

            if(key == 'q')
            {
                cout<<"User request [close window]"<<endl;
                return -1;
            }
        }
    }
    return 1;
}

/*UNUSED SOCK_DGRAM*/
void ServerSocket::EchoClient(int socket)
{
    int mes;
    char buffer[256];
    memset(buffer, '\0', 256);
    mes = read(socket,buffer,255);
    if (mes < 0)
    {
        cerr<<"ERROR reading from socket";
        exit(1);
    }
    cout<<"Message received from client: "<<buffer<<endl;
    mes = write(socket,"I got your message",18);
    if (mes < 0)
    {
        cerr<<"ERROR writing to socket";
        exit(1);
    }
}
ServerSocket::~ServerSocket()
{
    close(sockfd);
}