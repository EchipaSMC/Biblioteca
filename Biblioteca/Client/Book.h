#pragma once
#include <string>

class Book {

private:
	long long BookID;
	std::string original_title;
	std::string author;
	std::string ISBN;

public:
	Book();
	Book(long long id, std::string title, std::string auth, std::string ISBNcode);
	Book(const Book&);
	long long getBookID() const;
	std::string getISBN() const;
	std::string getTitle() const;
	std::string getAuthor() const;
};