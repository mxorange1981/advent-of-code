#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>

const std::string possible_answers = "abcdefghijklmnopqrstuvwxyz";

struct groups_answers_t
{
	std::multiset<char> answers;
	int number_in_group;

	groups_answers_t()
	{
		init();
	}

	void init()
	{
		answers.clear();
		number_in_group = 0;
	}
};

int main(int argc, char const *argv[])
{
	std::ifstream filestream("aoc_day6_input.txt");

	std::string line;
	char answer;

	groups_answers_t temp_group_answers;
	std::vector<groups_answers_t> groups_answers;

	while (std::getline(filestream, line))
	{
		if (line.empty())
		{
			groups_answers.push_back(temp_group_answers);
			temp_group_answers.init();
		}
		else
		{
			++temp_group_answers.number_in_group;
		}

		std::istringstream linestream(line);

		while (linestream >> answer)
		{
			temp_group_answers.answers.insert(answer);
		}
	}

	groups_answers.push_back(temp_group_answers);


	int total_answers = 0;

	for (const auto & group_answers : groups_answers)
	{
		for (const auto & possible_answer : possible_answers)
		{
			total_answers += group_answers.answers.count(possible_answer) == group_answers.number_in_group ? 1 : 0;
		}
	}

	std::cout << "total number of answers " << total_answers << std::endl; 

	return 0;
}
