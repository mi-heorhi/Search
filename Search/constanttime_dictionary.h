#pragma once
#include "idictionary.h"

#include <unordered_set>
class ConstantTimeDictionary :
	public IDictionary
{
public:
	ConstantTimeDictionary();
	int countMatches(std::string& str);
	void indexFile(std::string& path);
	~ConstantTimeDictionary();
private:
	std::unordered_set<std::string> _indexedDictionary;
};

