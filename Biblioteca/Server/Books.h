#pragma once
#include <iostream>
#include <sstream>

class Books
{
public:
	Books()=default;
	Books(const int& id, const int& bookId, const int& bestBookId, const int& workId, const int& booksCount, const std::string& isbn, const std::string& isbn13, const std::string& authors,
		const std::string& originalPublicationYear, const std::string& originalTitle, const std::string& title, const std::string& languageCode, const double& averageRating,
		const int& ratingsCount, const int& workRatingsCount, const int& workTextReviewsCount,const int& ratings1, const int& ratings2, const int &ratings3, const int& ratings4,
		const int& ratings5, const std::string& imageUrl, const std::string& smallImageUrl);
	Books(const std::string& queryResult);
	Books(const Books& book);
	~Books() = default;

	Books& operator=(const Books& book);

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
