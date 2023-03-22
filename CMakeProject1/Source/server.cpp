#include "server.h"
#include<stdio.h>
#include <winsock2.h>
#include "client.h"

server::server(){
	/*if(mode == MAIL)
		serverM = new mailSlot();
	else if (mode == PIPE)
		serverP = new pipe();
	else
		serverS = new winSock();*/
	serverM = new mailSlot();
	serverP = new pipe();
	serverS = new winSock();
}
inline BOOL server::getState() {
	return state;
};

inline BOOL server::setState(BOOL x) {
	return state = x;
}
inline MyEnum server::getIPC() {
	return mode;
};
enum MyEnum server::mode = MyEnum::SOCKETT;
BOOL server::state = false;
void __stdcall server::chooseIPC(char msg)
{

		if (msg == 'm' || msg == 'M') {
			server::mode = MAIL;
		}
		else if (msg == 'p' || msg == 'P') {
			server::mode = PIPE;
		}
		else if ( msg == 'S' || msg == 's') {
			server::mode = SOCKETT;
		}
		else {
			std::cerr << "Erorr: Invalid input variable!!\n"
				<< "Please choose 's' or 'p' or 'm' " << std::endl;
		}

};

BOOL __stdcall server::start()
{
	if (server::getIPC() == MAIL) {

		while (checkS()) {
			//if (!serverM->readHandle()) return false;
			/*std::cout << "Waiting connect from client..." << std::endl;*/
			setState(true);
			return true;
			Sleep(1000);
		}
		return false;
	}
	else if (server::getIPC() == PIPE) {
		while (checkS()) {
			/*std::cout << "Waiting connect from client..." << std::endl;*/
			setState(true);
			Sleep(1000);
			return true;
		}
		return false;
	}
	else {
		if (checkS()) {
			/*std::cout << "Waiting connect from client..." << std::endl;*/
			serverS->acceptConnect();
			setState(true);
			return true;
			//Sleep(1000);
		}
		return false;
	}
};

BOOL __stdcall server::stop() {
	if (server::getIPC() == MAIL) {
		if (server::getState()) {
				setState(false);
				CloseHandle(serverM->getSlot());
				/*std::cout << "Stop listening..." << std::endl;*/
				return true;
		}
		else{
			/*std::cout << "Warring: mailSlot don't create!!" << std::endl;*/
			return false;
		}
	}
	else  if (server::getIPC() == PIPE) {
		if (server::getState()) {
			if (DisconnectNamedPipe(serverP->getHpipe())) {
				CloseHandle(serverP->getHpipe());
				setState(false);
				/*std::cout << "Stop listening..." << std::endl;*/
				return true;
			}
			else
			{
				return false;
				/*std::cout << "Cann't close Named pipe!! " << std::endl;*/
			}
		}
		else
		{
			return false;
		}
	}
	else { // mode == SOCKETT
		if (server::getState()) {
			if (shutdown(serverS->getlsock(), SD_BOTH) == SOCKET_ERROR) {
				/*std::cout << "Stop listen failed with: " << WSAGetLastError() << std::endl;*/
				closesocket(serverS->getlsock());
				WSACleanup();
				return false;
			}
			else {
				setState(false);
				/*std::cout << "Stop listen successful!!" << std::endl;*/
				closesocket(serverS->getlsock());
				WSACleanup();
				return true;
			}
		}
	}
};

BOOL __stdcall server::sendMsg(const wchar_t* msg)
{
	if (server::getIPC() == MAIL) {
		if (server::getState()) {
			int len = lstrlenW(msg);
			len = WideCharToMultiByte(CP_UTF8, 0, msg, len, NULL, 0, NULL, NULL);

			char* buffer = new char[len];
			WideCharToMultiByte(CP_UTF8, 0, msg, len, buffer, len, NULL, NULL);
			//serverM->getSlot();
			if (!serverM->writeHandle(buffer))  return false;
			return true;
		}
		else
		{
			return false;
			/*std::cout << "Warring: mailSlot don't create!!" << std::endl;*/
		}
	}
	else if (server::getIPC() == PIPE) {
		if (server::getState()) {
			int len = lstrlenW(msg);
			len = WideCharToMultiByte(CP_UTF8, 0, msg, len, NULL, 0, NULL, NULL);

			char* buffer = new char[len];
			WideCharToMultiByte(CP_UTF8, 0, msg, len, buffer, len, NULL, NULL);
			if (!serverP->writeHandle(buffer)) return false;
			return true;
		}
		else
		{
			return false;
			/*std::cout << "Warring: Named pipe don't create!!" << std::endl;*/
		}
}
	else { //  mode == SOCKETT
		if (server::getState()) {
			int len = lstrlenW(msg);
			len = WideCharToMultiByte(CP_UTF8, 0, msg, len, NULL, 0, NULL, NULL);

			char* buffer = new char[len];
			WideCharToMultiByte(CP_UTF8, 0, msg, len, buffer, len, NULL, NULL);

			if (serverS->writeMessage(serverS->getcsock(), buffer) == false) return false;
			delete[] buffer;
			return true;

		}
		else
		{
			return true;
			/*std::cout << "Warring: socket don't create!!" << std::endl;*/
		}
	}
};

BOOL __stdcall server::receiverMsg()
{
	if (server::getIPC() == MAIL) {
		if (server::getState()) {
			if (!serverM->readHandle()) return false;
			return true;
				/*std::cout << "Not message in mailslot!!" << std::endl;*/
		}
		else
		{
			return false;
			/*std::cout << "Warring: mailSlot don't create!!" << std::endl;*/
		}
	}
	else if (server::getIPC() == PIPE) {
		if (server::getState()) {
			if (!serverP->readHandle()) return false;
			return true;
				/*std::cout << "Not message in pipe!!" << std::endl;*/
		}
		else
		{
			return false;
			/*std::cout << "Warring: mailSlot don't create!!" << std::endl;*/
		}
	}
	else { //  mode == SOCKETT
		if (server::getState()) {
			serverS->acceptConnect();
			if (serverS->readHandle(serverS->getcsock()) == false)  return false;
			return true;
				/*std::cout << "Not message in socket!!" << std::endl;*/

		}
		else {
			return false;
			/*std::cout << "Warring: socket don't create!!" << std::endl;*/
		}
	}
}
//void __stdcall server::mainServer() {
//	server _server;
//	char q = true;
//	do{
//			display::displayS1();
//			if (server::getIPC() == MAIL) {
//				std::cout << "\t\t\t>>>>>>> mailslot ipc <<<<<<< " << std::endl;
//				display::displayS2();
//			}
//			else if (server::getIPC() == PIPE) {
//				std::cout << "\t\t\t>>>>>>> named pipe ipc <<<<<<< " << std::endl;
//				display::displayS2();
//			}
//			else { //  server::getipc() == sockett
//				std::cout << "\t\t\t>>>>>>> socket ipc <<<<<<< " << std::endl;
//				display::displayS2();
//			}
//
//	} while (true);
//
//}
BOOL WINAPI server::checkS() {
	if (serverM->createHandle() == false  || serverP->createHandle() == false || serverS->createHandle() == false) {
		//server::stop();
		return true;
	}
	else return false;
}
server::~server(){
	/*if(mode == MAIL)
		delete serverM;
	else if(mode == PIPE)
		delete serverP;
	else 
		delete serverS;*/
	delete serverM;
	delete serverP;
	delete serverS;
}
