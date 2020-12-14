#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
	std::ifstream filestream("14.txt");

	std::map<long, long> mem;
	{
		std::string mask;
		std::vector<int> floating_positions;
		std::string line;
		while (std::getline(filestream, line))
		{
			std::istringstream linestream(line);
			std::string type; linestream >> type;
			linestream.ignore(std::string(" = ").size());
			std::string value; linestream >> value;

			if (type == "mask")
			{
				mask = value;
				floating_positions.clear();

				for (int i = mask.size() - 1; i > -1 ; --i)
				{
					if (mask[i] == 'X')
						floating_positions.push_back(mask.size() - i - 1);
				}

				std::cout << "using mask: " << mask << " floating_positions:";

				for (int i = 0; i < floating_positions.size(); ++i)
					std::cout << " " << floating_positions[i];

				std::cout << std::endl;
			}
			else if (type.substr(0, 3) == "mem")
			{
				const long in_address = std::stoi(type.substr(4, type.find("]") - 4));
				const long in = std::stoi(value);

				long maskbit = 1L << 35;
				long base_address = 0;

				for (const auto & m : mask)
				{
					if (m == 'X')
						base_address |= !maskbit;
					else if (m == '0')
						base_address |= (in_address & maskbit);
					else if (m == '1')
						base_address |= maskbit;
					else
						std::runtime_error("Error: bit mask");

					maskbit >>= 1;
				}

				std::cout
					<< "in_address " << in_address
					<< " base_address " << base_address
					<< " in " << in
					<< std::endl;

				for (int o = 0; o < std::pow(2, floating_positions.size()); ++o)
				{
					long offset = 0;

					int floating_position = floating_positions.size() - 1;
					maskbit = 1L << floating_position;

					std::cout
						<< "floating_position " << floating_position
						<< " maskbit " << maskbit
						<< std::endl;

					while (maskbit)
					{
						if (o & maskbit)
						{
							offset += std::pow(2, floating_positions[floating_position]);
						}

						--floating_position;
						maskbit >>= 1;
					}

					std::cout
						<< "offset " << offset
						<< " base_address * offset " << (base_address + offset)
						<< std::endl;

					mem[base_address + offset] = in;
				}
			}
			else
				std::runtime_error("Error: type");
		}
	}

	long total = 0;
	for (const auto & a : mem)
		total += a.second;

	std::cout << "total " << total << std::endl;

	return 0;
}
