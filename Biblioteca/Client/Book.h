#pragma once
#include <string>

class Book {
private:
	long long BookID;
	std::string original_title;
	std::string author;
	long long ISBN;
public:
	Book();
	Book(const Book&);
	long long getBookID() const;
	long long getISBN() const;
	std::string getTitle() const;
	std::string getAuthor() const;
};