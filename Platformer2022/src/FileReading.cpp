#include "FileReading.h"

#include <sstream>
#include <fstream>

std::string ReadFromFile(const std::string& filepath)
{
	std::ifstream data(filepath, std::ios::in | std::ios::binary);

	std::stringstream ss;
	std::string line;

	while (getline(data, line))
	{
		if (line.find("//") == std::string::npos)
			ss << line;
	}

	return ss.str();
}
