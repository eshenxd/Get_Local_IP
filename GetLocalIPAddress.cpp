/**************************************
      功能：获取本机IP
	  时间：2014年9月12日
	  作者：Ethan
**************************************/
#include "GetLocalIPAddress.h"



#define _WINSOCK_DEPRECATED_NO_WARNINGS

string IP::getIP()
{
	if(WSAStartup(MAKEWORD(1,1),&wsaData)!=0) 
	{ 
		return NULL; 
	}  

	ipAddress = fetchIPAddress(); 
	WSACleanup();  
	return ipAddress; 
}

string IP::fetchIPAddress()
{
	char host_name[225]; 
	if(gethostname(host_name,sizeof (host_name))==SOCKET_ERROR) 
	{ 
		cout<< "Error "<<WSAGetLastError()<<" when getting local host name."<<endl;  
	} 
	
	struct addrinfo *answer, hint, *curr;
	
	char ipstr[16];
	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

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

	string _ips = (string)ipstr;

	return _ips;

	/*struct hostent *phe = gethostbyname(host_name);

	if(phe==0)
	{
	cout<< "Yow!Bad host lookup.";
	}

	struct in_addr addr;
	memcpy(&addr,phe->h_addr_list[0], sizeof(struct in_addr));
	return inet_ntoa(addr);*/
	
}
