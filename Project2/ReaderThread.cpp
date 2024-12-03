#include "ReaderThread.h"
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace System::Windows::Forms;

void ReaderThread(SOCKET sock, std::string* fullMessage) {
    char buffer[512];

    while (true) {
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            fullMessage->append(buffer, bytesReceived);
            if (fullMessage->find("\n") != std::string::npos) {
                //MessageBox::Show(gcnew System::String(fullMessage->c_str()));
                break; // Завершення після отримання повного повідомлення
            }
        }
        else if (bytesReceived == 0) {
            *fullMessage = "Server disconnected.\r\n";
            break;
        }
        else {
            *fullMessage = "Recv failed with error: " + std::to_string(WSAGetLastError());
            break;
        }
    }
}

DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    auto params = static_cast<ThreadParams*>(lpParam);
    ReaderThread(params->sock, params->message);
    return 0;
}
