#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> values = {
	1384,
	1396,
	1072,
	1903,
	1387,
	1763,
	1600,
	1862,
	1992,
	1585,
	1909,
	1352,
	1288,
	1910,
	1070,
	1421,
	1802,
	1669,
	1059,
	1235,
	1854,
	1722,
	1275,
	198,
	1476,
	1588,
	1708,
	1217,
	1596,
	1355,
	1566,
	1973,
	1335,
	1480,
	1115,
	1272,
	1998,
	1821,
	2007,
	1721,
	1885,
	1420,
	1412,
	1487,
	1941,
	1835,
	1558,
	1061,
	1582,
	1940,
	1942,
	1210,
	1350,
	1175,
	1047,
	1456,
	1548,
	1110,
	1510,
	1995,
	1644,
	1968,
	1297,
	1198,
	1471,
	1360,
	1363,
	1528,
	1393,
	1365,
	1837,
	1886,
	2001,
	1161,
	1349,
	1787,
	988,
	1331,
	1960,
	1607,
	1324,
	97,
	1986,
	1955,
	1773,
	1443,
	1852,
	1368,
	1050,
	1378,
	1239,
	1750,
	1868,
	816,
	1965,
	1661,
	1728,
	1981,
	984,
	1037,
	1525,
	1789,
	1318,
	1952,
	1359,
	1358,
	1869,
	1641,
	1240,
	1542,
	1959,
	1022,
	1475,
	1733,
	1081,
	1889,
	1138,
	1757,
	1736,
	1723,
	1543,
	1820,
	1128,
	1039,
	1683,
	1477,
	1375,
	1499,
	676,
	1195,
	1250,
	220,
	1581,
	1328,
	1187,
	1485,
	1216,
	1769,
	1139,
	1064,
	1908,
	1516,
	1490,
	1419,
	1749,
	1347,
	1758,
	1024,
	1053,
	1842,
	1861,
	1403,
	1966,
	1546,
	1134,
	1593,
	1734,
	1916,
	1867,
	1101,
	1126,
	1301,
	1841,
	1515,
	1244,
	1401,
	1637,
	1054,
	1309,
	1933,
	1512,
	1263,
	1815,
	1634,
	1823,
	1295,
	1583,
	1104,
	1765,
	1850,
	1311,
	1692,
	1905,
	1149,
	1780,
	1330,
	1666,
	996,
	1913,
	1140,
	1089,
	1484,
	1356,
	1296,
	1323,
	1160,
	1881,
	1123,
	1166,
	1929,
};

int find_number_for_sum(
	const int number_count,
	const int running_total,
	const int max_additional_numbers = 2,
	const int target_total = 2020
)
{
	const auto remainder = target_total - running_total;
	auto value = values.crbegin();

	while (remainder >= *value)
	{
		const auto current_total = running_total + *value;

		if (number_count < max_additional_numbers && current_total < target_total)
		{
			const auto result = find_number_for_sum(number_count + 1, current_total);

			if (result)
			{
				std::cout << *value << std::endl;
				return *value * result;
			}
		}
		else if (number_count == max_additional_numbers && current_total == target_total)
		{
			std::cout << "huzzah! " << target_total << " found using:" << std::endl;
			std::cout << *value << std::endl;
			return *value;
		}

		++value;
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	std::sort(values.begin(), values.end(), std::greater<int>());

	for (const auto & value : values)
	{
		const auto result = find_number_for_sum(1, value);
		if (result)
		{
			std::cout << value << std::endl;
			std::cout << "answer = " << result * value << std::endl;
			return 0;
		}
	}

	return 1;
}
