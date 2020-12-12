#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace
{
	enum class actions_t
	{
		N = 0,
		E = 90,
		S = 180,
		W = 270,
		F = 1,
		L = 2,
		R = 3,
	};

	const std::map<std::string, actions_t> to_actions = {
		{"N", actions_t::N},
		{"E", actions_t::E},
		{"S", actions_t::S},
		{"W", actions_t::W},
		{"F", actions_t::F},
		{"L", actions_t::L},
		{"R", actions_t::R},
	};


	const std::map<actions_t, std::string> from_actions = {
		{actions_t::N, "N"},
		{actions_t::E, "E"},
		{actions_t::S, "S"},
		{actions_t::W, "W"},
		{actions_t::F, "F"},
		{actions_t::L, "L"},
		{actions_t::R, "R"},
	};

	const std::map<actions_t, int> adjustments = {
		{actions_t::N, 1},
		{actions_t::E, 1},
		{actions_t::S, -1},
		{actions_t::W, -1},
	};
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream("12.txt");
	std::string line;

	int pos_x = 0;
	int pos_y = 0;
	auto baring = actions_t::E;

	std::cout
		<< " pos_x: " << pos_x
		<< " pos_y: " << pos_y
		<< " baring: " << static_cast<int>(baring)
		<< std::endl;

	while (std::getline(filestream, line))
	{
		auto action = to_actions.at(line.substr(0, 1));
		auto value = std::stoi(line.substr(1));

		action = (action == actions_t::F ? baring : action);
		switch (action)
		{
		case actions_t::L:
				value = (((value / 360) + 1) * 360) - value;
		case actions_t::R:
			{
				int nb = abs(static_cast<int>(baring) + value);

				if (nb >= 360)
					nb -= ((nb / 360) * 360);

				baring = static_cast<actions_t>(nb);
			}
			break;
		case actions_t::E:
		case actions_t::W:
			pos_x += (value * adjustments.at(action));
			break;
		case actions_t::N:
		case actions_t::S:
			pos_y += (value * adjustments.at(action));
			break;
		default:
			std::cout << "Top level WTF!" << std::endl;
		};

		std::cout
			<< " action: " << from_actions.at(action)
			<< " value: " << value
			<< " pos_x: " << pos_x
			<< " pos_y: " << pos_y
			<< " baring: " << static_cast<int>(baring)
			<< std::endl;
	}

	std::cout << "Manhattan distance: " << abs(pos_x) + abs(pos_y) << std::endl;

	return 0;
}
