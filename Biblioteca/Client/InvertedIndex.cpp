#include "InvertedIndex.h"

void InvertedIndex::addFile(const std::string& filename)
{
	std::ifstream fp;
	fp.open(filename, std::ios::in);

	if (!fp)
	{
		std::cout << "File not found!\n";
		return;
	}

	std::string line, word;
	int lineNr = 0, wordNr = 0;
	char comma = ',';
	while (std::getline(fp, line)) {
		lineNr++;
		wordNr = 0;
		std::stringstream s(line);
		while (std::getline(s, word, comma))
		{
			wordNr++;
			wordPosition obj;
			obj.line = lineNr;
			obj.index = wordNr;
			Dictionary[word].push_back(obj);
		}
	}
	fp.close();
}

void InvertedIndex::search(std::string word)
{
	if (Dictionary.find(word) == Dictionary.end())
	{
		std::cout << "Title/author not found.";
		return;
	}
	else
	{
		int size = int(Dictionary[word].size());
		for (int index = 0; index < size; index++)
		{
			std::cout << index + 1<<std::endl;
			std::cout << "Line: " << Dictionary[word][index].line << std::endl;
			std::cout << "Index: " << Dictionary[word][index].index << std::endl;
		}
	}
}
