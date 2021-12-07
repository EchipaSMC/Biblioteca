#pragma once
#include <string>
#include <sstream>

class Book {

private:
	std::string bookId;
	std::string originalTitle;
	std::string author;
	std::string isbn;
	std::string imageUrl;

public:
	Book() = default;
	Book(const std::string& id, const std::string& title, const std::string& auth, const std::string& ISBNcode, const std::string& imgURL);
	Book(const Book& book);
	Book(const std::string& serverReceived);

	const Book& operator=(const Book& book);

	std::string getBookId() const;
	std::string getIsbn() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getImgUrl() const;

	void setBookId(const std::string& bookId);
	void setIsbn(const std::string& isbn);
	void setTitle(const std::string& originalTitle);
	void setAuthor(const std::string& author);
	void setImgUrl(const std::string& bookId);
	friend std::ostream& operator<<(std::ostream& fo, const Book& book);

};