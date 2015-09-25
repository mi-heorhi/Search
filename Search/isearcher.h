#pragma once
class ISearcher
{
public:
	virtual bool find(const char* pattern, const char* source) = 0;
};