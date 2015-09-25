#pragma once

#include "idictionary.h"

class IDictionaryFactory
{
public:
	enum DICTIONARY_FACTORIES
	{
		CONSTANTTIME_DICTIONARY,
		DICTIONARY_WTIH_KMP_SEARCH
	};
	static IDictionary* CreateFactory(DICTIONARY_FACTORIES factory);
};

