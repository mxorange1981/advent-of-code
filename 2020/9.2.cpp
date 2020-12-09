#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace
{
	const int target = 258585477;
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream("9.txt");
	std::vector<int> msg;
	std::string line;

	while (std::getline(filestream, line))
	{
		std::istringstream linestream(line);
		int tmp; linestream >> tmp;
		msg.push_back(tmp);
	}

	for (auto it = msg.begin(); it != msg.end(); ++it)
	{
		int total = *it;
		auto nit = it;

		while (total < target)
		{
			total += *(++nit);

			if (total == target)
			{
				// inc so it can be used as the end point.
				++nit;

				std::cout
					<< "answer = "
					<< *std::min_element(it, nit) + *std::max_element(it, nit)
					<< std::endl;

				return 0;
			}
		}
	}

	return 1;
}
