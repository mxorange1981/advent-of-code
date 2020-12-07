#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

std::map<std::string, std::map<std::string, int>> contained_by_rules;

std::set<std::string> find_all_container_bags(const std::string & bag)
{
	std::set<std::string> bags;

	for (const auto & bag : contained_by_rules[bag])
	{
		bags.insert(bag.first);
		bags.merge(find_all_container_bags(bag.first));
	}

	return bags;
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

			contained_by_rules[inner_bag_colour].emplace(outer_bag_colour, inner_bag_quantity);
		}
	}

	std::set<std::string> bags = find_all_container_bags("shiny gold");

	for (const auto & bag : bags)
	{
		std::cout << bag << std::endl;
	}

	std::cout << bags.size() << std::endl;

	return 0;
}
