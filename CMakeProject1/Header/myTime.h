#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h>


class myTime {
private:
    static SYSTEMTIME st;
public:
    myTime() {};
    ~myTime() {}; 
    static LPWSTR WINAPI timer(LPCTSTR message) {
        GetLocalTime(&st);
        TCHAR buffer[256];
        wsprintf(buffer, _T("%d/%d/%d %d:%d:%d"), st.wDay, st.wMonth,
            st.wYear, st.wHour, st.wMinute, st.wSecond);

        LPWSTR lpMessage = new WCHAR[512];
        wsprintfW(lpMessage, L"Time: %s\n%s", buffer, message);

        return lpMessage;
    }


};

#endif // TIME_CLASS_H
