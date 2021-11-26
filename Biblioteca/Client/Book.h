#pragma once
#include <string>
#include "InvertedIndex.h"

class Book {

private:
	std::string BookID;
	std::string original_title;
	std::string author;
	std::string ISBN;
	bool borrowed;

public:
	Book();
	Book(std::string id, std::string title, std::string auth, std::string ISBNcode, bool borrowed);
	Book(const Book&);
	Book(const std::string&);
	std::string getBookID() const;
	std::string getISBN() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	friend std::ostream& operator<<(std::ostream& fo, const Book& book);
	void printBookInfo(const Book& book);
	void setIfBorrow(bool option);
	bool isBorrowed() const;

};