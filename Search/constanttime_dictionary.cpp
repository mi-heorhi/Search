#include "stdafx.h"
#include "constanttime_dictionary.h"

#include "concurent_queue.h"
#include "helper.h"

#include <fstream>
#include <sstream>
#include <thread>


ConstantTimeDictionary::ConstantTimeDictionary()
{
}

int ConstantTimeDictionary::countMatches(std::string & str)
{
	return _indexedDictionary.find(Helper::toUpper(str)) != _indexedDictionary.end() ? 1 : 0;
}

void ConstantTimeDictionary::indexFile(std::string & path)
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
					_indexedDictionary.insert(Helper::toUpper(lines.pop()));
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


ConstantTimeDictionary::~ConstantTimeDictionary()
{
}
