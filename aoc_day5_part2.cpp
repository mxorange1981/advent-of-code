#include <fstream>
#include <iostream>
#include <set>

int find_half_of_range(const int min, const int max)
{
	return (((max - min) / 2)) + min;
}

int process_boardingpass(const std::string & boardingpass)
{
	if (boardingpass.size() != 10)
		std::cerr << "boardingpass incorrect length" << std::endl;

	int min_row = 0;
	int max_row = 127;

	for (int r = 0; r < 7; ++r)
	{
		if (boardingpass[r] == 'F')
		{
			max_row = find_half_of_range(min_row, max_row);
		}
		else if (boardingpass[r] == 'B')
		{
			min_row = find_half_of_range(min_row, max_row) + 1;
		}
		else
		{
			std::cerr << "WTF!?" << std::endl;
		}
	}

	int min_col = 0;
	int max_col = 7;

	for (int c = 7; c < 10; ++c)
	{
		if (boardingpass[c] == 'L')
		{
			max_col = find_half_of_range(min_col, max_col);
		}
		else if (boardingpass[c] == 'R')
		{
			min_col = find_half_of_range(min_col, max_col) + 1;
		}
		else
		{
			std::cerr << "WTF!?" << std::endl;
		}
	}

	return (min_row * 8) + min_col;
}

int process_boardingpass_binary(const std::string & boardingpass)
{
	int row = 0;

	for (int r = 0; r < 7; ++r)
	{
		row <<= 1;

		if (boardingpass[r] == 'B')
			row |= 1;
	}

	int seat = 0;

	for (int c = 7; c < 10; ++c)
	{
		seat <<= 1;

		if (boardingpass[c] == 'R')
			seat |= 1;
	}

	return (row << 3) | seat;
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream("aoc_day5_input.txt");

	std::string boardingpass;

	std::set<int> allocated_seats;

	while (std::getline(filestream, boardingpass))
	{
		int seat_id = process_boardingpass(boardingpass);
		int seat_id2 = process_boardingpass_binary(boardingpass);

		std::cout << seat_id << " " << seat_id2 << std::endl;

		allocated_seats.insert(seat_id);
	}

	for (int seat = *allocated_seats.begin(); seat < *allocated_seats.end(); ++seat)
	{
		if (!allocated_seats.contains(seat))
		{
			std::cout << "unoccupied seat found " << seat << std::endl;
		}
	}
	
	return 0;
}
