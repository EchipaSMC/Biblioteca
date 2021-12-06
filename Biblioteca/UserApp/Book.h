#pragma once
#include <string>
#include "InvertedIndex.h"

class Book {

private:
	std::string BookID;
	std::string original_title;
	std::string author;
	std::string ISBN;
	std::string imageURL;
	bool borrowed;

public:
	Book();
	Book(std::string id, std::string title, std::string auth, std::string ISBNcode, std::string imgURL, bool borrowed);
	Book(const Book&);
	Book(const std::string&);
	std::string getBookID() const;
	std::string getISBN() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getImgURL() const;
	friend std::ostream& operator<<(std::ostream& fo, const Book& book);
	void printBookInfo(const Book& book);
	void setIfBorrow(bool option);
	bool isBorrowed() const;

};