#pragma once
#include <iostream>
#include <sstream>

class Books
{
public:
	Books()=default;
	Books(int id, int bookId, int bestBookId, int workId, int booksCount, std::string isbn, std::string isbn13, std::string authors, std::string originalPublicationYear,
		std::string originalTitle, std::string title, std::string languageCode,double averageRating, int ratingsCount, int workRatingsCount, int workTextReviewsCount,
		int ratings1,int ratings2, int ratings3, int ratings4, int ratings5, std::string imageUrl, std::string smallImageUrl);

	Books(std::string queryResult);
	std::string BookSearch(const std::string& searchInput)const;

	int GetId() const;
	int GetBookId() const;
	int GetWorkId() const;
	int GetBestBookId() const;
	int GetBookCount() const;
	int GetRatingsCount() const;
	int GetWorkRatingsCount() const;
	int GetWorkTextReviewsCount() const;
	int GetRatings1() const;
	int GetRatings2() const;
	int GetRatings3() const;
	int GetRatings4() const;
	int GetRatings5() const;
	double GetAverageRating() const;
	std::string GetISBN() const;
	std::string GetISBN13() const;
	std::string GetLanguageCode() const;
	std::string GetAuthors() const;
	std::string GetImageURL() const;
	std::string GetSmallImageURL() const;
	std::string GetTitle() const;
	std::string GetOriginalTitle() const;
	std::string GetOriginalPublicationYear() const;

	void SetId(const int& id);
	void SetBookId(const int& bookId);
	void SetWorkId(const int& workId);
	void SetBestBookId(const int& bestBookId);
	void SetBookCount(const int& bookCount);
	void SetRatingsCount(const int& ratingsCount);
	void SetWorkRatingsCount(const int& workRatingsCount);
	void SetWorkTextReviewsCount(const int& workTextReviewsCount);
	void SetRatings1(const int& ratings1);
	void SetRatings2(const int& ratings2);
	void SetRatings3(const int& ratings3);
	void SetRatings4(const int& ratings4);
	void SetRatings5(const int& ratings5);
	void SetAverageRating(const double& averageRating);
	void SetISBN(const std::string& ISBN);
	void SetISBN13(const std::string& ISBN13);
	void SetLanguageCode(const std::string& languageCode);
	void SetAuthors(const std::string& authors);
	void SetImageURL(const std::string& imageURL);
	void SetSmallImageURL(const std::string& smallImageUrl);
	void SetTitle(const std::string& title);
	void SetOriginalTitle(const std::string& originalTitle);
	void SetOriginalPublicationYear(const std::string& originalPublicationYear);


private:
	int id=0, bookId = 0, bestBookId = 0, workId = 0, booksCount = 0, ratingsCount = 0, workRatingsCount = 0, workTextReviewsCount = 0, ratings1 = 0, ratings2 = 0, ratings3 = 0, ratings4 = 0, ratings5 = 0;
	std::string isbn="", isbn13 = "", authors = "", originalPublicationYear = "", originalTitle = "", title = "", languageCode = "", imageUrl = "", smallImageUrl = "";
	double averageRating = 0.0;

};
