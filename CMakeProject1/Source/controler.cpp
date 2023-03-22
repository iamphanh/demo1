#include<controler.h>
#include<mutex>
controler::controler() {}
controler::~controler() {}

void controler::controlerS(server& _server)
{
	/*std::mutex mutexS;
	mutexS.lock();*/
	if (_server.checkS()) {
		std::cout << "Server already existes!!" << std::endl;
		Sleep(1000);
		exit(1);
	} 
	_display.displayS1(_server);
	if (_server.start()) {
		std::cout << "Server start successfull!!!" << std::endl;
	}
	else {
		std::cout << "Server start falied!!!" << std::endl;
		Sleep(1000);
		exit(1);
	}
	char str = display::displayS2();
	//do {
		if (str == '1') {
			if (_server.stop()) {
				std::cout << "Server stop successful!!" << std::endl;
			}
			else {
				std::cout << "Server stop failed!!" << std::endl;
			}
		}
		else if (str == '2') {
			std::cin.ignore();
			std::string str;
			std::cout << "Enter message: ";
			std::getline(std::cin, str);

			int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
			wchar_t* wstr = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);
			LPCTSTR lpMsg = wstr;
			if (_server.sendMsg(lpMsg)) {
				std::cout << "Send message successful!!" << std::endl;
			}
			else {
				std::cout << "Send message failed!!" << std::endl;
			}
		}
		else if (str == '3') {
			if (_server.receiverMsg()) {
				std::cout << "Send message successful!!" << std::endl;
			}
			else {
				std::cout << "Send message failed!!" << std::endl;
			}
		}
		else if (str == '4') {
			//continue;
			display::displayMenu();

		}
		else if (str == '5') {
			exit(1);
		}
		else
		{
			std::cout << "\n\t\tErorr:Invalid input characters" << std::endl;
			//continue;
		}

	/*	mutexS.unlock();*/
	/*} while (true);*/

}

void WINAPI controler::controlerC(client& _client)
{
	std::mutex clientS;
	//do {
		char c = _display.displayC1();
		if (_client.connect()) {
			std::cout << "Client connect successfull!!!" << std::endl;
		}
		else {
			if (_client.check()) {
				clientS.lock();
				std::cout << "Create new server from client!!" << std::endl;
				server* _server = new server();
				controlerS(*_server);
				clientS.unlock();

			}
			std::cout << "Client connect falied!!!" << std::endl;
		}
		if (c == '1') {
			//client _client;
			_client.disconnect();

		}
		else if (c == '2')
		{
			//client _client;
			std::cin.ignore();
			std::string str;
			std::cout << "Message: ";
			std::getline(std::cin, str);
			int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
			wchar_t* wstr = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);
			LPCTSTR lpMsg = wstr;
			if (_client.sendMsg(lpMsg)) {
				std::cout << "Send message successful!!" << std::endl;
			}
			else {
				std::cout << "Send message failed!!" << std::endl;
			}
		}
		else if (c == '3')
		{
			//client _client;
			if (_client.receiverMsg()) {
				std::cout << "Read message successful!!" << std::endl;
			}
			else {
				std::cout << "Read message failed!!" << std::endl;
			}
		}
		else if (c == '4') {
			//continue;
			display::displayMenu();
		}
		else if (c == '5')
		{
			exit(1);

		}
		else
		{
			std::cout << "\n\t\tErorr:Invalid input characters" << std::endl;
			//continue;
		}
	/*} while (true);*/
}

void controler::_controler()
{


}

