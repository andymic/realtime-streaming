//============================================================================
// Name : kitkatsocket.h
// Author  : Andy
// Version : 1.0
// Copyright  : Use this code at your own risk!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>

#ifndef kitkatclient_h
#define kitkatclient_h

class KitKatSocket{
protected:
    const char * ip;
    int sockfd, port;
    std::vector<int> opened_socks;
    struct sockaddr_in serv_addr;
public:
    KitKatSocket(const char * _ip, int _port);
    void bindToSocket();
    std::vector<int>getOpenedSockets();
    ~KitKatSocket(); 
};
#endif 