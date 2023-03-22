#define UNICODE
#define _UNICODE
#include "server.h"
#include "client.h"
#include "display.h"
#include"controler.h"
#include <thread>
#include <mutex>

//void mainS() {
//	server _server;
//	_server.mainServer();
//	//server::mainServer();
//}
//void mainC() {
//	client _client;
//	_client.mainClient();
//}

//int main()
//{
//	
//	BOOL q = true;
//	do {
//		char cstr = display::displayMenu();
//		if (cstr == '1') {
// 			std::thread server_Thread(mainS);
//			server_Thread.join();
//		}
//		else if (cstr == '2')
//		{
//			std::thread client_Thread(mainC);
//			client_Thread.join();
//		}
//		else if (cstr == '3') {
//			q = false;
//			break;
//		}
//		else {
//			std::cout << "\n\t\tErorr:invalid input characters" << std::endl;
//			display(q);
//	
//		}
//	} while (q);
//
//	return 0;
//
//}

int main() {
	std::mutex mutexS;
	char c = display::displayMenu();
	do {
		if (c == '1') {
			mutexS.lock();
			server* _server = new server();
			controler::controlerS(*_server);
			//continue;
			mutexS.unlock();
			break;

		}
		else if (c == '2') {
			client* _client = new client();
			controler::controlerC(*_client);
			continue;

		}
		else if (c == '3') {
			exit(1);
		}
		else {
			std::cout << "Input character invailed!!" << std::endl;
			break;
		}
	} while (true);
	
}