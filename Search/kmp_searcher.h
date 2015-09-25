#pragma once
#include "isearcher.h"
class KMPSearcher :
	public ISearcher
{
public:
	KMPSearcher();
	bool find(const char* pattern, const char* source);
	~KMPSearcher();
private:
	void computeLPSArray(const char * pat, int M, int * lps);
};

