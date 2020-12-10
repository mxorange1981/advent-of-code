#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <set>

namespace
{
	struct pstat_t
	{
		long long pi = 0;
		std::set<int> ca;
	};
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream("10.txt");
	std::string line;

	std::set<int> adaptors;
	std::map<int, pstat_t> pstats;

	adaptors.insert(0);
	pstats[0] = pstat_t();
	pstats[0].pi = 1;

	while (std::getline(filestream, line))
	{
		std::istringstream linestream(line);
		int joltage; linestream >> joltage;

		adaptors.insert(joltage);
		pstats[joltage] = pstat_t();
	}

	for (const auto & a : adaptors)
	{
		std::cout << "a:" << a;

		// find compatible adapters.
		for (int i = 1; i < 4; ++i)
		{
			if (adaptors.contains(a + i))
				pstats.at(a).ca.insert(a + i);
		}

		std::cout << "\tca: " << pstats.at(a).ca.size();

		// calculate paths in at each stage
		for (const auto & ca : pstats.at(a).ca)
		{
			pstats.at(ca).pi += pstats.at(a).pi;
		}

		std::cout << "\tpi: " << pstats.at(a).pi;
		std::cout << std::endl;
	}

	return 0;
}
