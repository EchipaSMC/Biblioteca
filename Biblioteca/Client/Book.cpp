#include "Book.h"

Book::Book()
{
	this->BookID = 0;
	this->original_title = '\0';
	this->author = '\0';
	this->ISBN = '\0';
	this->borrowed = false;
}

Book::Book(long long id, std::string title, std::string auth, std::string ISBNcode, bool borrowed)
{
	this->BookID = id;
	this->original_title = title;
	this->author = auth;
	this->ISBN = ISBNcode;
	this->borrowed = borrowed;
}

Book::Book(const Book& B)
{
	this->author = B.author;
	this->BookID = B.BookID;
	this->ISBN = B.ISBN;
	this->original_title = B.original_title;
	this->borrowed = B.borrowed;
}


long long Book::getBookID() const
{
	return BookID;
}

std::string Book::getISBN() const
{
	return ISBN;
}

std::string Book::getTitle() const
{
	return original_title;
}

std::string Book::getAuthor() const
{
	return author;
}

void Book::setIfBorrow(bool option)
{
	this->borrowed = option;
}

bool Book::isBorrowed()const
{
	return borrowed;

}


