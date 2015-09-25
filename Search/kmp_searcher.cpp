#include "stdafx.h"
#include "kmp_searcher.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


KMPSearcher::KMPSearcher()
{
}

KMPSearcher::~KMPSearcher()
{
}


bool KMPSearcher::find(const char * pattern, const char * source)
{
	int M = strlen(pattern);
	int N = strlen(source);
	int *lps = new int[M];
	int j = 0;
	computeLPSArray(pattern, M, lps);
	bool result = false;
	int i = 0;
	while (i < N)
	{
		if (pattern[j] == source[i])
		{
			j++;
			i++;
		}

		if (j == M)
		{
			result = true;
			j = lps[j - 1];
		}

		else if (i < N && pattern[j] != source[i])
		{
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
	delete[] lps;
	return result;
}

void KMPSearcher::computeLPSArray(const char * pat, int M, int * lps)
{
	int len = 0;
	int i;

	lps[0] = 0;
	i = 1;

	while (i < M)
	{
		if (pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len != 0)
			{
				len = lps[len - 1];
			}
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

