#pragma once
#include <winsock2.h>
#include <string>
#include <windows.h>
#include <atomic>

struct ThreadParams {
    SOCKET sock;
    std::string* message;
};

void ReaderThread(SOCKET sock, std::string* fullMessage);
DWORD WINAPI ThreadFunc(LPVOID lpParam);


