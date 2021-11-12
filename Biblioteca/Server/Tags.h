#pragma once
#include <string>
class Tags
{
public:
	Tags();
	Tags(const int& tagId, const std::string& tagName);

	int GetTagId();
	std::string GetTagName();

	void SetTagId(int tagId);
	void SetTagName(std::string tagName);

private:
	int tagId;
	std::string tagName;
};