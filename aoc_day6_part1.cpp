#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>

int main(int argc, char const *argv[])
{
	std::ifstream filestream("aoc_day6_input.txt");

	std::string line;
	char answer;
	std::set<char> temp_group_answers;
	std::vector<std::set<char>> groups_answers;

	while (std::getline(filestream, line))
	{
		if (line.empty())
		{
			groups_answers.push_back(temp_group_answers);
			temp_group_answers.clear();
		}

		std::istringstream linestream(line);

		while (linestream >> answer)
		{
			temp_group_answers.insert(answer);
		}
	}

	groups_answers.push_back(temp_group_answers);


	int total_answers = 0;

	for (const auto & group_answers : groups_answers)
	{
		total_answers += group_answers.size();
	}

	std::cout << "total number of answers " << total_answers << std::endl; 

	return 0;
}
