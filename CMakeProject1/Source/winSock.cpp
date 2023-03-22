#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include "winSock.h"
#include <ctime>
#define DEFAULT_BUFLEN  1024
#define DEFAULT_PORT "2912"
SOCKET winSock::listenSocket = INVALID_SOCKET;
SOCKET winSock::clientSock = INVALID_SOCKET;
SOCKET winSock::m_connectSock = INVALID_SOCKET;
winSock::winSock() {};
winSock::~winSock() {};
BOOL WINAPI winSock::createHandle() {
	WSADATA wsaData;
	int iResult;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;


	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		/*printf("WSAStartup failed with error: %d\n", iResult);*/
		return false;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		/*printf("getaddrinfo failed with error: %d\n", iResult);*/
		WSACleanup();
		return false;
	}

	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET) {
		/*printf("socket failed with error: %ld\n", WSAGetLastError());*/
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}

	/*u_long iMode = 1;
	iResult = ioctlsocket(listenSocket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR) {
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}*/


	iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		/*printf("bind failed with error: %d\n", WSAGetLastError());*/
		freeaddrinfo(result);
		closesocket(listenSocket);
		WSACleanup();
		return false;
	}

	freeaddrinfo(result);

	iResult = listen(listenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
	/*	printf("listen failed with error: %d\n", WSAGetLastError());*/
		closesocket(listenSocket);
		WSACleanup();
		return false;
	}
	return true;
}

BOOL WINAPI winSock::writeMessage(SOCKET socket, const char* msg) {
	int sendResult = 0;
	do {
		time_t now = time(nullptr);
		char timeStr[26];
		ctime_s(timeStr, sizeof timeStr, &now);
		char message[32];
		sprintf(message, "Time%s", timeStr);
		sendResult = send(socket, message, strlen(message), 0);
		/*if (sendResult != SOCKET_ERROR) {
			std::cout << "Send message successful!!" << std::endl;
			break;
		}
		else {
			std::cout << "Send message failed with error: " << WSAGetLastError() << std::endl;
		}*/
	} while (sendResult != SOCKET_ERROR);
	closesocket(socket);
	WSACleanup();
	return true;
}

BOOL WINAPI  winSock::readHandle(SOCKET socket) {
		int iresult = 0;
		char buffer[512];
		do {
			iresult = recv(socket, buffer, strlen(buffer), 0);
			if (iresult > 0) {
				/*std::cout << "Received message: \n" << buffer << std::endl;*/
				closesocket(socket);
				WSACleanup();
				return true;
			}
			else {
				/*std::cout << "Received failed with erorr: " << WSAGetLastError() << std::endl;*/
				closesocket(socket);
				WSACleanup();
				return false;
			}
		} while (iresult > 0);
	};
BOOL WINAPI  winSock::acceptConnect() {
		//sockaddr_in clientAddr;
		//int clientAddrLen = sizeof(clientAddr);
		SOCKET clientSock = accept(listenSocket, NULL, NULL);
		/*return true;*/
		if (clientSock == INVALID_SOCKET) {
			/*std::cout << "Accept failed with error: " << WSAGetLastError() << std::endl;*/
			return false;
		}
		/*std::cout << "Accept successful!!" << std::endl;*/
		//writeMessage(clientSock, "");
		return true;
	}

SOCKET  winSock::getlsock() {
		return listenSocket;
	};
SOCKET  winSock::getcsock() {
		return clientSock;
	};
SOCKET  winSock::getcnsock() {
		return m_connectSock;
	};
int WINAPI  winSock::connectSock() {
	WSADATA wsaData;
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	int iResult;


	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		/*printf("WSAStartup failed with error: %d\n", iResult);*/
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		/*printf("getaddrinfo failed with error: %d\n", iResult);*/
		WSACleanup();
		return 1;
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		m_connectSock = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (m_connectSock == INVALID_SOCKET) {
		/*	printf("socket failed with error: %ld\n", WSAGetLastError());*/
			WSACleanup();
			return 1;
		}


		iResult = connect(m_connectSock, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(m_connectSock);
			m_connectSock = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (m_connectSock == INVALID_SOCKET) {
		/*printf("Unable to connect to server!\n");*/
		WSACleanup();
		return 1;
	}

	return 0;
};
