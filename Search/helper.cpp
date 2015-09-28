#include "stdafx.h"
#include "helper.h"

#include <algorithm>
#include <regex>
#include <fstream>


std::vector<std::string> Helper::tokenize(const std::string & str)
{
	std::vector<std::string> tokens;
	std::regex rgx("\\w+");
	for (std::sregex_iterator it(str.begin(), str.end(), rgx), it_end; it != it_end; ++it)
		tokens.push_back((*it)[0]);
	return tokens;
}

std::string Helper::toUpper(std::string string)
{
	std::string str(string.c_str());
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

std::vector<std::string> Helper::split(const std::string& str, int delimiter(int) = ::isspace)
{
	std::vector<std::string> result;
	auto end = str.end();
	auto iter = str.begin();
	while (iter != end)
	{
		iter = find_if_not(iter, end, delimiter);
		if (iter == end)
			break;
		auto pos = find_if(iter, end, delimiter);
		result.push_back(std::string(iter, pos));
		iter = pos;
	}
	return result;
}

std::vector<std::string> Helper::parseFile(const std::string & path)
{
	std::vector<std::string> result;
	std::ifstream file;
	file.open(path);
	if (file.is_open())
	{
		std::string str;
		std::getline(file, str);
		while (std::getline(file, str))
		{
			result.push_back(Helper::toUpper(str));
		}
	}
	else
	{
		throw std::exception("File isn't exist.");
	}
	file.close();
	return result;
}

void Helper::appendToFile(const std::string & path, const int matches)
{
	std::ofstream file;
	file.open(path, std::ofstream::app | std::ofstream::out);
	if (file.is_open())
	{
		file << std::to_string(matches) << std::endl;
	}
	file.close();
}
