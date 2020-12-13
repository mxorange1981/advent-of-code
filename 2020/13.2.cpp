#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>

int main(int argc, char const *argv[])
{
	std::ifstream filestream("13.test.txt");

	filestream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::map<long, long> ids;
	{
		std::string id;
		int p = -1;
		while (std::getline(filestream, id, ','))
		{
			std::cout << " " << id;
			++p;
			if (id != "x")
				ids.insert({std::stoi(id), p});
		}
	}

	long convergence = 1;
	for (const auto id : ids)
		convergence *= id.first;

	long b = ids.rbegin()->first;
	long p = ids.rbegin()->second;

	ids.erase(b);

	std::cout
		<< " convergence " << convergence
		<< " b " << b
		<< " p " << p
		<< std::endl;

	bool found = false;
	for (long y = 0; y < (convergence / b); ++y)
	{
		found = true;

		const long t = b * y;
		for (auto it = ids.begin(); it != ids.end() && found; ++it)
			found &= ((t + (it->second - p)) % it->first == 0);

		if (found)
		{
			std::cout << " t: " << ((b * y) - p)  << std::endl;
			break;
		}
	}

	return 0;
}
