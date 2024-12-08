#include "ReaderThread.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <thread>
using namespace System::Windows::Forms;

void ReaderThread(SOCKET sock, std::string* fullMessage) {
    char buffer[512];

    while (true) {  // Перевіряємо прапор завершення
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);

        if (bytesReceived > 0) {
            fullMessage->append(buffer, bytesReceived);
            MessageBox::Show(gcnew System::String(fullMessage->c_str()) + "===Update==="); 
        }
        else if (bytesReceived == 0) {
            break;
        }
        else {
            break;
        }

        Sleep(1000);  // Менша затримка
    }
}

DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    auto params = static_cast<ThreadParams*>(lpParam);

    ReaderThread(params->sock, params->message);

    return 0;
}


