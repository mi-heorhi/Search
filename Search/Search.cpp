// Search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "helper.h"
#include "idictionary_factory.h"
#include "idictionary.h"
#include "dictionary.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

int main(int argc, char *argv[])
{

	IDictionary* dict;
	auto dictionaryInstance = IDictionaryFactory::CONSTANTTIME_DICTIONARY;
	try
	{
		if (argc == 2)
		{
			std::string dictionaryPath = argv[1];
			std::string serchPath = "";
			dict = IDictionaryFactory::CreateFactory(dictionaryInstance);
			auto start = std::chrono::system_clock::now();
			dict->indexFile(dictionaryPath);
			auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
			std::cout << "Pre - processing time is " << seconds.count() / 1000LL << " seconds." << std::endl;
			delete dict;
		}
		else if (argc == 3)
		{
			auto start = std::chrono::system_clock::now();
			std::string dictionaryPath = argv[1];
			std::string serchPath = argv[2];
			std::vector<std::string> searchWords = Helper::parseFile(serchPath);
			dict = IDictionaryFactory::CreateFactory(dictionaryInstance);
			dict->indexFile(dictionaryPath);
			auto startSearch = std::chrono::system_clock::now();
			std::ofstream file;
			file.open("output.txt", std::ofstream::app);
			file << searchWords.size() << std::endl;
			for (auto word : searchWords)
			{
				int matches = dict->countMatches(word);
				file << matches << std::endl;
			}
			file.close();
			auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
			std::cout << "Total search time is " << seconds.count() / 1000LL << " seconds." << std::endl;
			seconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startSearch);
			std::cout << "Total pure search time is " << seconds.count() / 1000LL << " seconds." << std::endl;
			delete dict;
		}
		else
		{
			std::cout << "Invalid command line. ";
		}
		std::cout << "Press any key to exit... " << std::endl;
		std::cin.get();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}	
	return 0;
}

