#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstddef> // size_t

#include "base_helper.h"
// #include "string_int.h"
// #include "ifstream_with_path.h"
// #include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


void recursive_selection_162(size_t &count, std::vector<int> &selection,
	const int &index, const int &digits_remaining) {

	// If we have selected all digits, determine how many different
	// numbers can be made with the given selection
	if (!digits_remaining) {

		static const auto fact = factorial_helper::factorials(16LL); // 0!, 1!, ..., 16!

		// Ways to arrange 16 digits
		long long int ways = fact[16];

		// Deal with all the non zero digits being on the right
		// hand side. I.e. when all the zeros are leading zeros
		// and hence our number is invalid as it doesn't include
		// a zero. Arrange all the non zero digits
		long long int invalid = fact[16 - selection[0]];

		// Account for repeated digits
		for (size_t i = 0; i < selection.size(); ++i) {
			ways /= fact[selection[i]];

			if (i) {
				invalid /= fact[selection[i]];
			}
		}

		count += (ways - invalid);

		return;
	}

	// Decide how many times digit "index" occurs
	const int start = index ? 0 : digits_remaining;
	for (int i = start; i <= digits_remaining; ++i) {
		selection[index] += i;
		recursive_selection_162(count, selection, (index - 1), (digits_remaining - i));
		selection[index] -= i;
	}
}

/* In the hexadecimal number system numbers are represented using 16 different digits:
0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
The hexadecimal number AF when written in the decimal number system equals 10x16+15=175.

In the 3-digit hexadecimal numbers 10A, 1A0, A10, and A01 the digits 0, 1 and A are all present.
Like numbers written in base ten we write hexadecimal numbers without leading zeroes.

How many hexadecimal numbers containing at most sixteen hexadecimal digits exist with
all of the digits 0, 1, and A present at least once? Give your answer as a hexadecimal number.
(A,B,C,D,E and F in upper case, without any leading or trailing code that marks the number
as hexadecimal and without leading zeroes , e.g. 1A3F and not: 1a3f and not 0x1a3f and not
$1A3F and not #1A3F and not 0000001A3F) */
std::string q162() {
	size_t count = 0;
	int digits_required = 16;

	std::vector<int> selection(16, 0); // 0, 1, ..., 9, A, B, C, D, E, F
	selection[0] = selection[1] = selection[10] = 1;

	recursive_selection_162(count, selection, (int)(selection.size() - 1), (digits_required - 3));

	// 4'420'408'745'587'516'162
	// -> 3D58725572C62302
	return base_helper::convert_decimal_to_hexadecimal(count);
}


/* How many 20 digit numbers n (without any leading zero) exist such
that no three consecutive digits of n have a sum greater than 9? */
long long int q164() {

	return 1;
}


/* A 4x4 grid is filled with digits d, 0 <= d <= 9.
It can be seen that in the grid

6 3 3 0
5 0 4 3
0 7 1 4
1 2 4 5

the sum of each row and each column has the value 12.
Moreover the sum of each diagonal is also 12.

In how many ways can you fill a 4x4 grid with the digits d,
0 <= d <= 9 so that each row, each column, and both
diagonals have the same sum? */
int q166() {
	// Outer vector - index represents 4 digit sum
	// (ranging from SUM(0000) = 0 to SUM(9999) = 36).
	// Middle vector - index represents 1st digit of 4
	// digit number where we permit leading zeros.
	// Set - all 4 digits numbers with the given digit
	// sum and 1st digit.
	// Inner vector - 4 digit number stored as vector.
	std::vector<std::set<std::vector<int> > > element(10);
	std::vector<std::vector<std::set<std::vector<int> > > > out_v(37, element);

	for (int n = 0; n < 10000; ++n) {
		std::vector<int> current(4, 0);
		int m = n, index = 0, digit_sum = 0;
		while (m) {
			int digit = m % 10;
			digit_sum += digit;
			current[index++] = digit;
			m /= 10;
		}

		out_v[digit_sum][current.back()].insert(current);
	}

	int count = 0;
	for (int i = 0; i < (int)out_v.size(); ++i) {
		/*
		Sum = 0, count = 0
		Sum = 1, count = 1
		Sum = 2, count = 9
		Sum = 3, count = 57
		Sum = 4, count = 257
		Sum = 5, count = 932
		... ...
		Sum = 32, count = 7129102
		Sum = 33, count = 7129777
		Sum = 34, count = 7129977
		Sum = 35, count = 7130025
		Sum = 36, count = 7130033
		*/
		std::cout << "Sum = " << i << ", count = " << count << std::endl;

		const auto mid_v = out_v[i];
		for (const auto &set : mid_v) {

			// Select the top row
			for (const auto &r1 : set) {
				// Select the 1st column
				for (const auto &c1 : mid_v[r1[3]]) {

					// Select the 2nd column
					for (const auto &c2 : mid_v[r1[2]]) {
						int row2check = c1[2] + c2[2];
						int row3check = c1[1] + c2[1];
						int row4check = c1[0] + c2[0];
						int diagtopleft = c1[3] + c2[2];
						int diagtopright = c1[0] + c2[1];
						if (row2check > i || row2check < (i - 18) ||
							row3check > i || row3check < (i - 18) ||
							row4check > i || row4check < (i - 18) ||
							diagtopleft > i || diagtopleft < (i - 18) ||
							diagtopright > i || diagtopright < (i - 18)) {
							continue;
						}

						// Select the 3rd column
						for (const auto &c3 : mid_v[r1[1]]) {
							row2check = c1[2] + c2[2] + c3[2];
							row3check = c1[1] + c2[1] + c3[1];
							row4check = c1[0] + c2[0] + c3[0];
							diagtopleft = c1[3] + c2[2] + c3[1];
							diagtopright = c1[0] + c2[1] + c3[2];
							if (row2check > i || row2check < (i - 9) ||
								row3check > i || row3check < (i - 9) ||
								row4check > i || row4check < (i - 9) ||
								diagtopleft > i || diagtopleft < (i - 9) ||
								diagtopright > i || diagtopright < (i - 9)) {
								continue;
							}

							// Instead of selecting the 4th column, formulate the values
							// by taking sum along each row. Always possible to generate
							// values between 0 and 9 due to ealier sum checks.
							int c4_3 = r1[0];
							int c4_2 = i - row2check;
							int c4_1 = i - row3check;
							int c4_0 = i - row4check;

							// Perform checks
							if ((c4_3 + c4_2 + c4_1 + c4_0) == i && // 4th column
								(diagtopleft + c4_0) == i && // Diagonal top left
								(diagtopright + c4_3) == i) { // Diagonal top right

								++count;
							}

						} // Select the 3rd column
					} // Select the 2nd column
				} // Select the 1st column
			} // Select the top row

		}
	}

	return count; // 7130034
}
