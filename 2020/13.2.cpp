#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

int main(int argc, char const *argv[])
{
	std::ifstream filestream("13.txt");

	filestream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::vector<long> ids;
	{
		std::string id;
		while (std::getline(filestream, id, ','))
		{
			if (id == "x")
				ids.push_back(1);
			else
				ids.push_back(std::stoi(id));
		}
	}

	long max_t = 1;
	for (const auto & id : ids)
		max_t *= id;

	const long filter1 = (37 * 401);
	const long filter2 = (17 * 571);

	bool found = false;
	for (long m = 0; m < max_t / filter1; ++m)
	{
		const long t = (filter1 * m) - 48;

		if (((t + 17) % filter2) != 0)
			continue;

		found = true;

		for (auto it = ids.begin(); it != ids.end() && found; ++it)
		{
			if (*it == 1)
				continue;

			found &= ((t + (it - ids.begin())) % *it == 0);
		}

		if (found)
		{
			std::cout << " t: " << t << std::endl;
			break;
		}
	}

	return 0;
}
