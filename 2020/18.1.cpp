#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
	typedef std::vector<std::string> sum_t;

	struct state_t
	{
		long result;
		std::string operation;
	};

	sum_t parse(const std::string & raw)
	{
		std::istringstream linestream(raw);

		sum_t parsed;

		while (!linestream.eof())
		{
			std::string token; linestream >> token;

			const auto parse_brackets = [&token](const char c) {
				const auto n = std::count(token.begin(), token.end(), c);
				token.erase(std::remove(token.begin(), token.end(), c), token.end());
				return n;
			};

			if (const auto n = parse_brackets('('))
			{
				parsed.insert(parsed.cend(), n, "(");
				parsed.push_back(token);
			}
			else if (const auto n = parse_brackets(')'))
			{
				parsed.push_back(token);
				parsed.insert(parsed.cend(), n, ")");
			}
			else
			{
				parsed.push_back(token);
			}
		}

		return parsed;
	}

	long calculate(const sum_t & sum)
	{
		std::deque<state_t> state;
		state.emplace_front();

		for (const auto token : sum)
		{
			if (token == "+")
			{
				state.front().operation = token;
			}
			else if (token == "*")
			{
				state.front().operation = token;
			}
			else if (token == "(")
			{
				state.push_front(state_t());
			}
			else // number
			{
				long num = 0;
				if (token == ")")
				{
					num = state.front().result;
					state.pop_front();
				}
				else
				{
					num = std::stoi(token);
				}

				if (state.front().operation == "+")
				{
					state.front().result += num;
				}
				else if (state.front().operation == "*")
				{
					state.front().result *= num;
				}
				else
				{
					state.front().result = num;
				}

				state.front().operation.clear();
			}
		}

		return state.front().result;
	}
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream("18.txt");
	std::string line;

	long cum = 0;

	while (std::getline(filestream, line))
	{
		const sum_t sum = parse(line);
		const long result = calculate(sum);

		cum += result;
		std::cout << line << " = " << result << std::endl;
	}

	std::cout << cum << std::endl;

	return 0;
}
