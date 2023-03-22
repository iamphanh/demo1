#include "display.h"

display::display(){}
display::~display(){}
char display::displayC1()
{
	client _client;
	_client.connect();
	std::cout << "\t\t\t>>>>>>> Client mode <<<<<<< " << std::endl;
	std::cout << "\t\tChoose mode: \n";
	std::cout << "\t\t '1' : Disconnect\n";
	std::cout << "\t\t '2' :Send message\n";
	std::cout << "\t\t '3' :Read message\n";
	std::cout << "\t\t '4' : Back\n";
	std::cout << "\t\t '5' : Quit\n";
	std::cout << "Enter key: ";
	char c;
	std::cin >> c;
	return c;
	//if (!_client.connect()) {
	//	std::cout << "Change to Server!" << std::endl;
	//	displayS1();
	//}
	//if (c == '1') {
	//	//client _client;
	//	_client.disconnect();

	//}
	//else if (c == '2')
	//{
	//	//client _client;
	//	std::cin.ignore();
	//	std::string str;
	//	std::cout << "Message: ";
	//	std::getline(std::cin, str);
	//	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	//	wchar_t* wstr = new wchar_t[len];
	//	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);
	//	LPCTSTR lpMsg = wstr;
	//	_client.sendMsg(lpMsg);
	//}
	//else if (c == '3')
	//{
	//	//client _client;
	//	_client.receiverMsg();
	//}
	//else if (c == '4') {
	//	displayMenu();
	//}
	//else if (c == '5')
	//{
	//	exit(1);

	//}
	//else
	//{
	//	std::cout << "\n\t\tErorr:Invalid input characters" << std::endl;
	//	displayC1();
	//}
}
void display::displayS1(server &_server)
{
	std::cout << "\t\t\t>>>>>>> Server mode <<<<<<< " << std::endl;
	std::cout << "\t\tChoose IPC: \n";
	std::cout << "\t\tEnter 'M' or 'm' choose mailSlot.\n";
	std::cout << "\t\tEnter 'P' or 'p' choose named pipe.\n";
	std::cout << "\t\tEnter 'S' or 's' choose Socket.\n";
	std::cout << "\t\tEnter 'Q' or 'q' quit\n";
	std::cout << "\t\tBack: 'b' or 'B'" << std::endl;
	std::cout << "Enter key: ";

	char m;
	std::cin >> m;
	if (m == 'b' || m == 'B') {
		display::displayMenu();
	}
	else if (m == 'q' || m == 'Q') {
		exit(1);
	}
	else if (m == 'S' || m == 's' || m == 'P' || m == 'p' || m == 'm' || m == 'M')
	{
		_server.chooseIPC(m);
		/*server _server;
		_server.start();*/
		//displayS2(q);
	}
	else
	{
		std::cout << "\n\t\tErorr:Invalid input characters" << std::endl;
		displayS1(_server);
	}
}
char display::displayS2()
{
	server _server;
	std::cout << "\t\tChoose mode: \n";
	std::cout << "\t\t '1' : Disconnect server\n";
	std::cout << "\t\t '2' : Send message\n";
	std::cout << "\t\t '3' : Read message\n";
	std::cout << "\t\t '4' : Back\n";
	std::cout << "\t\t '5' : Quit\n";
	std::cout << "Enter key: ";
	char c;
	std::cin >> c;
	return c;
	/*if (c == '1') {
		_server.stop();
		displayS1();
	}
	else if (c == '2') {
		std::cin.ignore();
		std::string str;
		std::cout << "Message: ";
		std::getline(std::cin, str);

		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);
		LPCTSTR lpMsg = wstr;
		_server.sendMsg(lpMsg);
	}
	else if (c == '3') {
		_server.receiverMsg();
	}
	else if (c == '4') {
		displayMenu();
	}
	else if (c == '5') {
		exit(1);
	}
	else
	{
		std::cout << "\n\t\tErorr:Invalid input characters" << std::endl;
		displayS2();
	}*/
}
char display::displayMenu()
{
	std::cout << "\n\n\n\n\t\t\t\t\t\tSERVER AND CLIENT\n\n\n\n";
	std::cout << "\t\tChoose mode: 1. Server\t\t\ 2.Client\t\t 3.Quit\n";
	std::cout << "\t\tEnter key: ";
	char c;
	std::cin >> c;
	return c;
}
