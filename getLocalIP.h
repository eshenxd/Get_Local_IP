#ifndef _GET_LOCAL_IP_
#define _GET_LOCAL_IP_

#include <iostream>
#include <ws2tcpip.h>


class _IP_
{
public:
	_IP_();
	~_IP_();

	std::string getIP();
protected:
private:
	std::string ipAddress;
	struct addrinfo *answer;
	struct addrinfo hint; 
	struct addrinfo *curr;

	WSAData wsaData;

	char* ipstr;

};

#endif