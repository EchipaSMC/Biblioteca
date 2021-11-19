#include "TCPSocket.h"

const SOCKET TCPSocket::badSocket = INVALID_SOCKET;

TCPSocket::TCPSocket() :sock(badSocket)
{
	std::string adress = "127.0.0.1";
	std::wstring wideAddress(adress.begin(), adress.end());
	const wchar_t* wideWchar = wideAddress.c_str();
	addrServer.sin_family = AF_INET;
	InetPton(AF_INET, wideWchar, &addrServer.sin_addr.s_addr);
	addrServer.sin_port = htons(6666);
	memset(&(addrServer.sin_zero), '\0', 8);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		throw std::string("Error at socket(): ") + std::to_string(WSAGetLastError());
	}
}

TCPSocket::TCPSocket(SOCKET socketHandle) :sock(socketHandle)
{
	std::string adress = "127.0.0.1";
	std::wstring wideAddress(adress.begin(), adress.end());
	const wchar_t* wideWchar = wideAddress.c_str();
	addrServer.sin_family = AF_INET;
	InetPton(AF_INET, wideWchar, &addrServer.sin_addr.s_addr);
	addrServer.sin_port = htons(6666);
	memset(&(addrServer.sin_zero), '\0', 8);
}

TCPSocket::~TCPSocket()
{
	if (sock != badSocket)
	{
		closesocket(sock);
	}
}



struct WinsockInitializer
{
	WinsockInitializer()
	{
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != NO_ERROR) {
			throw std::string("WSAStartup Failed with error: ") + std::to_string(iResult);
		}
	}

	~WinsockInitializer()
	{
		WSACleanup();
	}
};

WinsockInitializer globalInitializer;
