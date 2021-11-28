#pragma once
#include "Books.h"
#include "BookTags.h"
#include "Database.h"
#include "Ratings.h"
#include "Tags.h"
#include "BorrowedBooks.h"
#include "UserServer.h"
#include "Query.h"
#include <sstream>
#include <string>
#include <vector>
#include "..\TCPSocket\TCPSocket.cpp"

class Server
{
public:
	Server();
	void RunServer();
	void PrepareVirtualTable();
	void DropVirtualTable();
private:
	Query queryList;
	Books book;
	BookTags bookTags;
	Database database;
	Ratings ratings;
	Tags tags;
	UserServer user;
	std::vector<BorrowedBooks> borrowedBooks;
	TCPSocket client;

};

