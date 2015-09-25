#pragma once
#include <string>
class IDictionary
{
public:
	virtual int countMatches(std::string& str) = 0;
	virtual void indexFile(std::string& path) = 0;
};