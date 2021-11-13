#pragma once
#include <string>
#include "InvertedIndex.h"

class Book {

private:
	long long BookID;
	std::string original_title;
	std::string author;
	std::string ISBN;
	bool borrowed;

public:
	Book();
	Book(long long id, std::string title, std::string auth, std::string ISBNcode, bool borrowed);
	Book(const Book&);
	long long getBookID() const;
	std::string getISBN() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	void setIfBorrow(bool option);
	bool isBorrowed() const;

};