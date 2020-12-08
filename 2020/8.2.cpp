#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

namespace
{
	struct vm_state_t
	{
		int ip;
		int a;

		std::set<int> p_ip;

		vm_state_t() :
			ip(0), a(0)
		{}
	};

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

		instruction_t() :
			opcode(opcodes::nop), arg(0)
		{}
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

	std::deque<vm_state_t> vm;
	vm.emplace_front();

	int ild_flag = false;
	int foc_flag = false;

	while(vm.front().ip < bootcode.size())
	{
		if (vm.front().p_ip.contains(vm.front().ip))
		{
			std::cout << "INFINTATE LOOP DETECTED!!!" << std::endl;

			ild_flag = true;
			foc_flag = true;

			vm.pop_front();
		}

		std::cout << "ex: " << vm.front().ip << " " << bootcode[vm.front().ip];

		vm.front().p_ip.insert(vm.front().ip);

		switch (bootcode[vm.front().ip].opcode)
		{
		case opcodes::acc:
			{
				vm.front().a += bootcode[vm.front().ip].arg;
				++vm.front().ip;
			}
			break;
		case opcodes::nop:
			{
				if (!ild_flag)
					vm.push_front(vm.front());

				if(!foc_flag)
					++vm.front().ip;

				if(foc_flag)
				{
					vm.front().ip += bootcode[vm.front().ip].arg;
					foc_flag = false;
				}
			}
			break;
		case opcodes::jmp:
			{
				if (!ild_flag)
					vm.push_front(vm.front());

				if(!foc_flag)
					vm.front().ip += bootcode[vm.front().ip].arg;

				if(foc_flag)
				{
					++vm.front().ip;
					foc_flag = false;
				}
			}
			break;
		};

		std::cout << " a: " << vm.front().a << " ip: " << vm.front().ip << std::endl;
	}

	return 0;
}
