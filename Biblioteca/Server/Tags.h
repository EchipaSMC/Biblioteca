#pragma once
#include <string>
#include <iostream>
#include <sstream>
class Tags
{
public:
	Tags();
	Tags(const int& tagId, const std::string& tagName);
	Tags(std::string queryResult);

	std::string QuerySearch(const std::string& searchInput)const;
	int GetTagId();
	std::string GetTagName();

	void SetTagId(int tagId);
	void SetTagName(std::string tagName);

private:
	int tagId;
	std::string tagName;
};