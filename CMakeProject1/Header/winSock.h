#ifndef WINSOCK_H
#define WINSOCK_H
#include <ws2tcpip.h>
#include<winsock2.h>
#include "network.h"

class winSock : public network {
private:
    static SOCKET listenSocket;
    static SOCKET clientSock;
    static SOCKET m_connectSock;
    /*struct addrinfo* result = NULL;
    struct addrinfo* ptr = NULL, hints;*/

public:
    winSock();
    ~winSock();
    BOOL WINAPI createHandle();
    BOOL WINAPI writeMessage(SOCKET socket, const char* msg);
    BOOL WINAPI readHandle(SOCKET socket);
    BOOL WINAPI acceptConnect();
    static SOCKET getlsock();
    static SOCKET getcsock();
    static SOCKET getcnsock();
    int WINAPI connectSock();

};

#endif
