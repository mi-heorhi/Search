#include "stdafx.h"
#include "idictionary_factory.h"

#include "constanttime_dictionary.h"
#include "dictionary.h"


IDictionary * IDictionaryFactory::CreateFactory(DICTIONARY_FACTORIES factory)
{
	if (factory == DICTIONARY_FACTORIES::CONSTANTTIME_DICTIONARY)
	{
		return new ConstantTimeDictionary();
	}
	else if (factory == DICTIONARY_FACTORIES::DICTIONARY_WTIH_KMP_SEARCH)
	{
		return new Dictionary();
	}
	else
	{
		return new ConstantTimeDictionary();
	}
}
