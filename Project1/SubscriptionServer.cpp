#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>  
#include <ws2tcpip.h>   
#include <windows.h>    
#include <winhttp.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <set>
#include <map>
#pragma comment(lib, "ws2_32.lib")  // ˳�������� � ��������� Winsock
#pragma comment(lib, "winhttp.lib") // ˳�������� � ��������� ��� HTTP




std::mutex clientMutex; //�'����� ��������� ���������� ������ �� ������� ������� �� ��������.

// ��������� ��� ���������� ��� �볺���
struct ClientInfo {
    SOCKET socket;       // ����� �볺���
    std::string type;    // ��� �볺��� (����., "HTTP", "FTP")
    bool operator<(const ClientInfo& other) const {
        return socket < other.socket; // ��������� �� ��������
    }
    bool operator==(const ClientInfo& other) const {
        return socket == other.socket && type == other.type; // ��������� �� ������� � �����
    }
};

SOCKET accept(SOCKET s, struct sockaddr* addr, int* addrlen);



std::set<ClientInfo> clients;
std::map<SOCKET, std::set<std::string>> clientss;

// ------------------- HTTP-������ -------------------
std::string HttpGetRequest(const std::wstring& server, const std::wstring& url) { //��'� ������� , ���� �� ������� �� ������
    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL; // ����������� ��� ���, ���������� �� ������ 
    std::string response; // ����� ��� ���������� ������ �������

    // ����������� WinHTTP: ����������� ���� ��� ��������� HTTP-������
    hSession = WinHttpOpen(
        L"MyApp/1.0", // ��'� ������ (User-Agent) �볺���
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, // ������������ ���������� ����� (���� �)
        WINHTTP_NO_PROXY_NAME, // �� ��������������� ����������� �����-������
        WINHTTP_NO_PROXY_BYPASS, // �� �������� ����� ��� ������ �����
        0 // ��������� (�� �������������)
    );

    if (hSession) { // ����������, �� ������� �������� ����
        hConnect = WinHttpConnect(
            hSession, // ������������� ������� ���
            server.c_str(), // ��'� �������
            INTERNET_DEFAULT_HTTPS_PORT, // ���� HTTPS (443)
            0 // ��������� ��������
        );
        if (hConnect) { // ����������, �� ������� ����������� �� �������
            hRequest = WinHttpOpenRequest(
                hConnect, // ������������� ����������
                L"GET", // ��� ������: GET
                url.c_str(), // ���� �� ������� �� ������
                NULL, // ����� ��������� (�� �������������)
                WINHTTP_NO_REFERER, // ³������ ��������� Referer
                WINHTTP_DEFAULT_ACCEPT_TYPES, // ��������� ���� ��������, �� �����������
                WINHTTP_FLAG_SECURE // ��������������� �������� �'������� (HTTPS)
            );
            if (hRequest) { // ����������, �� ������� �������� �����
                BOOL sent = WinHttpSendRequest(
                    hRequest, // ������������� ������
                    WINHTTP_NO_ADDITIONAL_HEADERS, // �������� ��������� �� �����������
                    0, // ������� ��������� (0, ���� �� ����)
                    WINHTTP_NO_REQUEST_DATA, // �������� ��� � ����� (������)
                    0, // ������� ����� ������
                    0, // �������� ������� ������ (0, ���� �������)
                    0 // ��������� ��������
                );
                // ����������, �� ������� ��������� ����� � �������� �������
                if (sent && WinHttpReceiveResponse(hRequest, NULL)) {
                    DWORD bytesRead = 0; // ʳ������ �����, ���������� �� ������
                    do {
                        char buffer[4096]; // ����� ��� ������� ����� (4 ��)
                        WinHttpReadData(
                            hRequest, // ������������� ������
                            buffer, // ����� ��� ��������� �����
                            sizeof(buffer), // ����� ������
                            &bytesRead // �������� ������� ���������� �����
                        );
                        // ������ �������� ��� �� ������, ���� ���� ���������
                        if (bytesRead > 0) {
                            response.append(buffer, bytesRead);
                        }
                    } while (bytesRead > 0); // ����������, ���� � ��� ��� �������
                }
            }
        }
    }

    // �������� �������� ����������� ��� ���������� ������� ���'��
    if (hRequest) WinHttpCloseHandle(hRequest); // ��������� ���������� ������
    if (hConnect) WinHttpCloseHandle(hConnect); // ��������� ���������� ����������
    if (hSession) WinHttpCloseHandle(hSession); // ��������� ���������� ���
    return response;
}

