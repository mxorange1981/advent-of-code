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
		std::vector<int> fps;
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
				fps.clear();

				for (auto it = mask.rbegin(); it != mask.rend(); ++it)
				{
					if (*it == 'X')
						fps.push_back(it - mask.rbegin());
				}
			}
			else if (type.substr(0, 3) == "mem")
			{
				const long in_address = std::stoi(type.substr(4, type.find("]") - 4));
				const long in_value = std::stoi(value);

				long base_address = 0;
				long maskbit = 1L << 35;

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

				for (long i = 0; i < std::pow(2, fps.size()); ++i)
				{
					long offset = 0;

					long fp = fps.size() - 1;
					maskbit = 1L << fp;

					while (maskbit)
					{
						if (i & maskbit)
							offset += std::pow(2, fps[fp]);

						--fp;
						maskbit >>= 1;
					}

					mem[base_address + offset] = in_value;
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
