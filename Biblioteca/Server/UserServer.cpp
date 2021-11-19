#include "UserServer.h"

UserServer::UserServer(const std::string queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	result >> word;
	userId = std::stoi(word);

	result >> word;
	username = word;

	result >> word;
	password = word;
}

UserServer::UserServer(const int& userId, const std::string& username, const std::string& password) :
	userId(userId), username(username), password(password) {}

std::string UserServer::UserSearch(const std::string& usernameSearch, const std::string& passwordSearch) const
{
	std::string query = "SELECT * FROM User	WHERE username=";
	query += usernameSearch;
	query += " AND password=";
	query += passwordSearch;
	return query;
}

std::string UserServer::UserInsert(const std::string& username, const std::string& password) const
{
	std::string query = "INSERT INTO User (username,password) VALUES ('";
	query += username + "'," + "'" + password + "')";
	return query;
}

std::string UserServer::UserDelete(const std::string& username, const std::string& password) const
{
	std::string query = "DELETE FROM User WHERE username = '";
	query += username + "' AND password = '" + "'" + password + "'";
	return query;
}

void UserServer::SetUserId(const int& userId)
{
	this->userId = userId;
}

void UserServer::SetUsername(const std::string& username)
{
	this->username = username;
}

void UserServer::SetPassword(const std::string& password)
{
	this->password = password;
}

int UserServer::GetUserId() const
{
	return userId;
}

std::string UserServer::GetUsername() const
{
	return username;
}

std::string UserServer::GetPassword() const
{
	return password;
}