// ------------------- ������� JSON -------------------
// ������� ��� ������ �������� ����� � JSON-�����
// json - JSON-�����, � ����� ���������� �����
// key - ����, �������� ����� ������� ������
std::string FindJsonValue(const std::string& json, const std::string& key) {
    // ��������� ����� ��������� ����� � JSON-�����
    // ������ ����� ������� �����, ��� �������� ���� � ������ �������� �������
    size_t start = json.find("\"" + key + "\":");
    // ���� ���� �� ��������, ��������� ������� �����
    if (start == std::string::npos) return "";
    // ��������� ��������� (":") ���� �����
    start = json.find(":", start) + 1;
    // ������ ����� ��������, �����������, �� ���� ���������� ����� (",")
    size_t end = json.find(",", start);
    // ���� �������� ��������� � �����, ������� ��� ��� �� �����������
    if (json[start] == '"') {
        start++; // ���������� ��������� �����
        end = json.find("\"", start); // ��������� ������ �����
    }

    // �������� �������, ���� ������� �������� �����
    return json.substr(start, end - start);
}




// ������� ��� ��������� ���������� ��� ������ ����� API OpenWeatherMap
std::vector<std::string> GetWeatherInfo() {
    std::vector<std::string> weatherInfo; // ����� ��� ��������� ������� ����������
    // ������ ������� �� ���� �� ������� � ����������� ������
    std::wstring server = L"api.openweathermap.org"; // ����� API OpenWeatherMap
    std::wstring url = L"/data/2.5/weather?q=Lviv&appid=e4a2c38dfe1b15e27796cb1e4b559c35";  // ̳��� - ����, ���� API

    // �������� HTTP-����� �� �������
    std::string response = HttpGetRequest(server, url);

    // ��������, �� �������� �������
    if (!response.empty()) {
        try {
            // ������� ��� � JSON-������
            std::string temp = FindJsonValue(response, "temp");         // �����������
            std::string pressure = FindJsonValue(response, "pressure"); // ����
            std::string humidity = FindJsonValue(response, "humidity"); // ��������
            std::string weatherType = FindJsonValue(response, "main");  // ��� ������ (����, ������ ����)


            // ���������� ����������� � ������� � �����
            double tempCelsius = std::stod(temp) - 273.15;

            // ��������� ����������� � ����� ������� ���� ����
            std::ostringstream tempStream;
            tempStream << std::fixed << std::setprecision(2) << tempCelsius << "�C";

            // ������ ��� �� ������ ������� ����������
            weatherInfo.push_back(tempStream.str());     // ����������� � �������
            weatherInfo.push_back(pressure + " hPa");    // ���� � ���
            weatherInfo.push_back(humidity + "%");       // �������� � ��������
            weatherInfo.push_back(weatherType);          // ��� ������
        }
        // � ��� ������� (���������, ������������ ������ ������)
        catch (...) {
            weatherInfo = { "-", "-", "-", "Error fetching data" };
        }
    }
    else {
        // ���� ������� ������� �������
        weatherInfo = { "-", "-", "-", "No response from server" };
    }
    // ��������� ����� � ����������� ��� ������
    return weatherInfo;
}

// ������� ��� ��������� ����� ����� ����� API ������������� ����� ������
std::vector<std::string> GetCurrencyInfo() {
    std::vector<std::string> currencyInfo;// ������ ��� ��������� ����� �����

    // ������ ������� �� ���� �� API
    std::wstring server = L"bank.gov.ua"; // ����� ������� ������������� ����� ������
    std::wstring url = L"/NBUStatService/v1/statdirectory/exchange?json";

    // �������� HTTP-����� �� �������
    std::string response = HttpGetRequest(server, url);

    // ����������, �� �������� ������� �� �������
    if (!response.empty()) {
        // ���� ��� ��������� ����� �����
        std::string usdRate, eurRate;

        // ����� �������, �� ������� ���� ������ ��� (USD) � ������
        size_t usdPos = response.find("\"cc\":\"USD\""); // ��������� JSON-������� ��� ������ USD
        if (usdPos != std::string::npos) {
            // ���� �������� ������� USD, �������� ���� ���� �� ��������� ������� FindJsonValue
            usdRate = FindJsonValue(response.substr(usdPos - 50, 100), "rate");
        }
        // ����� �������, �� ������� ���� ���� (EUR) � ������
        size_t eurPos = response.find("\"cc\":\"EUR\""); // ��������� JSON-������� ��� ������ EUR
        if (eurPos != std::string::npos) {
            // ���� �������� ������� EUR, �������� ���� ���� �� ��������� ������� FindJsonValue
            eurRate = FindJsonValue(response.substr(eurPos - 50, 100), "rate");
        }

        // ������ ����� ����� � ������
        currencyInfo.push_back(usdRate + " UAH");
        currencyInfo.push_back(eurRate + " UAH");
    }
    else {
        // ���� ������� �� ������� �������, ������ ������� ��������
        currencyInfo = { "-", "-" };
    }

    return currencyInfo;
}

