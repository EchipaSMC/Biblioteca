#pragma once
#include <iostream>
#include <string>
#include <sstream>

class Ratings
{
public:

	Ratings();
	Ratings(std::string queryResult);
	Ratings(const int& bookId, const int& userId, const int& rating);
	
	int GetBookId() const;
	int GetUserId() const;
	int GetRating() const;

	void SetBookId(int bookId);
	void SetUserId(int userId);
	void SetRating(int rating);

private:
	int bookId;
	int userId;
	int rating;
};

