#include <iostream>
#include <vector>

//#include "base_helper.h"
//#include "ifstream_with_path.h"
#include "factors_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


/*We shall define a square lamina to be a square outline with a square "hole"
so that the shape possesses vertical and horizontal symmetry. For example,
using exactly thirty-two square tiles we can form two different square laminae:

With one-hundred tiles, and not necessarily using all of the tiles at one time,
it is possible to form forty-one different square laminae.
Using up to one million tiles how many different square laminae can be formed?*/
int q173() {

	const int limit = 1000000;
	int count = 0;

	int start_side_len = 3;
	while (true) {
		int tiles = 0;

		tiles += (start_side_len * 4) - 4;
		if (tiles > limit) {
			break;
		}
		++count;

		int side_len = start_side_len;

		while (tiles < limit) {
			side_len += 2;
			tiles += (side_len * 4) - 4;
			if (tiles > limit) {
				break;
			}
			++count;
		}

		++start_side_len;
	}

	return count;
}

/*We shall define a square lamina to be a square outline with a square "hole"
so that the shape possesses vertical and horizontal symmetry.
Given eight tiles it is possible to form a lamina in only one way: 3x3 square
with a 1x1 hole in the middle. However, using thirty-two tiles it is possible
to form two distinct laminae.
If t represents the number of tiles used, we shall say that t = 8 is type L(1)
and t = 32 is type L(2). Let N(n) be the number of t <= 1000000 such that t is
type L(n); for example, N(15) = 832. What is SUM{N(n)} for 1 <= n <= 10?*/
int q174() {

	const int limit = 1000000;

	std::map<int, int> tile_counts;

	int start_side_len = 3;
	while (true) {
		int tiles = 0;

		tiles += (start_side_len * 4) - 4;
		if (tiles > limit) {
			break;
		}

		++tile_counts[tiles];

		int side_len = start_side_len;

		while (tiles < limit) {
			side_len += 2;
			tiles += (side_len * 4) - 4;
			if (tiles > limit) {
				break;
			}
			++tile_counts[tiles];
		}

		++start_side_len;
	}

	int count = 0;
	for (std::map<int, int>::const_iterator it = tile_counts.begin(); it != tile_counts.end(); ++it) {
		if (it->second <= 10) {
			++count;
		}
	}

	return count; // 209566

}


/*Find the number of integers 1 < n < 10^7, for which n and n + 1 have the same
number of positive divisors. For example, 14 has the positive divisors
1, 2, 7, 14 while 15 has 1, 3, 5, 15.*/
int q179() {
	
	const int limit = 10000000;
	int count = 0, prv_fact_count = 0;

	for (int n = 2; n <= limit; ++n) {
		// if (n % 100000 == 0) { std::cout << n << std::endl; }

		std::map<int, unsigned int> fact;
		factors_helper::factorise(n, fact);

		int fact_count = 1;
		for (std::map<int, unsigned int>::const_iterator it = fact.begin(); it != fact.end(); ++it) {
			fact_count *= (it->second + 1);
		}

		if (prv_fact_count == fact_count) {
			++count;
		}

		prv_fact_count = fact_count;
	}


	return count; // 986262
}
