#pragma once

#include <string>
#include <vector>
#include <map>


class Helper
{
public:
	static std::vector<std::string> tokenize(const std::string& str);
	static std::string toUpper(const std::string str);
	static std::vector<std::string> split(const std::string & str, int delimiter(int));
	static std::vector<std::string> parseFile(const std::string& path);
	static void appendToFile(const std::string& path, const int matches);
};

