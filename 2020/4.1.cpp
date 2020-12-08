#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

class passport_t
{
	std::map<std::string, bool> fields;

public:
	passport_t()
	{
		init();
	}

	void init()
	{
		fields["byr"] = false;
		fields["iyr"] = false;
		fields["eyr"] = false;
		fields["hgt"] = false;
		fields["hcl"] = false;
		fields["ecl"] = false;
		fields["pid"] = false;
		fields["cid"] = true;
	}

	void set_field(const std::string field)
	{
		fields.at(field.substr(0, 3)) = true;
	}

	bool is_valid() const
	{
		bool valid = true;

		for (const auto & field : fields)
			valid &= field.second;

		return valid;
	}

	void print() const
	{
		std::cout
			<< " byr " << fields.at("byr")
			<< " iyr " << fields.at("iyr")
			<< " eyr " << fields.at("eyr")
			<< " hgt " << fields.at("hgt")
			<< " hcl " << fields.at("hcl")
			<< " ecl " << fields.at("ecl")
			<< " pid " << fields.at("pid")
			<< " cid " << fields.at("cid")
			<< " valid " << is_valid()
			<< std::endl;
	}
};

int main(int argc, char const *argv[])
{
	std::ifstream filestream("aoc_day4_input.txt");

	std::string line;
	std::string field;
	std::vector<passport_t> passports;
	passport_t temp_passport;

	while (std::getline(filestream, line))
	{
		if (line.empty())
		{
			passports.push_back(temp_passport);
			temp_passport.init();
		}

		std::istringstream linestream(line);

		while (linestream >> field)
		{
			temp_passport.set_field(field);
		}
	}

	passports.push_back(temp_passport);

	int valid = 0;
	int invalid = 0;

	for (const auto & passport : passports)
	{
		if (passport.is_valid())
			++valid;
		else
			++invalid;
	}

	std::cout 
		<< " Total passports: " << passports.size()
		<< " Valid passports: " << valid
		<< " Invalid passports: " << invalid << std::endl;

	return 0;
}
