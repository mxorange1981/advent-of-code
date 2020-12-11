#include <fstream>
#include <iostream>
#include <string>

namespace
{
	const std::string filename = "11.txt";
	const int row_length = 91;

	const int top = -row_length;
	const int right = 1;
	const int bottom = row_length;
	const int left = -1;
	const int top_left = top + left;
	const int top_right = top + right;
	const int bottom_right = bottom + right;
	const int bottom_left = bottom + left;

	void print_seating_plan(const std::string & seating)
	{
		std::cout << "---" << std::endl;

		int current_row = 0;
		while (current_row < seating.size())
		{
			std::cout << seating.substr(current_row, row_length) << std::endl;
			current_row += row_length;
		}
	}

	int adjacent_occupied_seats(const std::string & seating, int position)
	{
		int occupied_seats = 0;

		bool onleft = (position % row_length) == 0;
		bool onright = (position % row_length) == (row_length - 1);

		try {
			if (!onleft && seating.at(position + bottom_left) == '#')
				++occupied_seats;
		} catch(...){}
		try {
			if (!onleft && seating.at(position + left) == '#')
				++occupied_seats;
		} catch(...){}
		try {
			if (!onleft && seating.at(position + top_left) == '#')
				++occupied_seats;
		} catch(...){}
		try {
			if (seating.at(position + top) == '#')
				++occupied_seats;
		} catch(...){}
		try {
			if (!onright && seating.at(position + top_right) == '#')
				++occupied_seats;
		} catch(...){}
		try {
			if (!onright && seating.at(position + right) == '#')
				++occupied_seats;
		} catch(...){}
		try {
			if (!onright && seating.at(position + bottom_right) == '#')
				++occupied_seats;
		} catch(...){}
		try {
			if (seating.at(position + bottom) == '#')
				++occupied_seats;
		} catch(...){}

		return occupied_seats;
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
				if (adjacent_occupied_seats(prev, p) == 0)
					next.at(p) = '#';
			}

			if (prev.at(p) == '#')
			{
				if (adjacent_occupied_seats(prev, p) >= 4)
					next.at(p) = 'L';
			}
		}

		print_seating_plan(next);
	}

	std::cout << "occupied_seats = " << std::count(next.begin(), next.end(), '#') << std::endl;

	return 0;
}
