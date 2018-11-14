#include <iostream>
#include <vector>
#include <algorithm> // std::max, std::min

// #include "base_helper.h"
// #include "ifstream_with_path.h"
// #include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*Let ABCD be a quadrilateral whose vertices are lattice points lying on
the coordinate axes as follows:
A(a, 0), B(0, b), C(-c, 0), D(0, -d), where 1 <= a, b, c, d <= m and a, b, c, d, m are integers.
It can be shown that for m = 4 there are exactly 256 valid ways to construct ABCD.
Of these 256 quadrilaterals, 42 of them STRICTLY contain a square number of lattice points.
How many quadrilaterals ABCD strictly contain a square number of lattice points for m = 100?*/
int q504() {
	
	// Note that counting the lattice points within any quadrant simply comes
	// down to the distance of each vertex (situated along the axes distinguishing
	// the quadrant) from the origin. In particular, the count does not matter
	// up the quadrant itself. We therefore calculate (and cache) the points
	// for each combination of vertices possible.

	const int m = 100, key_offset = (int)pow(10, number_helper::digits_count(m));
	
	int count = 0;

	std::map<int, int> points_cache;

	for (int x = 1; x <= m; ++x) {
		for (int y = 1; y <= x; ++y) {
	
			// Lattice points strictly contained and excluding axis, (i.e. 0 < i < x)
			int points = 0;
			for (int i = 1; i < x; ++i) {
				// Equation of a straight line: y = (y-axis intercept) + (grad * x)
				// where grad is gradient of line connecting (0, y) and (x, 0).

				int y_val = y - (int)ceil((double)(y * i) / (double)x); // ceil as proceeded by minus

				// If y_val is integer we need to subtract 1 to get points contained.
				points += y_val - ((y * i) % x == 0 ? 1 : 0);
			}

			points_cache.insert(std::pair<int, int>(x * key_offset + y, points));
		}
	}

	for (int a = 1; a <= m; ++a) {
		for (int b = 1; b <= m; ++b) {
			for (int c = 1; c <= m; ++c) {
				for (int d = 1; d <= m; ++d) {

					int total_points = 1; // Origin (0, 0)
					total_points += points_cache[std::max(a, b) * key_offset + std::min(a, b)];
					total_points += points_cache[std::max(b, c) * key_offset + std::min(b, c)];
					total_points += points_cache[std::max(c, d) * key_offset + std::min(c, d)];
					total_points += points_cache[std::max(d, a) * key_offset + std::min(d, a)];

					// Axis points
					total_points += a + b + c + d - 4; // -4 strictly contains

					if (total_points == 0) { continue; }

					int sqrt_total_points = (int)sqrt(total_points);
					if (sqrt_total_points * sqrt_total_points == total_points) {

						++count;
						// std::cout << count << " " << total_points << " " << a << " " << b << " " << c << " " << d << std::endl;
					}
				}
			}
		}
	}

	return count; // 694687
}
