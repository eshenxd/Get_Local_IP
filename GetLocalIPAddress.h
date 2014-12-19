#pragma once
#include <iostream>
#include"winsock2.h"
#include <string>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib") 

using namespace std;

class IP
{
public:
	string getIP();
protected:

private:
	WSAData wsaData;
	string ipAddress;
	string fetchIPAddress();
};
