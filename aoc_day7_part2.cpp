#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

std::map<std::string, std::map<std::string, int>> contained_by_rules;

int count_all_inner_bags(const std::string & bag)
{
	int total = 1;

	for (const auto & bag : contained_by_rules[bag])
	{
		total += count_all_inner_bags(bag.first) * bag.second;
	}

	return total;
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream("aoc_day7_input.txt");

	std::string rulestring;

	while (std::getline(filestream, rulestring))
	{
		std::istringstream rulestream(rulestring);
		std::string outer_bag_colour;

		std::getline(rulestream, outer_bag_colour, ',');

		std::string inner_bag_colour_and_quantity;

		while (std::getline(rulestream, inner_bag_colour_and_quantity, ','))
		{
			if (inner_bag_colour_and_quantity == "0")
				continue;

			int inner_bag_quantity;
			std::string inner_bag_colour;

			inner_bag_quantity = std::stoi(inner_bag_colour_and_quantity.substr(0, inner_bag_colour_and_quantity.find_first_of(" ")));
			inner_bag_colour = inner_bag_colour_and_quantity.substr(inner_bag_colour_and_quantity.find_first_of(" ")+1);

			contained_by_rules[outer_bag_colour].emplace(inner_bag_colour, inner_bag_quantity);
		}
	}

	int total = count_all_inner_bags("shiny gold") - 1;

	std::cout << total << std::endl;

	return 0;
}
