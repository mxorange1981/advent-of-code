#include <algorithm>
#include <cctype>
#include <functional>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

namespace
{
	bool string_year_between(const std::string & value, const int min, const int max)
	{
		if (value.size() != 4)
			return false;

		if (!std::all_of(value.begin(), value.end(), [](unsigned char c){return std::isdigit(c);}))
			return false;

		int year;
		std::istringstream yearstream(value);
		yearstream >> year;

		return (year >= min && year <= max);
	}

	bool validate_byr_field_data(const std::string & value)
	{
		return string_year_between(value, 1920, 2002);
	}

	bool validate_iyr_field_data(const std::string & value)
	{
		return string_year_between(value, 2010, 2020);
	}

	bool validate_eyr_field_data(const std::string & value)
	{
		return string_year_between(value, 2020, 2030);
	}

	bool string_height_between(
		const std::string & value,
		const std::string & units,
		const int min,
		const int max
	)
	{
		if (!value.ends_with(units))
			return false;

		std::string temp_height = value.substr(0, value.size() - 2);

		if (!std::all_of(temp_height.begin(), temp_height.end(), [](unsigned char c){return std::isdigit(c);}))
			return false;

		int height;
		std::istringstream heightstream(temp_height);
		heightstream >> height;

		return (height >= min && height <= max);
	}

	bool validate_hgt_field_data(const std::string & value)
	{
		if (string_height_between(value, "cm", 150, 193))
			return true;

		return string_height_between(value, "in", 59, 76);
	}

	bool validate_hcl_field_data(const std::string & value)
	{
		if (value.size() != 7)
			return false;

		if (value[0] != '#')
			return false;

		return std::all_of(value.begin()+1, value.end(), [](unsigned char c){return std::isxdigit(c);});
	}

	bool validate_ecl_field_data(const std::string & value)
	{
		std::set<std::string> accepted_eye_colours {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

		return accepted_eye_colours.contains(value);
	}

	bool validate_pid_field_data(const std::string & value)
	{
		if (value.size() != 9)
			return false;

		return true;
	}

	bool validate_cid_field_data(const std::string & value)
	{
		return true;
	}

	class passport_t
	{
		std::map<std::string, bool> fields;
		std::map<std::string, std::function<bool(const std::string&)>> validation_functions;

	public:
		passport_t()
		{
			validation_functions["byr"] = validate_byr_field_data;
			validation_functions["iyr"] = validate_iyr_field_data;
			validation_functions["eyr"] = validate_eyr_field_data;
			validation_functions["hgt"] = validate_hgt_field_data;
			validation_functions["hcl"] = validate_hcl_field_data;
			validation_functions["ecl"] = validate_ecl_field_data;
			validation_functions["pid"] = validate_pid_field_data;
			validation_functions["cid"] = validate_cid_field_data;


			init();
		}

		void init()
		{
			fields.clear();

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
			std::string key;
			std::string value;

			std::istringstream fieldstream(field);

			std::getline(fieldstream, key, ':');
			std::getline(fieldstream, value, ':');

			fields.at(key) = validation_functions.at(key)(value);
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
}

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