// ������� ��� ��������� ���������� ��� ����� �����
std::vector<std::string> GetStockInfo() {
    std::vector<std::string> stockInfo; // ������ ��� ��������� ���������� ��� �����
    // ����� ������� (������ API Finnhub)
    std::wstring server = L"finnhub.io";
    // ���� �� �������, �� ������ ������ TSLA (Tesla) �� ����� �����������
    std::wstring url = L"/api/v1/quote?symbol=TSLA&token=ct2tn8pr01qkff70vo3gct2tn8pr01qkff70vo40";
    // ��������� HTTP-������ �� ��������� �������
    std::string response = HttpGetRequest(server, url);

    // ��������, �� ���� �������� �������
    if (!response.empty()) {
        try {
            // ������� JSON-������ ��� ��������� ������� ���� �����
            std::string currentPrice = FindJsonValue(response, "c");
            // ������� ��� ��������� ������� ���� �� ����
            std::string highPrice = FindJsonValue(response, "h");
            // ������� ��� ��������� �������� ���� �� ����
            std::string lowPrice = FindJsonValue(response, "l");

            // ��������� ��������� ����� �� �������
            stockInfo.push_back("$" + currentPrice);  // ������� ����
            stockInfo.push_back("$" + highPrice);    // ������� ����
            stockInfo.push_back("$" + lowPrice);     // �������� ����
        }
        catch (...) {
            // � ��� ���������� ������� ��������� ������� ��������
            stockInfo = { "-", "-", "-" };
        }
    }
    else {
        // ���� ������� ������� ���� ���������, ������������ ������� ��������
        stockInfo = { "-", "-", "-" };
    }

    return stockInfo;
}



// ��������� ����� 
void BroadcastToClients(const std::string& message, const std::string& subscriptionType) {
    // ������ ������ �볺��� �� ��������� �'������
    std::lock_guard<std::mutex> lock(clientMutex);
    // ��������� �� ������ �볺���
    for (auto it = clients.begin(); it != clients.end(); ) {
        // ����������, �� ��������� �볺�� �� �������� ���
        if (it->type == subscriptionType) {
            // ��������� ����������� ����� �����
            int result = send(it->socket, message.c_str(), static_cast<int>(message.size()), 0);

            // ���� ������� ������� ��� �볺�� ����������
            if (result == SOCKET_ERROR) {
                closesocket(it->socket); // ��������� �����
                it = clients.erase(it); // ��������� �볺��� � ������
                continue;                // ���������� �� ���������� �볺���
            }
        }
        ++it;// ������� �� ���������� �볺���
    }
}


//������ ��������� ������
void WeatherUpdateService() {
    // ���������� ���� ��� ��������� ��������� ���������� ��� ������
    while (true) {
        // �������� ��������� ���������� ��� ������
        auto weatherInfo = GetWeatherInfo();
        std::ostringstream oss;
        oss << "Weather in Lviv:\n"
            << weatherInfo[0] << "�\n"
            << weatherInfo[1] << "\n"
            << weatherInfo[2] << "\n"
            << weatherInfo[3] << "\n";
        // ��������� ����������� ��� �볺����, ��������� �� ��� "weather"
        BroadcastToClients(oss.str(), "weather");
        // �������� �� 1 ������ (3600 ������) ����� ��������� ����������
        std::this_thread::sleep_for(std::chrono::seconds(3600)); // �������� ��� ����������
    }
}


