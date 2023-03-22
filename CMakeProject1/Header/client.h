#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <windows.h>
#include "server.h"
#include"mailSlot.h"
#include"pipe.h"
#include"winSock.h"
#include "display.h"


class client {
private:
	mailSlot* clientM;
	pipe* clientP;
	winSock* clientS;
	//void WINAPI changeMode() const;
	//DWORD WINAPI ThreadFunc();
	/*static DWORD WINAPI ThreadFunc(LPVOID lpParam);*/
public:
	client();
	~client();
	BOOL WINAPI connect() const;
	BOOL WINAPI disconnect() const;
	BOOL WINAPI sendMsg(wchar_t const* msg);
	BOOL WINAPI receiverMsg();
	BOOL WINAPI check();
	/*void WINAPI mainClient();*/

};

#endif // CLIENT_H
