#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

namespace
{
	struct field_range_t
	{
		int min;
		int max;
	};

	struct field_t
	{
		std::string name;
		field_range_t lower;
		field_range_t upper;
	};
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream("16.txt");

	std::vector<field_t> fields;
	std::vector<std::vector<int>> tickets;
	std::vector<int> myticket;

	std::string line;
	bool readmyticket = true;

	while (std::getline(filestream, line))
	{
		auto section_marker = std::string::npos;
		if ((section_marker = line.find_first_of(":")) != std::string::npos)
		{
			const auto section = line.substr(0, section_marker);

			if (section == "your ticket")
			{
				readmyticket = true;
			}
			else if (section == "nearby tickets")
			{
				readmyticket = false;
			}
			else
			{
				field_t f;

				f.name = section;

				const auto ranges = line.substr(section_marker + 2);
				const auto range1 = ranges.substr(0, ranges.find(" or "));
				const auto range2 = ranges.substr(ranges.find(" or ") + 4);

				const auto range1min = range1.substr(0, range1.find("-"));
				const auto range1max = range1.substr(range1.find("-") + 1);

				f.lower.min = std::stoi(range1min);
				f.lower.max = std::stoi(range1max);

				const auto range2min = range2.substr(0, range2.find("-"));
				const auto range2max = range2.substr(range2.find("-") + 1);

				f.upper.min = std::stoi(range2min);
				f.upper.max = std::stoi(range2max);

				fields.push_back(f);
			}
		}
		else
		{
			std::istringstream linestream(line);

			std::string field;
			std::vector<int> ticket;

			while (std::getline(linestream, field, ','))
				ticket.push_back(std::stoi(field));

			if (readmyticket)
				myticket = ticket;
			else
				tickets.push_back(ticket);
		}
	}

	const auto is_value_valid_for_field = [&](const int fv, const field_t & f) {
		const bool lower_range_valid = (fv >= f.lower.min && fv <= f.lower.max);
		const bool upper_range_valid = (fv >= f.upper.min && fv <= f.upper.max);
		return lower_range_valid || upper_range_valid;
	};

	const auto is_field_valid = [&](const int fv) {
		return std::any_of(fields.begin(), fields.end(), [&](const field_t & f){
			return is_value_valid_for_field(fv, f);
		});
	};

	tickets.erase(
		std::remove_if(
			tickets.begin(),
			tickets.end(),
			[&](const auto ticket_fields) {
				return !std::all_of(ticket_fields.begin(), ticket_fields.end(), is_field_valid);
			}
		),
		tickets.end()
	);

	struct field_valid_positions_t
	{
		field_t f;
		std::vector<int> vps;
	};

	std::multimap<int, field_valid_positions_t> field_valid_positions;

	const auto field_position_is_valid = [&](const int p, const field_t & f) {
		return std::all_of(
			tickets.begin(),
			tickets.end(),
			[&](const auto & ticket_fields) {
				return is_value_valid_for_field(ticket_fields[p], f);
			}
		);
	};

	for (const auto f : fields)
	{
		field_valid_positions_t fps;
		fps.f = f;

		for (int i = 0; i < fields.size(); ++i)
		{
			if (field_position_is_valid(i, f))
				fps.vps.push_back(i);
		}

		field_valid_positions.insert({fps.vps.size(), fps});
	}

	for (const auto fps : field_valid_positions)
	{
		std::cout << fps.first << " " << fps.second.f.name << std::endl;

		for (const auto vp : fps.second.vps)
		{
			std::cout << vp << " ";
		}

		std::cout << std::endl;
	}

	std::map<int, field_t> position_field_map;

	for (const auto fps : field_valid_positions)
	{
		for (const auto vp : fps.second.vps)
		{
			if (!position_field_map.contains(vp))
			{
				position_field_map[vp] = fps.second.f;
			}
		}
	}

	long ans = 1;
	for (const auto pf : position_field_map)
	{
		std::cout << pf.first << " " << pf.second.name << std::endl;

		if (pf.second.name.find("departure") != std::string::npos)
			ans *= myticket[pf.first];
	}

	std::cout << ans << std::endl;

	return 0;
}
