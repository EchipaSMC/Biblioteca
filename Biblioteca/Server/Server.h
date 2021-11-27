#pragma once
#include "Books.h"
#include "BookTags.h"
#include "Database.h"
#include "Ratings.h"
#include "Tags.h"
#include "UserServer.h"
#include <sstream>
#include <string>
class Server
{
public:
	Server();
	void RunServer();
	void PrepareVirtualTable();
	void DropVirtualTable();
private:
	Books book;
	BookTags bookTags;
	Database database;
	Ratings ratings;
	Tags tags;
	UserServer user;
};

