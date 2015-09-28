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
#include <iomanip>

void saveResult(std::vector<int>& results)
{

}

int main(int argc, char *argv[])
{

	IDictionary* dict;
	auto dictionaryInstance = IDictionaryFactory::CONSTANTTIME_DICTIONARY;
	dict = IDictionaryFactory::CreateFactory(dictionaryInstance);
	try
	{
		if (argc == 2)
		{
			std::string dictionaryPath = argv[1];
			std::string serchPath = "";
			
			auto start = std::chrono::system_clock::now();

			dict->indexFile(dictionaryPath);
			auto seconds = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::system_clock::now() - start);
			std::cout << "Pre - processing time is " << std::setprecision(4) << seconds.count() << " seconds." << std::endl;
			delete dict;
		}
		else if (argc == 3)
		{
			
			std::string dictionaryPath = argv[1];
			std::string serchPath = argv[2];
			
			std::vector<int> results;
			dict = IDictionaryFactory::CreateFactory(dictionaryInstance);
			std::vector<std::string> searchWords = Helper::parseFile(serchPath);
			auto start = std::chrono::system_clock::now();
			
			dict->indexFile(dictionaryPath);
			std::ofstream file;
			
			file.open("output.txt", std::ofstream::app);
			auto startSearch = std::chrono::system_clock::now();
			file << searchWords.size() << "\n";
			for (auto word : searchWords)
			{
				file << dict->countMatches(word) << "\n";
			}
			
			auto seconds = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::system_clock::now() - start);
			std::cout << "Total search time is " << std::setprecision(4) << seconds.count() << " seconds." << std::endl;
			seconds = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::system_clock::now() - startSearch);
			std::cout << "Total pure search time is " << std::setprecision(4) << seconds.count() << " seconds." << std::endl;
			file.close();
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

