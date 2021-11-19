#pragma once
#include <iostream>
#include <string>
#include <sstream>

class UserServer
{
public:
	UserServer()=default;
	UserServer(const std::string queryResult);
	UserServer(const int& userId, const std::string& username, const std::string& password);
	std::string UserSearch(const std::string& usernameSearch, const std::string& passwordSearch)const;

	void SetUserId(const int& userId);
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);

	int GetUserId() const;
	std::string GetUsername() const;
	std::string GetPassword() const;

private:
	int userId;
	std::string username, password;
};

