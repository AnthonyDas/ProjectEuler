#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm> // std::sort, std::min

#include "base_helper.h"
#include "vector_int.h"
#include "ifstream_with_path.h"
#include "number_helper.h"
#include "factors_helper.h"
#include "su_doku.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


/*The points P (x1, y1) and Q (x2, y2) are plotted at integer co-ordinates
and are joined to the origin, O(0,0), to form triangle OPQ.

There are exactly fourteen triangles containing a right angle that can be formed
when each co-ordinate lies between 0 and 2 inclusive; that is,
0 <= x1, y1, x2, y2 <= 2.

Given that 0 <= x1, y1, x2, y2 <= 50, how many right triangles can be formed?*/
int q91() {
	const int size = 50;
	int count = 0;

	std::vector<int> lengths;
	lengths.reserve(4);

	// Grid contains (size + 1) * (size + 1) points but numbering starts at 0
	for (int p = 1; p < (size + 1) * (size + 1) - 1; ++p) {
		for (int q = p + 1; q <= (size + 1) * (size + 1) - 1; ++q) { // q larger than p
			
			int x1, y1, x2, y2;
			x1 = p % (size + 1);
			y1 = p / (size + 1);
			x2 = q % (size + 1);
			y2 = q / (size + 1);

			// All three points (inc. origin) lie on x/y axis
			if ((x1 == 0 && x2 == 0) || (y1 == 0 && y2 == 0)) {
				continue;
			}

			lengths.clear();

			lengths.push_back((x1 * x1) + (y1 * y1)); // Length OP
			lengths.push_back((x2 * x2) + (y2 * y2)); // Length OQ
			lengths.push_back(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))); // Length PQ

			std::sort(lengths.begin(), lengths.end());

			if (lengths[2] == lengths[0] + lengths[1]) {
				++count;
			}
		}
	}

	return count; // 14234
}


/*A number chain is created by continuously adding the square of the digits
in a number to form a new number until it has been seen before. For example,
44 -> 32 -> 13 -> 10 -> 1 -> 1
85 -> 89 -> 145 -> 42 -> 20 -> 4 -> 16 -> 37 -> 58 -> 89
Therefore any chain that arrives at 1 or 89 will become stuck in an endless loop.
What is most amazing is that EVERY starting number will eventually arrive at 1 or 89.
How many starting numbers below ten million will arrive at 89?*/
int q92() {
	const int limit = 10000000;
	int count = 0;
	
	for (int i = 2; i < limit; ++i) {
		// if (i % 1000000 == 0) { std::cout << i << std::endl; }

		int next = i;

		while (next != 1 && next != 89) {
			int carry = next;
			next = 0;
			while (carry > 0) {
				int digit = carry % 10;
				next += digit * digit;
				carry /= 10;
			}
		}

		if (next == 89) {
			++count;
		}
	}

	return count;
}


/*It is easily proved that no equilateral triangle exists with integral length sides
and integral area. However, the almost equilateral triangle 5-5-6 has an area of 12
square units. We shall define an almost equilateral triangle to be a triangle for
which two sides are equal and the third differs by no more than one unit.
Find the sum of the perimeters of all almost equilateral triangles with integral side
lengths and area and whose perimeters do not exceed one billion (1,000,000,000).*/
int q94() {
	// Using the distinct side length as a base and the duplicate side lengths
	// as two sides of a roof, we form our triangle. Note that drawing a vertical
	// line from the mid-point of the base upwards to the tip forms a right angled triangle.
	// The height of the vertical line, h, can be calculated using Pythagoras' Theorem.
	// It must also be integral length for the area of the equilateral triangle to
	// be integral. (As equilateral triangle's area = 1/2 * base * h). 

	const int limit = 1000000000;

	int sum = 0;

	// Let x be the duplicate side. It must be odd because +/- 1 from
	// an even number gives an odd length for the base. Taking half the
	// base length results in a non-integer which won't work in Pythagors'
	// Theorem to get an integral height length.
	for (long long int x = 3; x <= (limit / 3); x += 2) {
		// if (x % 10000000 == 1) { std::cout << x << std::endl; }

		long long int half_y = (x - 1)/2;

		long long int h = (long long int)sqrt((x * x) - (half_y * half_y));
		if ((h * h) == (x * x) - (half_y * half_y)) {
			sum += (int)(2 * (x + half_y));

			// std::cout << x << " " << (x - 1) << " " << 2 * (x + half_y) << std::endl;
		}

		half_y = (x + 1) / 2;

		h = (long long int)sqrt((x * x) - (half_y * half_y));
		if ((h * h) == (x * x) - (half_y * half_y)) {
			sum += (int)(2 * (x + half_y));

			// std::cout << x << " " << (x + 1) << " " << 2 * (x + half_y) << std::endl;
		}
	}

	return sum; // 518408346
}

