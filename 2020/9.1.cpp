#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace
{
	const int preamble_length = 25;

	bool is_target_valid(
		int target,
		std::vector<int>::iterator preamble_start,
		std::vector<int>::iterator preamble_stop
	)
	{
		std::vector<int> values(preamble_start, preamble_stop+1);
		std::sort(values.begin(), values.end(), std::greater<int>());

		for (const auto & value1 : values)
		{
			const auto remainder = target - value1;
			auto value2 = values.crbegin();

			while (remainder >= *value2)
			{
				if (value1 + *value2 == target)
				{
					std::cout << target << " is valid" << std::endl;
					return true;
				}

				++value2;
			}
		}

		std::cout << target << " is invalid" << std::endl;
		return false;
	}
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

	bool target_is_valid = true;
	int preamble_start = -1;
	int preamble_stop = -1;
	int target = -1;

	const auto shift_preamble_window = [&](){
		++preamble_start;
		target = preamble_length + preamble_start;
		preamble_stop = target - 1;
	};
	shift_preamble_window();

	while (target < msg.size() && target_is_valid)
	{
		target_is_valid = is_target_valid(
			msg[target],
			msg.begin() + preamble_start,
			msg.begin() + preamble_stop
		);

		shift_preamble_window();
	}

	return 0;
}
