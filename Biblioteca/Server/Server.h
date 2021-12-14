#pragma once
#include "Books.h"
#include "Database.h"
#include "Ratings.h"
#include "Tags.h"
#include "BorrowedBooks.h"
#include "UserServer.h"
#include "Query.h"
#include <sstream>
#include <string>
#include <vector>
#include "..\TCPSocket\TCPSocket.h"

class Server
{
public:
	Server();
	void RunServer();
	~Server()=default;
private:
	Query queryList;
	Books book;
	Database database;
	Ratings ratings;
	std::vector<Tags> tags;
	UserServer user;
	std::vector<BorrowedBooks> borrowedBooks;
	TCPSocket clientConnections[100];
	std::thread connectionThreads[100];
	int connectionCounter = 0;

	void PrepareVirtualTable();
	void DropVirtualTable();
	bool ListenForNewConnection();

	bool ProcessData(const int& index);
	void ClientHandler(const int& index);

	void Register(const int& index);
	void Login(const int& index);
	void DeleteUser(const int& index);
	void Logout(const int& index);
	void ReturnBook(const int& index);
	void BorrowBook(const int& index);
	void SearchBook(const int& index);
	void ReadBook(const int& index);
	void ChangePassword(const int& index);
	void PrepareBookDetails(const int& index);
	void ProlongBorrowDate(const int& index);

	void RemoveInvalidCharacters(std::string& string);
};

