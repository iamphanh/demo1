#include "pipe.h"
#include "myTime.h"


pipe::pipe(){}
const LPCTSTR pipe::namePipe = TEXT("\\\\.\\pipe\\phanh");
void* pipe::hpipe = nullptr;
LPCTSTR pipe::getnamePipe() {
	return namePipe;
}
BOOL pipe::createHandle() {
		hpipe = CreateNamedPipe(namePipe, 
			PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE 
			| PIPE_READMODE_BYTE | PIPE_WAIT,
			1, 1024, 1024, NMPWAIT_USE_DEFAULT_WAIT, NULL);
		if (hpipe == INVALID_HANDLE_VALUE) {
			/*std::cout << "Erorr: Create Name pipe falied " << GetLastError() << std::endl;*/
			return false;
		}
		else
		{
			/*std::cout << "Create Name pipe successful!!" << std::endl;*/
			//writeHandle(hpipe, TEXT(""));
			return true;
		}
		CloseHandle(hpipe);
};
BOOL  pipe::writeHandle(LPCTSTR msg) {
	    HANDLE hfpipe;
	    hfpipe = CreateFile(pipe::getnamePipe(),
		GENERIC_WRITE,
	    FILE_SHARE_WRITE | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE,
		NULL);
		BOOL resultPipe;
		DWORD write;
		LPWSTR message = myTime::timer(msg);
		resultPipe = WriteFile(hfpipe,
			message,
			DWORD((lstrlenW(message) + 1) * sizeof(TCHAR)),
			&write,
			NULL);
		if (!resultPipe) {
			/*std::cout << "Erorr: Write named pipe failed " << GetLastError() << std::endl;*/
			return false;
		}
		else
		{
	/*		std::cout << "Name pipe written to successfull!!" << std::endl;*/
			return true;
		}
		DisconnectNamedPipe(hfpipe);
		CloseHandle(hfpipe);
};
BOOL  pipe::readHandle() {
		BOOL fResult;
		TCHAR buffer[1024];
		DWORD dwRead;
		fResult = ReadFile(hpipe, buffer,
			sizeof(buffer) - 1, &dwRead, NULL);

		if (fResult != false)
		{
			buffer[dwRead] = '\0';
			std::cout << "Received message: " << buffer << std::endl;
			return true;
		}
		else {
			return false;
		}
		CloseHandle(hpipe);
};
HANDLE WINAPI pipe::getHpipe() const {
		return hpipe;
	}
int WINAPI pipe::creatFpipe() {
		HANDLE hfpipe;
		hfpipe = CreateFile(pipe::getnamePipe(),
			GENERIC_READ |GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_ARCHIVE,
			NULL);
		if (hfpipe == INVALID_HANDLE_VALUE) {
			int erorr = WSAGetLastError();
			/*std::cout << "Erorr: Create file pipe failed " << erorr << std::endl;*/
			return erorr;
		}
		else {
	/*		std::cout << "Creat file pipe successful!!" << std::endl;*/
			return 0;
		}
}
pipe::~pipe(){}