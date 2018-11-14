#include <iostream>
#include <vector>
#include <algorithm> //std::sort()
#include <sstream> // ostringstream

#include "number_helper.h"
#include "wall_tile_helper.h"
// #include "base_helper.h"
// #include "ifstream_with_path.h"
// #include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*Working from left-to-right if no digit is exceeded by the digit to its left
it is called an increasing number; for example, 134468. Similarly if no digit
is exceeded by the digit to its right it is called a decreasing number; for
example, 66420. We shall call a positive integer that is neither increasing
nor decreasing a "bouncy" number; for example, 155349.
Clearly there cannot be any bouncy numbers below one-hundred, but just over half
of the numbers below one-thousand (525) are bouncy. In fact, the least number for
which the proportion of bouncy numbers first reaches 50% is 538.
Surprisingly, bouncy numbers become more and more common and by the time we reach
21780 the proportion of bouncy numbers is equal to 90%.
Find the least number for which the proportion of bouncy numbers is exactly 99%. */
int q112() {

	int count = 0, n = 100;

	while (true) {
		// if (n % 10000 == 0) { std::cout << n << std::endl; }

		if (number_helper::is_bouncy(n)) {
			++count;
		}

		if (count * 100 == n * 99) {
			break;
		}

		++n;
	}

	return n;
}


long long int recursive_count_increasing_numbers(const int &index, const int &digit, std::map<int, long long int> &cache) {
	if (index == 0 || digit == 9) {
		return 1;
	}

	const int key = (index * 10) + digit;
	const std::map<int, long long int>::const_iterator it = cache.find(key);
	if (it == cache.end()) {

		long long int ways = 0;

		for (int i = digit; i <= 9; ++i) {
			ways += recursive_count_increasing_numbers(index - 1, i, cache);
		}

		cache.insert(std::pair<int, long long int>(key, ways));

		return ways;
	}

	return it->second;
}


long long int recursive_count_decreasing_numbers(const int &index, const int &digit, std::map<int, long long int> &cache) {
	if (index == 0 || digit == 0) {
		return 1;
	}

	const int key = (index * 10) + digit;
	const std::map<int, long long int>::const_iterator it = cache.find(key);
	if (it == cache.end()) {

		long long int ways = 0;

		for (int i = digit; i >= 0; --i) {
			ways += recursive_count_decreasing_numbers(index - 1, i, cache);
		}

		cache.insert(std::pair<int, long long int>(key, ways));

		return ways;
	}

	return it->second;
}

/*Working from left-to-right if no digit is exceeded by the digit to its left it is
called an increasing number; for example, 134468. Similarly if no digit is exceeded
by the digit to its right it is called a decreasing number; for example, 66420.
We shall call a positive integer that is neither increasing nor decreasing a "bouncy"
number; for example, 155349. As n increases, the proportion of bouncy numbers below n
increases such that there are only 12951 numbers below one-million that are not bouncy
and only 277032 non-bouncy numbers below 10^10.
How many numbers below a googol (10^100) are not bouncy?*/
long long int q113() {
	// Numbers below 10^100 will have up to 100 digits, (i.e. set index = 100)

	long long int count = 0;

	std::map<int, long long int> inc_cache, dec_cache;

	// Generate increasing numbers and count them up
	int index = 100, digit = 0;
	count += recursive_count_increasing_numbers(index, digit, inc_cache);
	--count; // -1 as generates 0 as a possibility

	// Generate decreasing numbers and count them up.
	// Need a for loop as function can't handle leading zeros,
	// e.g. 09876 won't appear decreasing to the function. 
	digit = 9;
	for (int i = 1; i <= index; ++i) {
		count += recursive_count_decreasing_numbers(i, digit, dec_cache);
		--count; // -1 as generates 0 as a possibility
	}

	// Take away numbers which are both increasing and decreasing
	// as these have been double counted. Will be of the form
	// nnn...n (of varying length) for 1 <= n <= 9 and proceeded by
	// varying number of zeros.
	count -= index * 9;

	return count; // 51161058134250
}

/*A row measuring seven units in length has red blocks with a minimum length of
three units placed on it, such that any two red blocks (which are allowed to be
different lengths) are separated by at least one black square. There are exactly
seventeen ways of doing this.
How many ways can a row measuring fifty units in length be filled?
NOTE: Although the example above does not lend itself to the possibility, in
general it is permitted to mix block sizes. For example, on a row measuring
eight units in length you could use red (3), black (1), and red (4).*/
long long int q114() {

	const int blacks = 50, min_red_len = 3, separation = 1;
	// const int blacks = 1000000, min_red_len = 25, separation = 1; // HackerRank

	return wall_tile_helper::varying_tile_len_with_separation_count(min_red_len, separation, blacks); // 16475640049
}

