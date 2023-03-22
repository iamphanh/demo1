
#ifndef SERVER_H
#define SERVER_H


#include "client.h"
#include"mailSlot.h"
#include"pipe.h"
#include"winSock.h"
#include "display.h"


enum MyEnum
{
	MAIL,
	PIPE,
	SOCKETT
};
class server {

private:
	static BOOL state;
	static MyEnum mode;
	mailSlot *serverM;
	pipe *serverP;
	winSock *serverS;

public:
	server();
	~server();
	static void WINAPI chooseIPC(char msg);
	static MyEnum getIPC();
	BOOL WINAPI start();
	BOOL WINAPI stop();
	BOOL WINAPI sendMsg(const wchar_t* msg);
	BOOL WINAPI receiverMsg();
	static BOOL getState();
	BOOL WINAPI checkS();
	static BOOL setState(BOOL x);
	/*void WINAPI mainServer();*/
};

//BOOL server::state = TRUE;

//inline BOOL server::getState() {
//	return state;
//};
//
//inline BOOL server::setState(BOOL x) {
//	return state = x;
//}
//inline MyEnum server::getIPC() {
//	return mode;
//};

#endif // !SERVER_H