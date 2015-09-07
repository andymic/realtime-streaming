//============================================================================
// Name        : serversocket.cc
// Author      : Andy
// Version     : 1.0
// Copyright   : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include "serversocket.h"
#include <iostream>
#include <unistd.h> //read & write g++
#include <cstdlib>

using namespace std;

ServerSocket::ServerSocket()
{
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0)
   {
      cerr<<"ERROR opening socket";
      exit(1);
   }

   portno = 5001; //something above 5000

   memset((char *) &serv_addr, '\0', sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

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

void ServerSocket::Listen()
{
	/* Now start listening for the clients, here
   * process will go in sleep mode and will wait
   * for the incoming connection
   */
   
   listen(sockfd,5);
   int clilen = sizeof(cli_addr);
   int pid, newsockfd;

   cout<<"The server address: "<<serv_addr.sin_addr.s_addr<<endl;
   cout<<"The port number: "<<portno<<endl;
   cout<<"CMD [netstat -ntp -l] shows process is listening"<<endl;

   while (1)
   {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen);
      if (newsockfd < 0)
      {
         cerr<<"ERROR on accept";
         exit(1);
      }
      
      /* Create child process */
      pid = fork();
      if (pid < 0)
      {
         cerr<<"ERROR on fork";
         exit(1);
      }
      
      if (pid == 0)
      {
         cout<<"New child process created id: "<<pid<<endl;
         close(sockfd);
         EchoClient(newsockfd);
         exit(0);
      }
      else
      {
         close(newsockfd);
      }
   }
}

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