/*NOTE: This is a more difficult version of Problem 114.
A row measuring n units in length has red blocks with a minimum length of m units
placed on it, such that any two red blocks (which are allowed to be different lengths)
are separated by at least one black square. Let the fill-count function, F(m, n),
represent the number of ways that a row can be filled.
For example, F(3, 29) = 673135 and F(3, 30) = 1089155.
That is, for m = 3, it can be seen that n = 30 is the smallest value for which
the fill-count function first exceeds one million. In the same way, for m = 10,
it can be verified that F(10, 56) = 880711 and F(10, 57) = 1148904, so n = 57
is the least value for which the fill-count function first exceeds one million.
For m = 50, find the least value of n for which the fill-count function first
exceeds one million.*/
int q115() {

	int n = 50, min_red_len = 50, separation = 1;

	const int target = 1000000;

	long long int count = 0;
	while (count < target) {
		++n;

		count = wall_tile_helper::varying_tile_len_with_separation_count(min_red_len, separation, n);
	}

	return n; // 168
}


/*A row of five black square tiles is to have a number of its tiles replaced
with coloured oblong tiles chosen from red (length two), green (length three),
or blue (length four). If red tiles are chosen there are exactly seven ways
this can be done. If green tiles are chosen there are three ways. And if blue
tiles are chosen there are two ways.
Assuming that colours cannot be mixed there are 7 + 3 + 2 = 12 ways of replacing
the black tiles in a row measuring five units in length. How many different ways
can the black tiles in a row measuring fifty units in length be replaced if colours
cannot be mixed and at least one coloured tile must be used?
NOTE: This is related to Problem 117.*/
long long int q116() {

	const int blacks = 50;
	long long int count = 0;


	// Red tiles
	count += wall_tile_helper::fixed_tile_len_count(2, blacks);

	// Green tiles
	count += wall_tile_helper::fixed_tile_len_count(3, blacks);

	// Blue tiles
	count += wall_tile_helper::fixed_tile_len_count(4, blacks);

	// Not allowed to have all black tiles which each of
	// the three recursions above will include.
	count -= 3;

	return count; // 20492570929
}


/*Using a combination of black square tiles and oblong tiles chosen from:
red tiles measuring two units, green tiles measuring three units, and blue
tiles measuring four units, it is possible to tile a row measuring five
units in length in exactly fifteen different ways.
How many ways can a row measuring fifty units in length be tiled?
NOTE: This is related to Problem 116.*/
long long int q117() {

	const int blacks = 50, min = 2, max = 4;

	// Cache our results to avoid duplicate processing
	std::map<int, long long int> ways_cache;

	return wall_tile_helper::varying_tile_len_count(min, max, blacks); // 100808458960497
}


/*Using all of the digits 1 through 9 and concatenating them freely to form
decimal integers, different sets can be formed. Interestingly with the set
{2,5,47,89,631}, all of the elements belonging to it are prime.
How many distinct sets containing each of the digits one through nine exactly
once contain only prime elements?*/
int q118() {


	return 1;
}


/*The number 512 is interesting because it is equal to the sum of its digits
raised to some power: 5 + 1 + 2 = 8, and 8^3 = 512. Another example of a number
with this property is 614656 = 28^4.
We shall define a(n) to be the nth term of this sequence and insist that a number
must contain at least two digits to have a sum.
You are given that a(2) = 512 and a(10) = 614656. Find a(30).*/
long long int q119() {
	const int limit = 30;

	std::vector<long long int> numbers;
	int base = 1;

	// Trying to generate the numbers is way more efficient
	// than checking each and every n. Let's just trial generate
	// some and see how many we produce, hoping to produce at least
	// 30 to give an upper bouund on a(30).
	while (numbers.size() < limit) {
		++base;

		long long int base_pow = base;
		int pow = 1;

		while (true) {
			long long int base_pow_sav = base_pow;
			base_pow *= base;
			++pow;

			// We are finished with this base if there is an overflow
			if (base_pow < base_pow_sav) {
				break;
			}

			if (number_helper::digits_sum(base_pow) == base) {
				numbers.push_back(base_pow);
				// std::cout << numbers.size() << " " << base_pow << " " << base << " " << pow << std::endl;
			}
		}
	}

	// The above successfully generates 30 numbers fulfilling the necessary criteria.
	// The 30th number in ascending order is 81920000000000000. This is an upper bound on a(30).

	std::sort(numbers.begin(), numbers.end());

	long long int upper_bound = numbers[limit - 1];
	long long int sqrt_upper_bound = (long long int)sqrt(upper_bound);

	while (base < sqrt_upper_bound) {
		++base;

		long long int base_pow = base;
		int pow = 1;

		while (true) {
			long long int base_pow_sav = base_pow;
			base_pow *= base;
			++pow;

			// We are finished with this base if base_pow exceeds
			// upper_bound or there is an overflow
			if (base_pow > upper_bound || base_pow < base_pow_sav) {
				break;
			}

			if (number_helper::digits_sum(base_pow) == base) {
				numbers.push_back(base_pow);
				// std::cout << numbers.size() << " " << base_pow << " " << base << " " << pow << std::endl;

				// Calculate the new upper bound as we have found a smaller n
				std::sort(numbers.begin(), numbers.end());

				upper_bound = numbers[limit - 1];
				sqrt_upper_bound = (long long int)sqrt(upper_bound);
			}
		}
	}

	return numbers[limit - 1];
}
