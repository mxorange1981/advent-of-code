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

	void add_precedence(std::string * line)
	{
		// find +
		//  if token left is number then wrap it
		//  if token right is number then wrap it
		//  if token left is close bracket then find associated open bracket and wrap it
		//  if token right is open bracket then find associated close bracket and wrap it

		// remove all whitespace
		line->erase(std::remove(line->begin(), line->end(), ' '), line->end());

		std::cout << "before: " << *line << std::endl;

		for (long i = 0; i < line->size(); ++i)
		{
			if (line->at(i) == '+')
			{
				const char left = line->at(i - 1);
				const char right = line->at(i + 1);

				if (left != ')' && right != '(')
				{
					line->insert((i++) - 1, "(");
					line->insert((i++) + 2, ")");
				}
				else if(left == ')' && right != '(')
				{
					// find position of associated opening bracket

					long brackets = 1;
					long p = (i++) - 2;
					while (brackets)
					{
						if (line->at(p) == '(')
							--brackets;
						else if (line->at(p) == ')')
							++brackets;

						if(brackets) --p;
					}

					line->insert(p, "(");
					line->insert((i++) + 2, ")");
				}
				else if(left != ')' && right == '(')
				{
					line->insert((i++) - 1, "(");

					// find position of associated closing bracket

					long brackets = 1;
					long p = (i++) + 2;
					while (brackets)
					{
						if (line->at(p) == '(')
							++brackets;
						else if (line->at(p) == ')')
							--brackets;

						if(brackets) ++p;
					}

					line->insert(p, ")");
				}
				else if(left == ')' && right == '(')
				{
					// find position of associated opening bracket

					long brackets = 1;
					long p = (i++) - 2;
					while (brackets)
					{
						if (line->at(p) == '(')
							--brackets;
						else if (line->at(p) == ')')
							++brackets;

						if(brackets) --p;
					}

					line->insert(p, "(");

					// find position of associated closing bracket

					brackets = 1;
					p = (i++) + 2;
					while (brackets)
					{
						if (line->at(p) == '(')
							++brackets;
						else if (line->at(p) == ')')
							--brackets;

						if(brackets) ++p;
					}

					line->insert(p, ")");
				}
			}
		}

		std::cout << "after: " << *line << std::endl;

		// add uniform whitespace
		for (long i = 0; i < line->size(); ++i)
			line->insert(i++, " ");
	}

	sum_t tokenise(const std::string & line)
	{
		std::istringstream linestream(line);

		sum_t tokens;

		while (!linestream.eof())
		{
			std::string token; linestream >> token;
			tokens.push_back(token);
		}

		return tokens;
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
	long count = 0;

	while (std::getline(filestream, line))
	{
		add_precedence(&line);
		const sum_t sum = tokenise(line);
		const long result = calculate(sum);

		cum += result;
		std::cout << ++count << " " << result << std::endl;
	}

	std::cout << cum << std::endl;

	return 0;
}
