#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

namespace
{
	enum class opcodes
	{
		acc,
		jmp,
		nop,
	};

	const std::map<std::string, opcodes> to_opcodes_map = {
		{"acc", opcodes::acc},
		{"jmp", opcodes::jmp},
		{"nop", opcodes::nop},
	};

	const std::map<opcodes, std::string> from_opcodes_map = {
		{opcodes::acc, "acc"},
		{opcodes::jmp, "jmp"},
		{opcodes::nop, "nop"},
	};

	std::istream& operator>>(std::istream& is, opcodes& o)
	{
		std::string s; is >> s;
		o = to_opcodes_map.at(s);

		return is;
	}

	std::ostream& operator<<(std::ostream& os, const opcodes& o)
	{
		os << from_opcodes_map.at(o);

		return os;
	}

	struct instruction_t
	{
		opcodes opcode;
		int arg;
		bool called;
	};

	std::istream& operator>>(std::istream& is, instruction_t& i)
	{
		is >> i.opcode;
		is >> i.arg;

		return is;
	}

	std::ostream& operator<<(std::ostream& os, const instruction_t& i)
	{
		os << i.opcode << " " << i.arg;

		return os;
	}

	bool run_bootcode(std::vector<instruction_t> bootcode)
	{
		int a = 0;
		int ip = 0;

		while(ip < bootcode.size() && !bootcode[ip].called)
		{
			std::cout << "ex: " << ip << " " << bootcode[ip];

			bootcode[ip].called = true;

			switch (bootcode[ip].opcode)
			{
			case opcodes::acc:
				a += bootcode[ip].arg;
			case opcodes::nop:
				++ip;
				break;
			case opcodes::jmp:
				ip += bootcode[ip].arg;
				break;
			};

			std::cout << " a: " << a << " ip: " << ip << std::endl;
		}

		return bootcode[ip].called;
	}
}

int main(int argc, char const *argv[])
{
	std::ifstream filestream("8.txt");

	std::vector<instruction_t> bootcode;
	std::string line;

	while (std::getline(filestream, line))
	{
		std::istringstream linestream(line);
		instruction_t tmp; linestream >> tmp;
		bootcode.push_back(tmp);
	}

	int rip = bootcode.size() - 1;
	std::vector<instruction_t> modified_bootcode;

	do
	{
		modified_bootcode = bootcode;

		std::cout << "running brute force loop: " << rip << " " << modified_bootcode[rip] << " > ";

		switch (modified_bootcode[rip].opcode)
		{
		case opcodes::acc:
			break;
		case opcodes::nop:
			modified_bootcode[rip].opcode = opcodes::jmp;
			break;
		case opcodes::jmp:
			modified_bootcode[rip].opcode = opcodes::nop;
			break;
		};

		std::cout << modified_bootcode[rip] << std::endl;

		--rip;
	}
	while(run_bootcode(modified_bootcode));

	return 0;
}
