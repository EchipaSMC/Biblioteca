#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#pragma comment(lib,"Ws2_32.lib")
class TCPSocket
{
private:
	SOCKET sock;
	const static SOCKET badSocket;
	sockaddr_in addrServer;
public:
	TCPSocket();
	TCPSocket(SOCKET socketHandle);
	~TCPSocket();

	bool Connect();
	bool Listen();
	TCPSocket Accept();
	bool Send(const std::string& data, int size);
	bool Receive(std::string& data);

};

