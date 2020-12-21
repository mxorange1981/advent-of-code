#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
	typedef char point_type;
	typedef std::vector<point_type> line_t; // x
	typedef std::vector<line_t> plane_t; // y
	typedef std::vector<plane_t> dimension_t; // z

	const point_type active = '#';
	const point_type inactive = '.';

	dimension_t init_dimension(const long x_size, const long y_size, const long z_size)
	{
		line_t l(x_size, inactive);
		plane_t p(y_size, l);
		return dimension_t(z_size, p);
	}

	bool is_point_active(
		const long px,
		const long py,
		const long pz,
		const dimension_t & curr
	)
	{
		bool currently_active = false;
		int active_neighbours = 0;

		for (long nz = -1; nz <= 1; ++nz)
		{
			for (long ny = -1; ny <= 1; ++ny)
			{
				for (long nx = -1; nx <= 1; ++nx)
				{
					if (! ((px + nx) < 0
						|| (px + nx) >= curr.front().front().size()
						|| (py + ny) < 0
						|| (py + ny) >= curr.front().size()
						|| (pz + nz) < 0
						|| (pz + nz) >= curr.size()
					))
					{
						if (nz == 0 && ny == 0 && nx == 0)
						{
							currently_active = (curr[pz][py][px] == active);
						}
						else
						{
							if (curr[pz + nz][py + ny][px + nx] == active)
								++active_neighbours;
						}
					}
				}
			}
		}

		if (currently_active && (active_neighbours == 2 || active_neighbours == 3))
			return true;
		else if (!currently_active && active_neighbours == 3)
			return true;

		return false;
	}

	dimension_t run_cycle(const dimension_t & curr)
	{
		auto next = init_dimension(
			curr.front().front().size() + 2,
			curr.front().size() + 2,
			curr.size() + 2
		);

		for (long z = 0; z < next.size(); ++z)
		{
			for (long y = 0; y < next.front().size(); ++y)
			{
				for (long x = 0; x < next.front().front().size(); ++x)
				{
					next[z][y][x]
						= is_point_active(
							x - 1, y - 1, z - 1,
							curr
						)
						? active
						: inactive;
				}
			}
		}

		return next;
	}

	void print(const dimension_t & dimension)
	{
		long active_points = 0;
		long inactive_points = 0;

		for (const auto & plane : dimension)
		{
			for (const auto & line : plane)
			{
				for (const auto & point : line)
				{
					std::cout << point;

					if (point == active)
						++active_points;
					else if (point == inactive)
						++inactive_points;
					else
						std::cerr << "WTF!?" << std::endl;
				}

				std::cout << std::endl;
			}

			std::cout << std::endl;
		}

		std::cout << "inactive " << inactive_points << " active " << active_points << std::endl;
	}
}

int main(int argc, char const *argv[])
{
	dimension_t dimension;
	{
		std::ifstream filestream("17.txt");
		std::string line;

		plane_t plane;
		while (std::getline(filestream, line))
			plane.emplace_back(line.begin(), line.end());

		dimension.push_back(plane);
	}

	print(dimension);

	for (int cycle = 0; cycle < 6; ++cycle)
	{
		dimension = run_cycle(dimension);
		print(dimension);
	}

	return 0;
}
