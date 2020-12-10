#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

int main(int argc, char const *argv[])
{
	std::ifstream filestream("10.txt");
	std::string line;

	std::map<int, long long> adapters;
	adapters[0] = 1;

	while (std::getline(filestream, line))
	{
		std::istringstream linestream(line);
		int joltage; linestream >> joltage;
		adapters[joltage] = 0;
	}

	for (const auto & a : adapters)
	{
		for (int i = 1; i < 4; ++i)
		{
			if (adapters.contains(a.first + i))
				adapters[a.first + i] += a.second;
		}
	}

	std::cout << adapters.rbegin()->second << std::endl;

	return 0;
}
