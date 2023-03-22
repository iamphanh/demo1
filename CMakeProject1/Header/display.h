#ifndef DISPLAY_H
#define DISPLAY_H

#include "server.h"
#include "client.h"
class server;
class display {
public:
    display();
    ~display();
    static char displayMenu();
    static void displayS1(server & _server);
    static char displayS2();
    static char displayC1();
};
#endif // DISPLAY_H
