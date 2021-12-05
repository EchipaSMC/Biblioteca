#include "Query.h"

std::string Query::BooksBookSearch(const std::string& searchInput) const
{
	std::string query = "Select * from Books where id in (SELECT rank from demo where editdist3(word,'";
	query += searchInput;
	query += "')/100 < 5);";
	return query;
}
std::string Query::BooksNumOfBookSearch(const std::string& searchInput) const
{
	std::string query = "Select count(*) from Books where id in (SELECT rank from demo where editdist3(word,'";
	query += searchInput;
	query += "')/100 < 5);";
	return query;
}
std::string Query::BookTagsGetTags(const int& bestBookId) const
{
	std::string query = "SELECT goodreads_book_id,tag_id,count FROM BookTags INNER JOIN Books o ON goodreads_book_id = o.best_book_id WHERE goodreads_book_id = ";
	query += std::to_string(bestBookId);
	return query;
}
std::string Query::BookTagsNumGetTags(const int& bestBookId) const
{
	std::string query = "SELECT count(*) FROM BookTags INNER JOIN Books o ON goodreads_book_id = o.best_book_id WHERE goodreads_book_id = ";
	query += std::to_string(bestBookId);
	return query;
}
std::string Query::BorrowedBooksSearch(const int& userIdSearch) const
{
	std::string query = "SELECT * FROM BorrowedBooks WHERE user_id=";
	query += userIdSearch;
	return query;
}
std::string Query::BorrowedBooksInsert(const int& userId, const int& bookId) const
{
	std::string query = "INSERT INTO BorrowedBooks (user_id,book_id)VALUES ('";
	query += std::to_string(userId) + "'," + "'" + std::to_string(bookId) + "')";
	return query;
}
std::string Query::BorrowedBooksDelete(const int& userId, const int& bookId) const
{
	std::string query = "DELETE FROM BorrowedBooks WHERE user_id = '";
	query += std::to_string(userId) + "' AND book_id = '" + std::to_string(bookId) + "'";
	return query;
}
std::string Query::BookGetBookByID(const int& bookId) const
{
	std::string query = "SELECT * FROM Books WHERE id = ";
	query += std::to_string(bookId);
	return query;
}
std::string Query::RatingsGetRatings(const int& bestBookId) const
{
	std::string query = "SELECT book_id,user_id,rating FROM Ratings INNER JOIN Books o ON ON Ratings.book_id =o.id  WHERE Ratings.book_id = ";
	query += std::to_string(bestBookId);
	return query;
}
std::string Query::TagsQuerySearch(const std::string& searchInput) const
{
	std::string query = "SELECT * FROM Tags INNER JOIN BookTags ON Tags.tag_id = BookTags.tag_id WHERE Tags.tag_id = ";
	query += searchInput;
	return query;
}
std::string Query::UserServerUserSearch(const std::string& usernameSearch, const std::string& passwordSearch) const
{
	std::string query = "SELECT * FROM User	WHERE username=";
	query += usernameSearch;
	query += " AND password=";
	query += passwordSearch;
	return query;
}
std::string Query::UserServerUserInsert(const std::string& username, const std::string& password) const
{

	std::string query = "INSERT INTO User (username,password) VALUES ('";
	query += username + "'," + "'" + password + "')";
	return query;
}
std::string Query::UserServerUserDelete(const std::string& username, const std::string& password) const
{
	std::string query = "DELETE FROM User WHERE username = '";
	query += username + "' AND password = '" + "'" + password + "'";
	return query;
}
std::string Query::UserServerCheckExistingUsers(const std::string& username) const
{
	std::string query = "SELECT COUNT(*) FROM User WHERE username='";
	query += username + "'";
	return query;
}
std::string Query::UserServerUsersLogin(const std::string& username, const std::string& password) const
{
	std::string query = "SELECT COUNT(*) FROM User WHERE username='";
	query += username + "' AND password ='" + password + "'";
	return query;
}
std::string Query::UserServerUsersLoginID(const std::string& username, const std::string& password) const
{
	std::string query = "SELECT user_id FROM User WHERE username='";
	query += username + "' AND password ='" + password + "'";
	return query;
}
std::string Query::UserChangePassword(const int& userId, const std::string& newPassword)
{
	std::string query = "UPDATE User SET password = '";
	query += newPassword+"' WHERE user_id = "+std::to_string(userId);
	return query;
}

