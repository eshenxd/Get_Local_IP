#include "getLocalIP.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

_IP_::_IP_(){

	ipstr = new char[16];

	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
}

_IP_::~_IP_(){

	delete[] ipstr;
}

string _IP_::getIP(){

	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		return NULL;
	}

	char host_name[225];

	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR)
	{
		cout << "Error " << WSAGetLastError() << " when getting local host name." << endl;
	}
	
	int ret = getaddrinfo(host_name, NULL, &hint, &answer);

	if (ret != 0) {
		fprintf(stderr, "getaddrinfo: %s\n",
			gai_strerror(ret));
	}

	for (curr = answer; curr != NULL; curr = curr->ai_next) {
		inet_ntop(AF_INET,
			&(((struct sockaddr_in *)(curr->ai_addr))->sin_addr),
			ipstr, 16);
	}

	ipAddress = (string)ipstr;

	WSACleanup();

	return ipAddress;
}