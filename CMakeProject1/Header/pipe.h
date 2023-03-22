#ifndef PIPE_H
#define PIPE_H
#include <conio.h>
#include<windows.h>
#include "network.h"
class pipe : public network {
private:
    static HANDLE hpipe;
    static const LPCTSTR namePipe;
    //static PHANDLE hread;
    //static PHANDLE hwrite;

public:
    pipe();
    ~pipe();
    BOOL createHandle();
    BOOL writeHandle(LPCTSTR msg);
    BOOL readHandle();
    HANDLE WINAPI getHpipe() const;
    int WINAPI creatFpipe();
    static LPCTSTR getnamePipe();
};
#endif // PIPE_H

