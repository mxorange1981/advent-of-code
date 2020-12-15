#include <iostream>
#include <map>

int main(int argc, char const *argv[])
{
	std::map<long, long> number_history = {
		{2, 1},
		{20, 2},
		{0, 3},
		{4, 4},
		{1, 5},
	};

	long number = 17;
	long count = 6;

	while(count < 30000000)
	{
		if (!number_history.contains(number))
		{
			number_history[number] = count;
			number = 0;
		}
		else
		{
			long age = count - number_history[number];
			number_history[number] = count;
			number = age;
		}

		++count;
	}

	std::cout << "30000000th number: " << number << std::endl;

	return 0;
}
