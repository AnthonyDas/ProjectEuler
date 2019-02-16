#include <iostream>
#include <vector>

//#include "base_helper.h"
//#include "ifstream_with_path.h"
#include "factors_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


void recursive_selection_172(long long int &count, std::vector<int> &selection,
	const int &index, const int &digits_remaining, const int &max_digit_occurrences) {

	// If we have selected 18-digits, determine how many different
	// 18-digit numbers can be made with the given selection
	if (!digits_remaining) {

		static std::vector<int> fact({ 1, 1, 2, 6 }); // 0!, 1!, 2!, 3!

		// Select the leading digit (which must be non zero)
		for (size_t i = 1; i < selection.size(); ++i) {
			if (selection[i]) {
				// Ways to arrange remaining 17 digits = 17!
				long long int ways = 355'687'428'096'000; 
				
				for (size_t j = 0; j < selection.size(); ++j) {
					if (j == i) {
						ways /= fact[selection[j] - 1]; // Used 1 for leading digit
					}
					else {
						ways /= fact[selection[j]];
					}
				}
				count += ways;
			}
		}

		return;
	}

	// Decide how many times digit "index" occurs
	const int start = std::max(0, digits_remaining - (index * max_digit_occurrences));
	const int end = std::min(max_digit_occurrences, digits_remaining);
	for (int i = start; i <= end; ++i) {
		selection[index] = i;
		recursive_selection_172(count, selection, (index - 1), (digits_remaining - i), max_digit_occurrences);
		selection[index] = 0;
	}
}

/* How many 18-digit numbers n (without leading zeros) are there
such that no digit occurs more than three times in n? */
long long int q172() {
	long long int count = 0;
	const int digits_required = 18;
	const int max_digit_occurrences = 3;

	std::vector<int> selection(10, 0);
	recursive_selection_172(count, selection, (int)(selection.size() - 1), digits_required, max_digit_occurrences);

	return count; // 227'485'267'000'992'000
}


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

		auto factors = factors_helper::factorise(n);

		int fact_count = 1;
		for (auto it = factors.begin(); it != factors.end(); ++it) {
			fact_count *= (it->second + 1);
		}

		if (prv_fact_count == fact_count) {
			++count;
		}

		prv_fact_count = fact_count;
	}


	return count; // 986262
}
