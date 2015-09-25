#pragma once

#include "helper.h"
#include "idictionary.h"

class Dictionary : public IDictionary
{
public:
	Dictionary();
	int countMatches(std::string& str);
	void indexFile(std::string& path);
	~Dictionary();
private:
	std::string _dictionaryPath;
	std::vector<std::string> _indexDictionary;
};

