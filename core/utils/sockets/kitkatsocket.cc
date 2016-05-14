#include "kitkatsocket.h"
#include <iostream>
#include <unistd.h> //read & write g++
#include <arpa/inet.h>
#include <cstdlib>
#define TAG "KitKatSocket - "

using namespace std;
KitKatSocket::KitKatSocket(const char * _ip, int _port){
    cout<<TAG<<"Creating socket...\n";
    ip = _ip;
    port = _port;  //something above 5000
}

void KitKatSocket::bindToSocket()
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        cerr<<TAG<<"ERROR opening socket";
        exit(1);
    }
    
    //keep track of the open sockets so we can close them properly before exit
    opened_socks.push_back(sockfd);
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(this->port);
 
    cout<<TAG<<"Binding to ip ["<<this->ip<<"] "
    <<" port ["<<this->port<<"]"<<endl;
    cout<<TAG<<"CMD [netstat -ntp -l] shows process is listening"<<endl;

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        cerr<<TAG<<"ERROR on binding\n";
        exit(1);
    }
}

vector<int> KitKatSocket::getOpenedSockets(){
    return opened_socks;
}

KitKatSocket::~KitKatSocket(){
    
}