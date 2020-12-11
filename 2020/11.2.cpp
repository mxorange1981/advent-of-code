#include <fstream>
#include <iostream>
#include <string>
#include <map>

namespace
{
	const std::string filename = "11.txt";
	const int rows = 97;
	const int cols = 91;

	enum directions
	{
		LEFT = 1,
		TOP = 2,
		RIGHT = 4,
		BOTTOM = 8,
	};

	const int left = -1;
	const int top = -cols;
	const int right = 1;
	const int bottom = cols;

	const std::map<int, int> visible_directions = {
		{BOTTOM|LEFT,  bottom + left},
		{LEFT,         left},
		{TOP|LEFT,     top + left},
		{TOP,          top},
		{TOP|RIGHT,    top + right},
		{RIGHT,        right},
		{BOTTOM|RIGHT, bottom + right},
		{BOTTOM,       bottom},
	};

	int count_occupied_seats(const std::string & seating, const int position)
	{
		int occupied_seats = 0;

		// convert from 0 based to 1 based
		const int x = (position % cols) + 1;
		const int y = ((position / cols) % rows) + 1;

		for (const auto & vd : visible_directions)
		{
			// -1 for left and top due to the position being that distance from the edge.
			const int max_distance_x = (vd.first & RIGHT) ? cols - x : x - 1;
			const int max_distance_y = (vd.first & BOTTOM) ? rows - y : y - 1;

			int max_distance = 0;
			if (vd.first == LEFT || vd.first == RIGHT)
				max_distance = max_distance_x;
			else if (vd.first == TOP || vd.first == BOTTOM)
				max_distance = max_distance_y;
			else
				max_distance = std::min(max_distance_x, max_distance_y);

			std::cout
				<< " position: " << position
				<< " vd.first: " << vd.first
				<< " vd.second: " << vd.second
				<< " x: " << x
				<< " y: " << y
				<< " max_distance_x: " << max_distance_x
				<< " max_distance_y: " << max_distance_y
				<< " max_distance: " << max_distance
				<< std::endl;

			// start at 1 due to multiplication
			for (int p = 1; p <= max_distance; ++p)
			{
				const auto object = seating.at(position + (vd.second * (p)));

				std::cout
					<< " p: " << p
					<< " vd.second * p: " << vd.second * p
					<< " object: " << object
					<< std::endl;

				if (object == 'L')
					break;

				if (object == '#')
				{
					++occupied_seats;
					break;
				}
			}
		}

		return occupied_seats;
	}

	void print_seating_plan(const std::string & seating)
	{
		std::cout << "---" << std::endl;

		for (int row = 0; row < rows; ++row)
			std::cout << seating.substr(row*cols, cols) << std::endl;
	}
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream(filename);
	std::string line;

	std::string seating;
	while (std::getline(filestream, line))
		seating += line;

	std::string prev;
	std::string next = seating;

	print_seating_plan(next);

	while (next != prev)
	{
		prev = next;

		for (int p = 0; p < prev.size(); ++p)
		{
			if (prev.at(p) == 'L')
			{
				if (count_occupied_seats(prev, p) == 0)
					next.at(p) = '#';
			}

			if (prev.at(p) == '#')
			{
				if (count_occupied_seats(prev, p) >= 5)
					next.at(p) = 'L';
			}
		}

		print_seating_plan(next);
	}

	std::cout << "occupied_seats = " << std::count(next.begin(), next.end(), '#') << std::endl;

	return 0;
}
