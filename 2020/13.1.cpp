#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char const *argv[])
{
	std::ifstream filestream("13.txt");

	long departure_time = 0; filestream >> departure_time;

	std::vector<long> ids;
	{
		std::string id;
		while (std::getline(filestream, id, ','))
		{
			if (id == "x")
				continue;

			ids.push_back(std::stoi(id));
		}
	}

	int actual_departure_time = departure_time - 1;
	int matching_id = 0;
	while (!matching_id)
	{
		++actual_departure_time;

		for (const auto & id : ids)
		{
			if (actual_departure_time % id == 0)
			{
				matching_id = id;
				break;
			}
		}
	}

	std::cout
		<< " departure_time " << departure_time
		<< " actual_departure_time " << actual_departure_time
		<< " matching_id " << matching_id
		<< " ((actual_departure_time - departure_time) * matching_id) "
		<< ((actual_departure_time - departure_time) * matching_id)
		<< std::endl;

	return 0;
}
