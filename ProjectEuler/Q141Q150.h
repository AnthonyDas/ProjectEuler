#include <iostream>
#include <vector>

//#include "base_helper.h"
//#include "ifstream_with_path.h"
//#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*Some positive integers n have the property that the sum [ n + reverse(n) ] consists entirely
of odd (decimal) digits. For instance, 36 + 63 = 99 and 409 + 904 = 1313. We will call such numbers
reversible; so 36, 63, 409, and 904 are reversible. Leading zeroes are not allowed in either n
or reverse(n).
There are 120 reversible numbers below one-thousand.
How many reversible numbers are there below one-billion (10^9)?*/
int q145() {
	const long long int limit = 1000000000;
	int count = 0;
	
	for (long long int i = 1; i < limit; ++i) {
		// if (i % 1000000 == 0) { std::cout << i << std::endl; }

		long long int carry = i, rev = 0;
		while (carry > 0) {
			rev = (rev * 10) + (carry % 10);
			carry /= 10;
		}

		if (rev < i) {
			continue; // Already considered
		}

		long long int sum = i + rev;
		bool all_odd_digits = true;

		while (sum > 0) {
			if (sum % 2 == 0) {
				all_odd_digits = false;
				break;
			}
			sum /= 10;
		}

		if (all_odd_digits) {
			count += 2; // Plus two because we count abcd and reverse dcba
			// std::cout << count << " " << i << " " << rev << std::endl;
		}
	}

	return count;
}


/* In a 3x2 cross-hatched grid, a total of 37 different rectangles
could be situated within that grid as indicated in the sketch.

There are 5 grids smaller than 3x2, vertical and horizontal dimensions being
important, i.e. 1x1, 2x1, 3x1, 1x2 and 2x2. If each of them is cross-hatched,
the following number of different rectangles could be situated within those
smaller grids:

1x1: 1 
2x1: 4 
3x1: 8 
1x2: 4 
2x2: 18

Adding those to the 37 of the 3x2 grid, a total of 72 different rectangles could
be situated within 3x2 and smaller grids.
How many different rectangles could be situated within 47x43 and smaller grids? */
long long int q147() {
	const int rows = 47, cols = 43;

	long long int rects = 0;

	for (int grid_r = 1; grid_r <= rows; ++grid_r) {
		for (int grid_c = 1; grid_c <= cols; ++grid_c) {

			// Horizontally aligned rectangles
			for (int i = 1; i <= grid_r; ++i) {
				for (int j = 1; j <= grid_c; ++j) {
					// Rectangle has dimensions i x j but will have
					// multiple locaitons within the same grid
					rects += (grid_r - i + 1) * (grid_c - j + 1);

				}
			}

			// Diagonally aligned rectangles
			for (int i = 1; i <= grid_r; ++i) {
				for (int j = 1; j <= grid_c; ++j) {
					// TODO
				}
			}

		}
	}

	return rects;
}