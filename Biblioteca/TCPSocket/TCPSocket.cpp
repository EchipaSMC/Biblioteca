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

bool TCPSocket::Connect()
{
	std::cout << "Connecting..." << std::endl;
	int iResult = connect(sock, (SOCKADDR*)&addrServer, sizeof(addrServer));
	if (iResult == SOCKET_ERROR) {
		closesocket(sock);
		std::cerr << "Unable to connect to server: " << WSAGetLastError() << std::endl;
		return false;
	}

	return true;
}

bool TCPSocket::Listen()
{
	if (bind(sock, (SOCKADDR*)&addrServer, sizeof(addrServer)) == SOCKET_ERROR) {
		std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}

	if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

TCPSocket TCPSocket::Accept()
{
	SOCKET clientSocket = accept(sock, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
		throw std::string("Accept failed with error: ") + std::to_string(WSAGetLastError());
	}
	return TCPSocket(clientSocket);
}

bool TCPSocket::Send(const std::string& data, int size)
{
	int iSendResult = send(sock, (char*)&size, sizeof(int), 0);
	if (iSendResult == SOCKET_ERROR) {
		std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}

	iSendResult = send(sock, data.c_str(), data.size(), 0);
	if (iSendResult == SOCKET_ERROR) {
		std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

bool TCPSocket::Receive(std::string& data)
{
	int size;
	int iReceiveResult = recv(sock, (char*)&size, sizeof(int), 0);
	if (iReceiveResult == 0)
		std::cout << "Connection closed\n" << std::endl;
	else if (iReceiveResult < 0)
	{
		std::cerr << "recv failed with error: " << WSAGetLastError();
		return false;
	}
	char* recvbuf = new char[size];

	iReceiveResult = recv(sock, recvbuf, size, 0);
	if (iReceiveResult > 0) {
		for (int i = 0; i < iReceiveResult; i++) data += recvbuf[i];
	}
	if (iReceiveResult < 0)
	{
		std::cerr << "receive failed: " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
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
