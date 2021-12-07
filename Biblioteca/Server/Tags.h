#pragma once
#include <string>
#include <iostream>
#include <sstream>
class Tags
{
public:
	Tags();
	Tags(const Tags& tags);
	Tags(std::string queryResult);
	Tags(const int& tagId, const std::string& tagName);

	int GetTagId()const;
	std::string GetTagName()const;

	void SetTagId(const int &tagId);
	void SetTagName(const std::string &tagName);
	Tags& operator=(const Tags& tags);

	~Tags()=default;
private:
	int tagId;
	std::string tagName;
};