/*The proper divisors of a number are all the divisors excluding the number itself.
For example, the proper divisors of 28 are 1, 2, 4, 7, and 14. As the sum of these
divisors is equal to 28, we call it a perfect number.
Interestingly the sum of the proper divisors of 220 is 284 and the sum of the proper
divisors of 284 is 220, forming a chain of two numbers. For this reason, 220 and 284
are called an amicable pair.
Perhaps less well known are longer chains. For example, starting with 12496, we form
a chain of five numbers:
12496 -> 14288 -> 15472 -> 14536 -> 14264 (-> 12496 -> ...)
Since this chain returns to its starting point, it is called an amicable chain.
Find the smallest member of the longest amicable chain with no element exceeding one
million.*/
int q95() {
	const int limit = 1000000;
	int max_chain_len = 0, max_chain_n = 0;

	std::vector<int> chain_lens(limit + 1, -1);

	for (int n = 2; n < limit; ++n) {
		// if (n % 100000 == 0) { std::cout << n << std::endl; }

		// Have we already done this processing in an earlier iteration?
		if (chain_lens[n] != -1) {
			continue;
		}

		std::set<int> s_chain; 
		std::queue<int> q_chain;

		// Include starting n
		s_chain.insert(n);
		q_chain.push(n);

		int prop_div = n;

		while (true) {

			prop_div = factors_helper::sum_proper_divisors(prop_div);

			// Above limit - all current queue elements ultimately go above limit so fail
			if (prop_div > limit) {
				while (!q_chain.empty()) {
					chain_lens[q_chain.front()] = 0;
					q_chain.pop();
				}
				break;
			}

			// Have we already done this processing in an earlier iteration?
			// If current n is part of a chain which has some smaller element,
			// prop_div say, then n will not be the answer as it isn't the smallest
			// element in the chain.
			if (chain_lens[prop_div] != -1 || prop_div < n) {
				chain_lens[n] = 0;
				break;
			}

			// Repeated number which is the chain starting number 
			if (prop_div == n) {
				const int size = (int)q_chain.size();
				if (max_chain_len < size) {
					// std::cout << n << " " << size << std::endl;
					max_chain_len = size;
					max_chain_n = n;
				}
				// All current queue elements have the same chain length
				while (!q_chain.empty()) {
					chain_lens[q_chain.front()] = size;
					q_chain.pop();
				}
				break;
			}

			// Repeated number which isn't the chain starting number
			if (prop_div == 1 || s_chain.find(prop_div) != s_chain.end()) {
				// All queue elements before the repeated element will fail
				while (!q_chain.empty() && q_chain.front() != prop_div) {
					chain_lens[q_chain.front()] = 0;
					q_chain.pop();
				}
				// All queue elements at and after the repeated element have same chain length
				const int size = (int)q_chain.size();
				int min_n = INT_MAX;
				while (!q_chain.empty()) {
					min_n = std::min(min_n, q_chain.front());
					chain_lens[q_chain.front()] = size;
					q_chain.pop();
				}
				if (max_chain_len < size) {
					// std::cout << min_n << " " << size << std::endl;
					max_chain_len = size;
					max_chain_n = min_n;
				}
				break;
			}

			s_chain.insert(prop_div);
			q_chain.push(prop_div);
		}
	}

	return max_chain_n;
}


/*Su Doku (Japanese meaning number place) is the name given to a popular puzzle concept.
Its origin is unclear, but credit must be attributed to Leonhard Euler who invented a
similar, and much more difficult, puzzle idea called Latin Squares. The objective of
Su Doku puzzles, however, is to replace the blanks (or zeros) in a 9 by 9 grid in such
that each row, column, and 3 by 3 box contains each of the digits 1 to 9. Below is an
example of a typical starting puzzle grid and its solution grid.
A well constructed Su Doku puzzle has a unique solution and can be solved by logic,
although it may be necessary to employ "guess and test" methods in order to eliminate
options (there is much contested opinion over this). The complexity of the search
determines the difficulty of the puzzle; the example above is considered easy because
it can be solved by straight forward direct deduction.
The 6K text file, sudoku.txt (right click and 'Save Link/Target As...'), contains fifty
different Su Doku puzzles ranging in difficulty, but all with unique solutions
(the first puzzle in the file is the example above).
By solving all fifty puzzles find the sum of the 3-digit numbers found in the top left
corner of each solution grid; for example, 483 is the 3-digit number found in the top
left corner of the solution grid above.*/
int q96() {

	int sum = 0;

	std::vector<std::vector<int> > grid;

	ifstream_with_path fin("Problem96.txt");
	std::string row_str;
	while (std::getline(fin, row_str)) {
		if (row_str.find("Grid") != std::string::npos) {
			// std::cout << row_str << std::endl;
			grid.clear();
			continue;
		}

		std::vector<int> row;
		for (std::string::const_iterator it = row_str.begin(); it != row_str.end(); ++it) {
			row.push_back(*it - '0');
		}

		grid.push_back(row);

		if (grid.size() == 9) {
			su_doku puzzle(grid);

			sum += (*(puzzle[0][0].begin()) * 100) + (*(puzzle[0][1].begin()) * 10) + *(puzzle[0][2].begin());

			// std::cout << puzzle << std::endl;
		}

	}
	fin.close();

	return sum;
}

