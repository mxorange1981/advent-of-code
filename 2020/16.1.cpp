#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace
{
	struct field_range_t
	{
		int min;
		int max;
	};
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream("16.txt");

	std::vector<field_range_t> field_ranges;
	std::vector<std::vector<int>> tickets;

	std::string line;
	bool ignore = true;

	while (std::getline(filestream, line))
	{
		auto section_marker = std::string::npos;
		if ((section_marker = line.find_first_of(":")) != std::string::npos)
		{
			const auto section = line.substr(0, section_marker);

			if (section == "your ticket")
			{
				ignore = true;
			}
			else if (section == "nearby tickets")
			{
				ignore = false;
			}
			else
			{
				const auto ranges = line.substr(section_marker + 2);
				const auto range1 = ranges.substr(0, ranges.find(" or "));
				const auto range2 = ranges.substr(ranges.find(" or ") + 4);

				const auto range1min = range1.substr(0, range1.find("-"));
				const auto range1max = range1.substr(range1.find("-") + 1);

				field_ranges.push_back({std::stoi(range1min), std::stoi(range1max)});

				const auto range2min = range2.substr(0, range2.find("-"));
				const auto range2max = range2.substr(range2.find("-") + 1);

				field_ranges.push_back({std::stoi(range2min), std::stoi(range2max)});
			}
		}
		else if (!ignore)
		{
			std::istringstream linestream(line);

			std::string field;
			std::vector<int> ticket;

			while (std::getline(linestream, field, ','))
				ticket.push_back(std::stoi(field));

			tickets.push_back(ticket);
		}
	}

	int scanning_error_rate = 0;

	for (const auto & ticket : tickets)
	{
		for (const auto & ticket_field : ticket)
		{
			bool valid = false;

			for (const auto & field_range : field_ranges)
			{
				if (ticket_field >= field_range.min && ticket_field <= field_range.max)
				{
					valid = true;
					break;
				}
			}

			if (!valid)
				scanning_error_rate += ticket_field;
		}
	}

	std::cout << "scanning_error_rate " << scanning_error_rate << std::endl;

	return 0;
}
