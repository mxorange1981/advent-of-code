#include <fstream>
#include <iostream>

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

int main(int argc, char const *argv[])
{
	std::ifstream filestream("aoc_day5_input.txt");

	std::string boardingpass;

	int max_seat_id  = 0;

	while (std::getline(filestream, boardingpass))
	{
		int seat_id = process_boardingpass(boardingpass);

		if (seat_id > max_seat_id)
			max_seat_id = seat_id;
	}

	std::cout << " max seat id: " << max_seat_id << std::endl;
	
	return 0;
}