/*The first known prime found to exceed one million digits was discovered in 1999,
and is a Mersenne prime of the form (2^6972593) - 1; it contains exactly 2,098,960 digits.
Subsequently other Mersenne primes, of the form (2^p) - 1, have been found which contain more digits.
However, in 2004 there was found a massive non-Mersenne prime which contains
2,357,207 digits: (28433 * (2^7830457)) + 1.
Find the last ten digits of this prime number.*/
long long int q97() {
	const int digits_required = 10;

	std::vector<int> binary = base_helper::convert_decimal_to_base(7830457, 2);

	vector_int res(1), pow_2(2);
	for (std::vector<int>::const_reverse_iterator rit = binary.rbegin(); rit != binary.rend(); ++rit) {
		if (rit != binary.rbegin()) {
			pow_2 *= pow_2;

			// Only care about last 10 digits
			pow_2.keep_last_digits(digits_required);
		}
		if (*rit) {
			res *= pow_2;

			// Only care about last 10 digits
			res.keep_last_digits(digits_required);
		}
	}

	res *= 28433;
	res += 1;

	return res.keep_last_digits(digits_required);
}


/*Comparing two numbers written in index form like 211 and 37 is not difficult,
as any calculator would confirm that 211 = 2048 < 37 = 2187.
However, confirming that 632382^518061 > 519432^525806 would be much more difficult,
as both numbers contain over three million digits.
Using base_exp.txt (right click and 'Save Link/Target As...'), a 22K text file
containing one thousand lines with a base/exponent pair on each line, determine which
line number has the greatest numerical value.
NOTE: The first two lines in the file represent the numbers in the example given above.*/
int q99() {

	std::vector<std::pair<int, long double> > log_base_exp;

	ifstream_with_path fin("Problem99.txt");
	int base, exp;
	for (int i = 1; i <= 1000; ++i) {
		fin >> base >> exp;

		// Taking logs of (b^e) preserves relative ordering:
		// log(b^e) = e.log(b);
		log_base_exp.push_back(std::pair<int, long double>(i, exp * log(base)));
		
	}
	fin.close();

	sort(log_base_exp.begin(), log_base_exp.end(), [](std::pair<int, long double> a, std::pair<int, long double> b) {
		return a.second < b.second;
	});

	return log_base_exp.back().first;
}


/*If a box contains twenty-one coloured discs, composed of fifteen blue discs
and six red discs, and two discs were taken at random, it can be seen that the
probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.
The next such arrangement, for which there is exactly 50% chance of taking two
blue discs at random, is a box containing eighty-five blue discs and thirty-five
red discs. By finding the first arrangement to contain over 10^12 = 1,000,000,000,000
discs in total, determine the number of blue discs that the box would contain.*/
long long int q100() {

	/*long long int total_discs = 10;

	bool finished = false;
	while (!finished) {
		if (total_discs % 10000000 == 0) { std::cout << total_discs << std::endl; }

		// long long int range not large enough!
		// The product of two consecutive numbers is even, hence dividing by 2 is exact 
		long long int half_prob_denominator = (total_discs * (total_discs - 1)) / 2;

		long long int blue = (long long int)sqrt(half_prob_denominator);

		while (true) {
			long long int prob_numerator = blue * (blue - 1);

			if (prob_numerator == half_prob_denominator) {
				// 21 15
				// 120 85
				// 697 493
				// 4060 2871
				// 23661 16731
				// 137904 97513
				// 803761 568345
				// 4684660 3312555
				// 27304197 19306983
				// 159140520 112529341

				// Blue: 15, 85, 493, 2871, 16731, 97513, 568345, 3312555, 19306983, 112529341
				// From the above we can derive the following recurrence relationship:
				// https://oeis.org/A011900
				// a(n) = 6*a(n-1) - a(n-2) - 2 with a(0) = 1, a(1) = 3.
				std::cout << total_discs << " " << blue << std::endl;
				// finished = true;
				break;
			}
			else if (prob_numerator > half_prob_denominator) {
				break;
			}
			++blue;
		}
		if (finished) {
			break;
		}

		++total_discs;
	}*/

	long long int a = 1, b = 3, c = 0;

	while (c < 1000000000000) {
		c = (6 * b) - a - 2;

		/*1 3 15
		3 15 85
		15 85 493
		85 493 2871
		493 2871 16731
		2871 16731 97513
		16731 97513 568345
		97513 568345 3312555
		568345 3312555 19306983
		3312555 19306983 112529341
		19306983 112529341 655869061
		112529341 655869061 3822685023
		655869061 3822685023 22280241075
		3822685023 22280241075 129858761425
		22280241075 129858761425 756872327473
		129858761425 756872327473 4411375203411*/
		// std::cout << a << " " << b << " " << c << std::endl;

		a = b;
		b = c;
	}

	// a will house the old b which is the previous term
	return a; // 
}