// ������ ��������� �������� �����
void CurrencyUpdateService() {
    // ���������� ���� ��� ��������� ��������� �������� �����
    while (true) {
        // �������� �������� ����� �����
        auto currencyInfo = GetCurrencyInfo();
        std::ostringstream oss;
        oss << "Currency Rates:\n"
            << currencyInfo[0] << "\n"
            << currencyInfo[1] << "\n";
        // ��������� ����������� ��� �볺����, ��������� �� ��� "currency"
        BroadcastToClients(oss.str(), "currency");
        // �������� �� 24 ������ ����� ��������� ����������
        std::this_thread::sleep_for(std::chrono::hours(24)); // �������� ��� ����������
    }
}


// ������ ��������� ���������� ��� �����
void StockUpdateService() {
    // ���������� ���� ��� ��������� ��������� ���������� ��� �����
    while (true) {
        // �������� ��������� ���������� ��� ����� Tesla Inc.
        auto stockInfo = GetStockInfo();

        std::ostringstream oss;
        oss << "Tesla Inc.(TSLA):\n"
            << stockInfo[0] << "\n"
            << stockInfo[1] << "\n"
            << stockInfo[2] << "\n";
        // ��������� ����������� ��� �볺����, ��������� �� ��� "stock"
        BroadcastToClients(oss.str(), "stock");
        // �������� �� 1 ������� (60 ������) ����� ��������� ����������
        std::this_thread::sleep_for(std::chrono::seconds(60)); // �������� ��� ����������
    }
}

// ------------------- �������� ������ -------------------
void HandleClient(SOCKET clientSocket) {
    char buffer[256];
    int bytesRead;

    // ������� ����� �� �볺���
    bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::string command(buffer);

        {
            std::lock_guard<std::mutex> lock(clientMutex);

            // ��������� ������ � ��������� �������
            std::stringstream ss(command);
            std::string singleCommand;
            while (std::getline(ss, singleCommand, ',')) {
                if (singleCommand == "weather" || singleCommand == "currency" || singleCommand == "stock") {
                    clientss[clientSocket].insert(singleCommand);
                    std::cout << "Client subscribed to: " << singleCommand << std::endl;
                }
                else {
                    std::cout << "Invalid subscription type: " << singleCommand << std::endl;
                }
            }
        }

        // ���������� ������ ����������� ��� �볺���
        std::ostringstream response;
        {
            std::lock_guard<std::mutex> lock(clientMutex);

            if (clientss[clientSocket].count("weather")) {
                auto weatherInfo = GetWeatherInfo();
                response << "Weather in Lviv:\n"
                    << weatherInfo[0] << "\n"
                    << weatherInfo[1] << "\n"
                    << weatherInfo[2] << "\n"
                    << weatherInfo[3] << "\n";
            }
            if (clientss[clientSocket].count("currency")) {
                auto currencyInfo = GetCurrencyInfo();
                response << "Currency Rates:\n"
                    << currencyInfo[0] << "\n"
                    << currencyInfo[1] << "\n";
            }
            if (clientss[clientSocket].count("stock")) {
                auto stockInfo = GetStockInfo();
                response << "TSLA Inc. (TSLA):\n"
                    << stockInfo[0] << "\n"
                    << stockInfo[1] << "\n"
                    << stockInfo[2] << "\n";
            }
        }

        // ³������� ����������� �볺���
        std::string responseStr = response.str();
        if (!responseStr.empty()) {
            send(clientSocket, responseStr.c_str(), responseStr.size(), 0);
        }
    }
    else {
        // �������� �'�������
        {
            std::lock_guard<std::mutex> lock(clientMutex);
            clientss.erase(clientSocket);
        }
        closesocket(clientSocket);
        std::cout << "Client disconnected (read error)." << std::endl;
    }
}


int main() {
    // ����������� Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    const std::string ipAddress = "127.0.0.1";
    const int port = 12345;

    // ��������� ������
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Binding failed." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // �������� ������� �� �����
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server started on " << ipAddress << ":" << port << std::endl;

    std::thread weatherThread(WeatherUpdateService);
    std::thread currencyThread(CurrencyUpdateService);
    std::thread stockThread(StockUpdateService);
    weatherThread.detach();
    currencyThread.detach();
    stockThread.detach();

    while (true) {
        // ������ ������� �'������
        struct sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed." << std::endl;
            continue;
        }

        std::cout << "Client connected." << std::endl;

        // ���������� �볺��� � �������� ������
        std::thread clientThread(HandleClient, clientSocket);
        clientThread.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}