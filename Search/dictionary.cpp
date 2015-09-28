#include "stdafx.h"
#include "dictionary.h"
#include "isearcher.h"
#include "kmp_searcher.h"
#include "concurent_queue.h"

#include <fstream>
#include <thread>


Dictionary::Dictionary()
{
}

int Dictionary::countMatches(std::string& str)
{
	int result_1 = 0;
	int result_2 = 0;
	bool done = false;
	ConcurentQueue<std::string> lines_1;
	ConcurentQueue<std::string> lines_2;

	std::string pattern_1 = Helper::toUpper(str);
	std::string pattern_2 = Helper::toUpper(str);

	ISearcher* sercher_1 = new KMPSearcher();
	ISearcher* sercher_2 = new KMPSearcher();

	std::thread producer([&]() {
		int i = 0;
		for (auto line : _indexDictionary)
		{
			if (i % 2 == 0)
				lines_2.push(line);
			else
				lines_1.push(line);
			i++;
		}
		done = true;
	});
	std::thread consumer_1([&]() {
		while (!done) {
			while (!lines_1.empty()) {
				if(sercher_1->find(pattern_1.c_str(), lines_1.pop().c_str()))
					result_1++;
			}
		}
	});
	std::thread consumer_2([&]() {
		while (!done) {
			while (!lines_2.empty()) {
				if (sercher_2->find(pattern_2.c_str(), lines_2.pop().c_str()))
					result_2++;
			}
		}
	});

	producer.join();
	consumer_1.join();
	consumer_2.join();

	delete sercher_1;
	delete sercher_2;

	return result_1 + result_2;
}

void Dictionary::indexFile(std::string& path)
{
	std::ifstream file;
	file.open(path);
	std::string str;
	int line = 0;
	ConcurentQueue<std::string> lines;
	bool done = false;

	if (file.is_open())
	{
		std::getline(file, str);
		std::thread producer([&]() {
			while (std::getline(file, str))
			{
				lines.push(str);
				line++;
			}
			done = true;
		});
		std::thread consumer([&]() {
			while (!done) {
				while (!lines.empty()) {
					_indexDictionary.push_back(Helper::toUpper(lines.pop()));
				}
			}
		});

		producer.join();
		consumer.join();
	}
	else
	{
		throw std::exception("File isn't exist.");
	}
	file.close();	
}

Dictionary::~Dictionary()
{
}