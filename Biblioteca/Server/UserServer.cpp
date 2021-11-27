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
