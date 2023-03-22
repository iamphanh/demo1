#include "client.h"
#include "server.h"


client::client(){
		clientM = new mailSlot();
		clientP = new pipe();
		clientS = new winSock();
}
BOOL __stdcall client::connect() const
{
	if (clientM->creatFmail() == 0) {
		/*if (clientM->creatFmail()!=0) {
			std::cout << "Connect failed!!" << std::endl;
			return false;
		}
		else
		{
			std::cout << "Connect successful!!" << std::endl;
			return true;
		}*/
		/*std::cout << ">>>>>>> Connect to server using Mailslot IPC!! <<<<<<<" << std::endl;*/
		return true;
	}
	else if (clientP->creatFpipe() == 0) {
		/*std::cout << ">>>>>>> Connect to server using Pipe IPC!! <<<<<<<" << std::endl;*/
		return true;
		      /*std::cout << "Connect successful!!" << std::endl;	
		 std::cout << "Connect failed!!" << std::endl;*/
		}
	else if (clientS->connectSock() == 0){
		/*if (server::getState()) {
			clientS->acceptConnect();
			if (clientS->connectSock() != 0)
				std::cout << "Connect failed!!" << std::endl;
		}
		else
		{
			std::cout << "Connect successful!!" << std::endl;
		}*/
		/*std::cout << ">>>>>>> Connect to server using Socket IPC!! <<<<<<<" << std::endl;*/
		return true;
	}
	return false;
}

BOOL __stdcall client::disconnect() const
{
	if (clientM->creatFmail() == 0) {
		if (CloseHandle(clientM->getSlot())) {
			return true;
			/*std::cout << "Disconnect successful..." << std::endl;*/
		}
		else
		{
			return false;
			/*std::cout << "Warring: mailSlot don't create!!" << std::endl;*/
		}
	}
	else if (clientP->creatFpipe() == 0) {
		if (DisconnectNamedPipe(clientP->getHpipe())) {
			return true;
			/*std::cout << "Disconnect successful..." << std::endl;*/
		}
		else
		{
			return false;
			/*std::cout << "Warring: Named pipe don't create!!" << std::endl;*/
		}
	}
	else { // server::getIPC == SOCKET
		if (clientS->connectSock()) {
			/*winSock myWinSock;
			SOCKET connectSock = myWinSock.getcnsock();*/
			/*shutdown(clientS->getcnsock(), SD_BOTH);*/
			if (shutdown(clientS->getcnsock(), SD_BOTH) != SOCKET_ERROR) {
				/*std::cout << "Disconnect successful..." << std::endl;*/
				closesocket(clientS->getcnsock());
				return true;
			}
			else
			{
				return false;
				/*std::cout << "Cann't disconnect!! " << std::endl;*/
			}
		}
		else
		{
			return false;
			/*std::cout << "Warring: Socket don't create!!" << std::endl;*/
		}
	}
}

BOOL __stdcall client::sendMsg(wchar_t const* msg)
{
	if (clientM->creatFmail() == 0) {
		if (clientM->getSlot()) {
			int len = lstrlenW(msg);
			len = WideCharToMultiByte(CP_UTF8, 0, msg, len, NULL, 0, NULL, NULL);
			char* buffer = new char[len];
			WideCharToMultiByte(CP_UTF8, 0, msg, len, buffer, len, NULL, NULL);
			//clientM->creatFmail();
			if (!clientM->writeHandle(buffer)) {
				return false;
				/*std::cout << "Erorr: send message failed " << WSAGetLastError() << std::endl;*/
			}
			else {
				return true;
				/*std::cout << "Send message successfull!!" << std::endl;*/
			}

		}
		else {
			return false;
			/*std::cout << "Warring: Not connect to server" << std::endl;*/
		}
	}
	else if (clientP->creatFpipe() == 0) {
		if (clientP->getHpipe()) {
			int len = lstrlenW(msg);
			len = WideCharToMultiByte(CP_UTF8, 0, msg, len, NULL, 0, NULL, NULL);

			char* buffer = new char[len];
			WideCharToMultiByte(CP_UTF8, 0, msg, len, buffer, len, NULL, NULL);
			if (!clientP->writeHandle(buffer)) return false;
			return true;
				/*std::cout << "Erorr: Writing from pipe failed " << GetLastError() << std::endl;*/
		}
		else {
			return false;
			/*std::cout << "Warring: Not connect to server" << std::endl;*/
		}
	}
	else { // server::getIPC == SOCKET
		if (clientS->connectSock() == 0) {
			int len = WideCharToMultiByte(CP_UTF8, 0, msg, -1, NULL, 0, NULL, NULL);
			char* buffer = new char[len];
			WideCharToMultiByte(CP_UTF8, 0, msg, -1, buffer, len, NULL, NULL);
			if (!clientS->writeMessage(clientS->getcnsock(), buffer)) return false;
			return true;
				/*std::cout << "Erorr: Writing from socket failed " << GetLastError() << std::endl;*/
			delete[] buffer;
		}
		else {
			return false;
			/*std::cout << "Warring: Not connect to server" << std::endl;*/
		}
	}
}

BOOL __stdcall client::receiverMsg()
{
	if (clientM->creatFmail() == 0) {
		if (!clientM->readHandle()) return false;
		return true;
				/*std::cout << "Erorr: Reading from mailslot failed " << GetLastError() << std::endl;
			std::cout << "Reading from mailslot successful!!" << std::endl;*/
		
	}
	else if (clientP->creatFpipe() == 0) {
		if (!clientP->readHandle()) return false;
		return true;
				/*std::cout << "Erorr: Reading from pipe failed " << GetLastError() << std::endl;
			std::cout << "Reading from pipe successful!!" << std::endl;*/
	}
	else if (clientS->connectSock() == 0) {
		if (!clientS->readHandle(clientS->getcnsock())) return false;
		return true;
				/*std::cout << "Erorr: Reading from socket failed " << GetLastError() << std::endl;
			std::cout << "Reading from server successful!!" << std::endl;*/
	}
	else {
		return false;
			/*std::cout << "Warring: Not connect to server" << std::endl;*/
	}
}

//void __stdcall client::mainClient() {
//	//client _client;
//	do {
//		if (clientM->creatFmail()==0) {
//			std::cout << "\t\t\t>>>>>>> mailslot ipc <<<<<<< " << std::endl;
//			display::displayC1();
//		}
//		else if (clientP->creatFpipe()==0) {
//			std::cout << "\t\t\t>>>>>>> named pipe ipc <<<<<<< " << std::endl;
//			display::displayC1();
//		}
//		else 
//			if (clientS->connectSock()==0)
//		{
//			std::cout << "\t\t\t>>>>>>> socket ipc <<<<<<< " << std::endl;
//			display::displayC1();
//		}
//		else {
//			HANDLE hchange = CreateSemaphore(NULL, 1, 1, NULL);
//			WaitForSingleObject(hchange, INFINITE);
//			std::cout << "\t\t\t>>>>>>> Create new server from client <<<<<<< " << std::endl;
//			server _server;
//			display::displayS1();
//			ReleaseSemaphore(hchange, 1, NULL);
//		}
//	} while (true);
//	
//}
BOOL WINAPI client::check() {
	if (clientM->creatFmail() != 0 && clientP->creatFpipe() != 0
		&& clientS->connectSock() != 0) {
		return true;
	}
	else {
		return false;
	}
}

client::~client(){
		delete clientM;
		delete clientP;
		delete clientS;
}