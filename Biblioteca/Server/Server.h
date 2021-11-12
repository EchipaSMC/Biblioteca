#pragma once
#include "Books.h"
#include "BookTags.h"
#include "Database.h"
#include "Ratings.h"
#include "Tags.h"
class Server
{
public:
	Server();
	void Run();
private:
	Books book;
	BookTags bookTags;
	Database database;
	Ratings ratings;
	Tags tags;
};

