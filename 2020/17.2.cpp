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
	typedef std::vector<dimension_t> hyper_t; // w

	const point_type active = '#';
	const point_type inactive = '.';

	hyper_t init_dimension(const long x_size, const long y_size, const long z_size, const long w_size)
	{
		line_t l(x_size, inactive);
		plane_t p(y_size, l);
		dimension_t d(z_size, p);
		return hyper_t(w_size, d);
	}

	bool is_point_active(
		const long px,
		const long py,
		const long pz,
		const long pw,
		const hyper_t & curr
	)
	{
		bool currently_active = false;
		int active_neighbours = 0;

		for (long nw = -1; nw <= 1; ++nw)
		{
			for (long nz = -1; nz <= 1; ++nz)
			{
				for (long ny = -1; ny <= 1; ++ny)
				{
					for (long nx = -1; nx <= 1; ++nx)
					{
						if (! ((px + nx) < 0
							|| (px + nx) >= curr.front().front().front().size()
							|| (py + ny) < 0
							|| (py + ny) >= curr.front().front().size()
							|| (pz + nz) < 0
							|| (pz + nz) >= curr.front().size()
							|| (pw + nw) < 0
							|| (pw + nw) >= curr.size()
						))
						{
							if (nw == 0 && nz == 0 && ny == 0 && nx == 0)
							{
								currently_active = (curr[pw][pz][py][px] == active);
							}
							else
							{
								if (curr[pw + nw][pz + nz][py + ny][px + nx] == active)
									++active_neighbours;
							}
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

	hyper_t run_cycle(const hyper_t & curr)
	{
		auto next = init_dimension(
			curr.front().front().front().size() + 2,
			curr.front().front().size() + 2,
			curr.front().size() + 2,
			curr.size() + 2
		);

		for (long w = 0; w < next.size(); ++w)
		{
			for (long z = 0; z < next.front().size(); ++z)
			{
				for (long y = 0; y < next.front().front().size(); ++y)
				{
					for (long x = 0; x < next.front().front().front().size(); ++x)
					{
						next[w][z][y][x]
							= is_point_active(
								x - 1, y - 1, z - 1, w - 1,
								curr
							)
							? active
							: inactive;
					}
				}
			}
		}

		return next;
	}

	void print(const hyper_t & hyper)
	{
		long active_points = 0;
		long inactive_points = 0;

		for (const auto & dimension : hyper)
		{
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

			std::cout << std::endl;
		}

		std::cout << "inactive " << inactive_points << " active " << active_points << std::endl;
	}
}

int main(int argc, char const *argv[])
{
	hyper_t hyper;
	{
		std::ifstream filestream("17.txt");
		std::string line;

		plane_t plane;
		while (std::getline(filestream, line))
			plane.emplace_back(line.begin(), line.end());

		dimension_t dimension = {plane};
		hyper.push_back(dimension);
	}

	print(hyper);

	for (int cycle = 0; cycle < 6; ++cycle)
	{
		hyper = run_cycle(hyper);
		print(hyper);
	}

	return 0;
}
