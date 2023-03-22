#ifndef NETWORK_H
#define NETWORK_H

#include<iostream>
#include <stdio.h>

class network {
    //	HANDLE handle;
public:
    virtual ~network() {};
    BOOL createHandle();
    BOOL writeHandle(HANDLE handle, LPCTSTR msg);
    BOOL readHandle() const;

};

#endif // !NETWORK_H


