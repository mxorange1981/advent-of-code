#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace
{
	enum class actions_t
	{
		N,
		E,
		S,
		W,
		F,
		L,
		R,
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

	int ship_pos_x = 0;
	int ship_pos_y = 0;

	int waypoint_pos_x = 10;
	int waypoint_pos_y = 1;

	std::cout
		<< " ship_pos_x: " << ship_pos_x
		<< " ship_pos_y: " << ship_pos_y
		<< " waypoint_pos_x: " << waypoint_pos_x
		<< " waypoint_pos_y: " << waypoint_pos_y
		<< std::endl;

	while (std::getline(filestream, line))
	{
		auto action = to_actions.at(line.substr(0, 1));
		auto value = std::stoi(line.substr(1));

		switch (action)
		{
		case actions_t::F:
			ship_pos_x += waypoint_pos_x * value;
			ship_pos_y += waypoint_pos_y * value;
			break;
		case actions_t::L:
				value = (((value / 360) + 1) * 360) - value;
		case actions_t::R:
			{
				value = abs((((value / 360)) * 360) - value);

				int temp;

				if (value == 90)
				{
					temp = waypoint_pos_y;
					waypoint_pos_y = -waypoint_pos_x;
					waypoint_pos_x = temp;
				}
				else if (value == 180)
				{
					temp = -waypoint_pos_x;
					waypoint_pos_y = -waypoint_pos_y;
					waypoint_pos_x = temp;
				}
				else if (value == 270)
				{
					temp = -waypoint_pos_y;
					waypoint_pos_y = waypoint_pos_x;
					waypoint_pos_x = temp;
				}
				else
					std::cout << "Rotation WTF! " << value << std::endl;
			}
			break;
		case actions_t::E:
		case actions_t::W:
			waypoint_pos_x += (value * adjustments.at(action));
			break;
		case actions_t::N:
		case actions_t::S:
			waypoint_pos_y += (value * adjustments.at(action));
			break;
		default:
			std::cout << "Top level WTF!" << std::endl;
		};

		std::cout
			<< " action: " << from_actions.at(action)
			<< " value: " << value
			<< " ship_pos_x: " << ship_pos_x
			<< " ship_pos_y: " << ship_pos_y
			<< " waypoint_pos_x: " << waypoint_pos_x
			<< " waypoint_pos_y: " << waypoint_pos_y
			<< std::endl;
	}

	std::cout << "Manhattan distance: " << abs(ship_pos_x) + abs(ship_pos_y) << std::endl;

	return 0;
}
