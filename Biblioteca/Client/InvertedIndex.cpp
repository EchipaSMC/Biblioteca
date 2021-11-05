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