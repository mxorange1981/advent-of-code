#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main(int argc, char const *argv[])
{
	std::ifstream filestream("14.txt");

	std::map<long, long> mem;
	{
		std::string mask;
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
				std::cout << "using mask: " << mask << std::endl;
			}
			else if (type.substr(0, 3) == "mem")
			{
				const long address = std::stoi(type.substr(4, type.find("]") - 4));
				const long in = std::stoi(value);

				long maskbit = 1L << 35;
				mem[address] = 0;

				for (const auto & m : mask)
				{
					if (m == 'X')
						mem[address] |= (in & maskbit);
					else if (m == '0')
						mem[address] |= !maskbit;
					else if (m == '1')
						mem[address] |= maskbit;
					else
						std::runtime_error("Error: bit mask");

					maskbit >>= 1;
				}

				std::cout
					<< "in: " << in
					<< " out -> mem[" << address << "]: " << mem[address]
					<< std::endl;
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
