#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char const *argv[])
{
	std::ifstream filestream("10.txt");
	std::vector<int> adaptors;
	std::string line;

	while (std::getline(filestream, line))
	{
		std::istringstream linestream(line);
		int joltage; linestream >> joltage;
		adaptors.push_back(joltage);
	}

	std::sort(adaptors.begin(), adaptors.end());

	int count_diff_1 = 0;
	int count_diff_3 = 1;
	int last_adapter = 0;

	for (const auto j : adaptors)
	{
		switch (j - last_adapter)
		{
		case 1:
			++count_diff_1;
			last_adapter = j;
			break;
		case 3:
			++count_diff_3;
			last_adapter = j;
			break;
		};
	}

	std::cout << count_diff_1 * count_diff_3 << std::endl;

	return 0;
}
