#include <fstream>
#include <iostream>
#include <map>
#include <set>

std::map<std::string, std::map<std::string, int>> rules;

int count_all_inner_bags(const std::string & bag)
{
	int total = 1;

	for (const auto & bag : rules[bag])
	{
		total += count_all_inner_bags(bag.first) * bag.second;
	}

	return total;
}

int main(int argc, char const *argv[])
{
	const std::string delim1 = " bags contain ";
	const std::string delim2 = ", ";
	const std::string delim3 = ".";
	const std::string delim4 = " ";
	const std::string delim5 = " bag";

	std::ifstream filestream("aoc_day7_input.txt");
	std::string rulestring;

	while (std::getline(filestream, rulestring))
	{
		const auto delim1_pos = rulestring.find(delim1);

		const std::string outer_bag_colour = rulestring.substr(0, delim1_pos);

		rulestring = rulestring.substr(delim1_pos + delim1.size());

		size_t delim2_pos = 0;
		size_t delim3_pos = 0;

		while ((delim2_pos = rulestring.find(delim2)) != std::string::npos
			|| (delim3_pos = rulestring.find(delim3)) != std::string::npos)
		{
			const auto delim_pos = delim2_pos != std::string::npos ? delim2_pos : delim3_pos;
			const auto delim_size = delim2_pos != std::string::npos ? delim2.size() : delim3.size();

			const std::string inner_bag = rulestring.substr(0, delim_pos);

			rulestring = rulestring.substr(delim_pos + delim_size);

			if (inner_bag == "no other bags")
				continue;

			const auto delim4_pos = inner_bag.find(delim4);
			const auto delim5_pos = inner_bag.find(delim5) - delim4.size() - 1;
			const auto inner_bag_quantity = std::stoi(inner_bag.substr(0, delim4_pos));
			const auto inner_bag_colour = inner_bag.substr(delim4_pos + delim4.size(), delim5_pos);

			rules[outer_bag_colour].emplace(inner_bag_colour, inner_bag_quantity);
		}
	}

	int total = count_all_inner_bags("shiny gold") - 1;
	std::cout << total << std::endl;

	return 0;
}
