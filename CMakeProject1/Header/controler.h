#ifndef CONTROLER_H
#define CONTROLER_H

#define UNICODE
#define _UNICODE
#include "server.h"
#include "client.h"
#include "display.h"
class controler {
private:
    static display _display;
public:
    controler();
    ~controler();
    static void WINAPI controlerS(server &_server);
    static void WINAPI controlerC(client &_client);
    static void _controler();
};

#endif 