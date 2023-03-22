#include"mailSlot.h"

void* mailSlot::hSlot = nullptr;
const LPCTSTR mailSlot::slotName = TEXT("\\\\.\\mailslot\\phanh");
mailSlot::mailSlot(){}
mailSlot::~mailSlot() {}

HANDLE  mailSlot::getSlot() const {
        return hSlot;
}
BOOL  mailSlot::createHandle() {
        hSlot = CreateMailslot(slotName,
            0,
            MAILSLOT_WAIT_FOREVER,
            NULL);
        if (hSlot == INVALID_HANDLE_VALUE) {
            /*std::cout << "Error: Create mailSlot failed " << GetLastError() << std::endl;*/
            return false;
        }
        else {
          /*  std::cout << "Create mailSlot successfully!!" << std::endl;*/
            //writeHandle(hSlot, TEXT(""));
            return true;
        }
}
BOOL  mailSlot::writeHandle(LPCTSTR msg) {
    HANDLE clientSlot;
    clientSlot = CreateFile(slotName, GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    /*if (handle == INVALID_HANDLE_VALUE) {
        std::cout << "Error: Invalid mailslot handle" << std::endl;
        return false;
    }*/

    DWORD dwBytesWritten;
    LPWSTR message = myTime::timer(msg);
    BOOL resultSlot = WriteFile(clientSlot,
        message, DWORD((lstrlenW(message) + 1) * sizeof(TCHAR)),
        &dwBytesWritten,
        NULL);

    if (!resultSlot) {
        /*std::cout << "Error: Write Mailslot failed " << GetLastError() << std::endl;*/
        //CloseHandle(handle);
        return false;
    }
    else {
        /*std::cout << "Mailslot written successfully!!" << std::endl;*/
        //CloseHandle(handle);
        return true;
    }
    CloseHandle(clientSlot);
}


int  mailSlot::creatFmail() {
    //std::cout << getDNS();
    HANDLE clientSlot;
    clientSlot = CreateFile(slotName, GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (clientSlot == INVALID_HANDLE_VALUE) {
        int error = GetLastError();
        /*std::cout << "Error: Not connected to server!!\n" << "Error code: " << error << std::endl;*/
        return error;
    }
    else {
       /* std::cout << "Connected successfully!!" << std::endl;*/
        CloseHandle(clientSlot);
        return 0;
    }
}

BOOL  mailSlot::readHandle() {
        DWORD cbMessage, cMessage, cbRead;
        BOOL fResult;
        char lpszBuffer[1024];
        /*TCHAR achID[80];
        DWORD cAllMessages;*/
        HANDLE hEvent;
        OVERLAPPED ov;

        cbMessage = cMessage = cbRead = 0;

        hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("readMailslot"));
        if (hEvent == NULL) {
            /*std::cout << "Error: Failed to create event " << GetLastError() << std::endl;*/
            return FALSE;
        }
        ov.Offset = 0;
        ov.OffsetHigh = 0;
        ov.hEvent = hEvent;
        HANDLE clientSlot;
        clientSlot = CreateFile(slotName, GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        //fResult = GetMailslotInfo(hSlot,
        //    (LPDWORD)NULL,
        //    &cbMessage,
        //    &cMessage,
        //    (LPDWORD)NULL);

        //if (!fResult)
        //{
        //   /* std::cout << "Erorr: GetMailslotInfo failed " << GetLastError() << std::endl;*/
        //    return FALSE;
        //}

        //if (cbMessage == MAILSLOT_NO_MESSAGE)
        //{
        //    std::cout << "Waiting for a message..." << std::endl;
        //    return TRUE;
        //}

        //cAllMessages = cMessage;

        //while (cMessage != 0)
        //{

        //    StringCchPrintf((LPTSTR)achID,
        //        80,
        //        TEXT("\nMessage #%d of %d\n"),
        //        cAllMessages - cMessage + 1,
        //        cAllMessages);

        //    lpszBuffer = (LPTSTR)GlobalAlloc(GPTR,
        //        lstrlen((LPTSTR)achID) * sizeof(TCHAR) + cbMessage);
        //    if (NULL == lpszBuffer)
        //        return FALSE;
        //    lpszBuffer[0] = '\0';

            fResult = ReadFile(clientSlot,
                lpszBuffer,
                sizeof(lpszBuffer),
                &cbRead,
                &ov);

            if (!fResult)
            {
                /*std::cout << "Erorr: Readfile failed " << GetLastError() << std::endl;*/
               /* GlobalFree((HGLOBAL)lpszBuffer);*/
                return FALSE;
            }

        //    StringCbCat(lpszBuffer,
        //        lstrlen((LPTSTR)achID) * sizeof(TCHAR) + cbMessage,
        //        (LPTSTR)achID);

        //    _tprintf(TEXT("Contents of the mailslot: %s\n"), lpszBuffer);

        //    GlobalFree((HGLOBAL)lpszBuffer);

        //    fResult = GetMailslotInfo(hSlot,
        //        (LPDWORD)NULL,
        //        &cbMessage,
        //        &cMessage,
        //        (LPDWORD)NULL);

        //    if (!fResult)
        //    {
        //       /* std::cout << "Erorr: GetMailslotInfo failed " << GetLastError() << std::endl;*/
        //        return FALSE;
        //    }
        //}
        CloseHandle(hEvent);
        return TRUE;
}


