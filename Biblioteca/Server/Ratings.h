#pragma once
#include <iostream>
#include <string>
#include <sstream>

class Ratings
{
public:

	Ratings()=default;
	Ratings(const Ratings& ratings);
	Ratings(std::string queryResult);
	Ratings(const int& bookId, const int& userId, const int& rating);
	
	int GetBookId() const;
	int GetUserId() const;
	int GetRating() const;

	void SetBookId(const int &bookId);
	void SetUserId(const int &userId);
	void SetRating(const int &rating);

	Ratings& operator=(const Ratings& ratings);

	~Ratings()=default;
private:
	int bookId;
	int userId;
	int rating;
};

