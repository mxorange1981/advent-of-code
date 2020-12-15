#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
	std::vector<int> numbers = {2,20,0,4,1,17};

	while(numbers.size() < 2020)
	{
		int i = numbers.size() - 2;
		for (; i >= 0; --i)
			if (*numbers.rbegin() == numbers[i])
				break;
		++i;

		if (i == 0)
			numbers.push_back(i);
		else
			numbers.push_back(numbers.size() - i);
	}

	std::cout << "2020th number: " << *numbers.rbegin() << std::endl;

	return 0;
}
