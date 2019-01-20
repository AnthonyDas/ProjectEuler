#include <iostream>
#include <vector>
#include <algorithm> // std::min
#include <stdlib.h> // abs 
#include <utility> // std::make_pair
#include <queue>

#include "ifstream_with_path.h"
#include "roman_numeral_helper.h"
#include "monopoly_board.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*In the 5 by 5 matrix below, the minimal path sum from the top left
to the bottom right, by only moving to the right and down, is indicated
in bold red and is equal to 2427.

131 673 234 103 18
201 96 342 965 150
630 803 746 422 111
537 699 497 121 956
805 732 524 37 331

Find the minimal path sum, in matrix.txt (right click and "Save Link/Target As..."),
a 31K text file containing a 80 by 80 matrix, from the top left to the bottom
right by only moving right and down.*/
int q81() {
	const int max_width = 80;
	std::vector<int> row(max_width, 0);
	std::vector<std::vector<int> > matrix(max_width, row);

	ifstream_with_path fin("Problem81.txt");
	for (int i = 0; i < max_width; ++i) {
		for (int j = 0; j < max_width; ++j) {
			fin >> matrix[i][j];
		}
	}
	fin.close();

	// Work our way along each row (left to right) starting at top row and ending up at bottom row.

	// Let index i denote row and index j denote column
	for (int i = 0; i < max_width; ++i) {
		for (int j = 0; j < max_width; ++j) {
			if (i == 0 && j == 0) {
				continue; // Nothing to do for (starting) top left cell
			}

			if (j == 0) {
				// In first column - can only come from above 
				matrix[i][j] += matrix[i - 1][j];
			}
			else if (i == 0) {
				// In top row - can only come from left 
				matrix[i][j] += matrix[i][j - 1];
			}
			else {
				// Take the min between above and left
				matrix[i][j] += std::min(matrix[i - 1][j], matrix[i][j - 1]);
			}
		}
	}

	/*for (int i = 0; i < max_width; ++i) {
		for (int j = 0; j < max_width; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}*/

	return matrix.back().back();
}

/*The minimal path sum in the 5 by 5 matrix below, by starting in any cell in the left
column and finishing in any cell in the right column, and only moving up, down, and right,
is indicated in red and bold; the sum is equal to 994.

Find the minimal path sum, in matrix.txt (right click and "Save Link/Target As..."),
a 31K text file containing a 80 by 80 matrix, from the left column to the right column.*/
int q82() {

	const int max_width = 80;
	std::vector<int> row(max_width, 0);
	std::vector<std::vector<int> > matrix(max_width, row);

	ifstream_with_path fin("Problem82.txt");
	for (int i = 0; i < max_width; ++i) {
		for (int j = 0; j < max_width; ++j) {
			fin >> matrix[i][j];
		}
	}
	fin.close();

	// Work on a column at a time starting on the left and moving to the right

	for (int j = 1; j < max_width; ++j) { // Start on second column

		// Save the calculated min paths. Don't write to the main grid
		// until whole column has been calculated as otherwise will
		// affect the results for subsequent cells.
		std::vector<int> col_up(max_width, 0), col_down(max_width, 0);

		// Work down the column finding the minimum path from the left or from above
		for (int i = 0; i < max_width; ++i) {
			if (i == 0) {
				// From left only
				col_up[i] = matrix[i][j] + matrix[i][j - 1];
			}
			else {
				// From left or from above
				// - note that we use the already computed minimum value for from above within col
				col_up[i] = matrix[i][j] + std::min(matrix[i][j - 1], col_up[i - 1]);
			}
		}

		// Work up the column finding the minimum path from the left or from below
		for (int i = (max_width - 1); i >= 0; --i) {
			if (i == (max_width - 1)) {
				// From left only
				col_down[i] = matrix[i][j] + matrix[i][j - 1];
			}
			else {
				// From left or from below
				// - note that we use the already computed minimum value for from below within col
				col_down[i] = matrix[i][j] + std::min(matrix[i][j - 1], col_down[i + 1]);
			}
		}

		// Now write the calculated minimum column back into the main grid
		for (int i = 0; i < max_width; ++i) {
			matrix[i][j] = std::min(col_up[i], col_down[i]);
		}
	}

	// Find the overall min path
	int final_min_path = INT_MAX;
	for (int i = 0; i < max_width; ++i) {
		if (matrix[i][max_width - 1] < final_min_path) {
			final_min_path = matrix[i][max_width - 1];
		}
	}

	return final_min_path; // 260324
}


/* In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right,
by moving left, right, up, and down, is indicated in bold red and is equal to 2297.

Find the minimal path sum, in matrix.txt, a 31K text file containing a 80 by 80 matrix,
from the top left to the bottom right by moving left, right, up, and down. */
int q83() {

	const int max_width = 80;
	std::vector<int> row(max_width, 0);
	std::vector<std::vector<int> > matrix(max_width, row);

	ifstream_with_path fin("Problem83.txt");
	for (int i = 0; i < max_width; ++i) {
		for (int j = 0; j < max_width; ++j) {
			fin >> matrix[i][j];
		}
	}
	fin.close();

	std::vector<int> row2(max_width, INT32_MAX);
	std::vector<std::vector<int> > min_path(max_width, row2);

	// row, col, path sum
	std::queue<std::tuple<int, int, int> > q({ std::make_tuple(0, 0, matrix[0][0]) });

	while (!q.empty()) {
		auto current = q.front();
		q.pop();

		const int i = std::get<0>(current); // row
		const int j = std::get<1>(current); // col
		const int path_sum = std::get<2>(current);

		if (path_sum < min_path[i][j]) {
			min_path[i][j] = path_sum;

			// Decide whether we can move north, south, east and west
			if (i - 1 >= 0) {
				q.push(std::make_tuple(i - 1, j, path_sum + matrix[i - 1][j]));
			}
			if (i + 1 < max_width) {
				q.push(std::make_tuple(i + 1, j, path_sum + matrix[i + 1][j]));
			}
			if (j - 1 >= 0) {
				q.push(std::make_tuple(i, j - 1, path_sum + matrix[i][j - 1]));
			}
			if (j + 1 < max_width) {
				q.push(std::make_tuple(i, j + 1, path_sum + matrix[i][j + 1]));
			}
		}
	}

	return min_path[max_width - 1][max_width - 1]; // 425185
}


/* In the game, Monopoly, the standard board is set up in the following way:

GO	A1	CC1	A2	T1	R1	B1	CH1	B2	B3	JAIL
H2	 	C1
T2	 	U1
H1	 	C2
CH3	 	C3
R4	 	R2
G3	 	D1
CC3	 	CC2
G2	 	D2
G1	 	D3
G2J	F3	U2	F2	F1	R3	E3	E2	CH2	E1	FP

A player starts on the GO square and adds the scores on two 6-sided dice to determine the
number of squares they advance in a clockwise direction. Without any further rules we would
expect to visit each square with equal probability: 2.5%. However, landing on G2J (Go To Jail),
CC (community chest), and CH (chance) changes this distribution.

In addition to G2J, and one card from each of CC and CH, that orders the player to go directly
to jail, if a player rolls three consecutive doubles, they do not advance the result of their
3rd roll. Instead they proceed directly to jail.

At the beginning of the game, the CC and CH cards are shuffled. When a player lands on CC or CH
they take a card from the top of the respective pile and, after following the instructions, it
is returned to the bottom of the pile. There are sixteen cards in each pile, but for the purpose
of this problem we are only concerned with cards that order a movement; any instruction not 
concerned with movement will be ignored and the player will remain on the CC/CH square.

Community Chest (2/16 cards):
Advance to GO
Go to JAIL

Chance (10/16 cards):
Advance to GO
Go to JAIL
Go to C1
Go to E3
Go to H2
Go to R1
Go to next R (railway company)
Go to next R
Go to next U (utility company)
Go back 3 squares.

The heart of this problem concerns the likelihood of visiting a particular square. That is, the
probability of finishing at that square after a roll. For this reason it should be clear that,
with the exception of G2J for which the probability of finishing on it is zero, the CH squares
will have the lowest probabilities, as 5/8 request a movement to another square, and it is the
final square that the player finishes at on each roll that we are interested in. We shall make
no distinction between "Just Visiting" and being sent to JAIL, and we shall also ignore the rule
about requiring a double to "get out of jail", assuming that they pay to get out on their next turn.

By starting at GO and numbering the squares sequentially from 00 to 39 we can concatenate these
two-digit numbers to produce strings that correspond with sets of squares.

Statistically it can be shown that the three most popular squares, in order, are
JAIL (6.24%) = Square 10, E3 (3.18%) = Square 24, and GO (3.09%) = Square 00.
So these three most popular squares can be listed with the six-digit modal string: 102400.

If, instead of using two 6-sided dice, two 4-sided dice are used, find the six-digit modal string.*/
std::string q84() {

	monopoly_board board(4, 100, false); // dice sides, max iterations, logging

	return board.modal_string();
}


/*By counting carefully it can be seen that a rectangular grid measuring 3 by 2
contains eighteen rectangles:

Although there exists no rectangular grid that contains exactly two million rectangles,
find the area of the grid with the nearest solution.*/
int q85() {
	const int target = 2000000;

	int	diff = INT_MAX, nearest_x = 0, nearest_y = 0;

	bool finished = false;
	// Dimensions of the grid
	for (int grid_x = 1; !finished; ++grid_x) {
		for (int grid_y = 1; grid_y <= grid_x; ++grid_y) { // grid_y <= grid_x to prevent duplicate processing

			// int count = 0;

			// Size of the rectangle
			/*for (int x = 1; x <= grid_x; ++x) {
				for (int y = 1; y <= grid_y; ++y) {
					// Count of possible rectangle positions equivalent
					// to count of rectangles
					count += (grid_x - x + 1) * (grid_y - y + 1);
				}
			}*/

			// The above nested loops make intuitive sense but observe for a 5x5 grid we count:
			// (5.5) + (5.4) + (5.3) + (5.2) + (5.1) +
			// (4.5) + (4.4) + (4.3) + (4.2) + (4.1) +
			// ... +
			// (1.5) + (1.4) + (1.3) + (1.2) + (1.1)
			// = (5 + 4 + ... + 1) . SUM(5,...,1)
			// = SUM(5,...,1) . SUM(5,...,1)

			// Using formula for arithmetic sequence
			int count = (((grid_x + 1) * grid_x) / 2) * (((grid_y + 1) * grid_y) / 2);

			if (abs(count - target) < diff) {
				// std::cout << abs(count - target) << " " << grid_x << " " << grid_y << std::endl;

				diff = abs(count - target);
				nearest_x = grid_x;
				nearest_y = grid_y;
			}

			// If count > target then no need to go onto the next value of y 
			// because the count will just be even bigger. Further, if we have
			// grid_y == 1 then grid_x is already too large and we are finished.
			if (count > target) {
				if (grid_y == 1) {
					finished = true;
				}
				break;
			}
		}
	}

	return nearest_x * nearest_y; // 2772
}


/*A spider, S, sits in one corner of a cuboid room, measuring 6 by 5 by 3, and a fly,
F, sits in the opposite corner. By travelling on the surfaces of the room the shortest
"straight line" distance from S to F is 10 and the path is shown on the diagram.
However, there are up to three "shortest" path candidates for any given cuboid and
the shortest route doesn't always have integer length.
It can be shown that there are exactly 2060 distinct cuboids, ignoring rotations,
with integer dimensions, up to a maximum size of M by M by M, for which the shortest
route has integer length when M = 100. This is the least value of M for which the number
of solutions first exceeds two thousand; the number of solutions when M = 99 is 1975.
Find the least value of M such that the number of solutions first exceeds one million.*/
int q86() {
	// Note that is we lay the walls of the cuboid flat onto the same plane,
	// then the shortest distance between S and F is just the hypotenuse of a
	// right angle triangle which can be calculated using Pythagoras' Theorem.
	// Further, if we want the shortest distance, then we should add the two
	// shortest sides of the cuboid together to form one side of our
	// right angle triangle leaving the longest cuboid side forming another
	// side of the triangle.

	const int target = 1000000;

	int a, count = 0;

	for (a = 1; true; ++a) { // Longest cuboid side
		for (int b = 2; b <= 2 * a; ++b) { // Combined length of two shortest cuboid sides
			int c_sqrd = (a * a) + (b * b);

			// Need c_sqrd to be a perfect square to have integer length
			int c = (int)sqrt(c_sqrd);
			if (c * c == c_sqrd) {
				// std::cout << a << " " << b << " " << c << std::endl;

				// Now we need to break down b into two separate cuboid sides
				// whilst bearing in mind that neither side should exceed a.
				// The longest length one of these sides can be is (b - 1).

				if ((b - 1) > a) {
					// Just considering the longer side the options are:
					// For b even: a, (a - 1), ...., (b / 2). This is a - (b / 2) + 1 options.
					// For b odd: a, (a - 1), ...., ((b + 1) / 2). This is a - ((b + 1) / 2) + 1 options.
					if (b % 2 == 0) {
						count += a + 1 - (b / 2);
					}
					else {
						count += a + 1 - ((b + 1) / 2);
					}
				}
				else {
					// We can ignore a. Just considering the longer side the options are:
					// For b even: (b - 1), (b - 2), ...., (b / 2). This is (b - 1) - (b / 2) + 1 = (b / 2) options.
					// For b odd: (b - 1), (b - 2), ...., ((b + 1) / 2). (b - 1) - ((b + 1) / 2) + 1 = ((b - 1) / 2) options.
					if (b % 2 == 0) {
						count += b / 2;
					}
					else {
						count += (b - 1) / 2;
					}
				}

			}
		}

		// std::cout << a << " " << count << std::endl;

		if (count > target) {
			break;
		}
	}

	return a; // 1818
}


/*The smallest number expressible as the sum of a prime square, prime cube, and
prime fourth power is 28. In fact, there are exactly four numbers below fifty
that can be expressed in such a way:
28 = 2^2 + 2^3 + 2^4
33 = 3^2 + 2^3 + 2^4
49 = 5^2 + 2^3 + 2^4
47 = 2^2 + 3^3 + 2^4
How many numbers below fifty million can be expressed as the sum of a prime
square, prime cube, and prime fourth power?*/
int q87() {
	const int limit = 50000000;

	std::vector<int> primes_sqr, primes_cub, primes_fth;
	primes_sqr.push_back(4);
	primes_cub.push_back(8);
	primes_fth.push_back(16);

	const int upper = (int)sqrt(limit - 8.0 - 16.0);
	for (int i = 3; i <= upper; i += 2) {
		if (prime_helper::is_prime(i)) {
			const int sqr = i * i;
			primes_sqr.push_back(sqr);

			// Need sqr to be long long so RHS is calc correctly
			const long long int cub = (long long int)sqr * i;
			if (cub > limit - 4 - 16) {
				continue;
			}
			primes_cub.push_back((int)cub);

			const long long int fth = cub * i;
			if (fth > limit - 4 - 8) {
				continue;
			}
			primes_fth.push_back((int)fth);
		}
	}

	std::set<int> numbers;
	for (std::vector<int>::const_iterator it_i = primes_sqr.begin(); it_i != primes_sqr.end(); ++it_i) {
		int trial = *it_i;
		for (std::vector<int>::const_iterator it_j = primes_cub.begin(); it_j != primes_cub.end(); ++it_j) {
			trial += *it_j;
			if (trial >= limit) {
				trial -= *it_j;
				break;
			}
			for (std::vector<int>::const_iterator it_k = primes_fth.begin(); it_k != primes_fth.end(); ++it_k) {
				trial += *it_k;
				if (trial > limit) {
					trial -= *it_k;
					break;
				}
				numbers.insert(trial);
				/*if (numbers.size() % 10000 == 0) {
					std::cout << numbers.size() << " " << trial << " " << *it_i << " " << *it_j << " " << *it_k << std::endl;
				}*/
				trial -= *it_k;
			}
			trial -= *it_j;
		}
		trial -= *it_i;
	}

	return (int)numbers.size(); // 1097343
}


/*For a number written in Roman numerals to be considered valid there are basic rules
which must be followed. Even though the rules allow some numbers to be expressed in
more than one way there is always a "best" way of writing a particular number.
For example, it would appear that there are at least six ways of writing the number sixteen:
IIIIIIIIIIIIIIII
VIIIIIIIIIII
VVIIIIII
XIIIIII
VVVI
XVI
However, according to the rules only XIIIIII and XVI are valid, and the last example
is considered to be the most efficient, as it uses the least number of numerals.
The 11K text file, roman.txt (right click and 'Save Link/Target As...'), contains
one thousand numbers written in valid, but not necessarily minimal, Roman numerals;
see About... Roman Numerals for the definitive rules for this problem.
Find the number of characters saved by writing each of these in their minimal form.
Note: You can assume that all the Roman numerals in the file contain no more than four
consecutive identical units.*/
int q89() {

	size_t start_char_count = 0;
	std::vector<int> roman_nums;

	ifstream_with_path fin("Problem89.txt");
	for (int i = 0; i < 1000; ++i) {
		std::string roman_str;
		fin >> roman_str;

		start_char_count += roman_str.size();

		int roman_int;
		roman_numeral_helper::convert_to_int(roman_str, roman_int);
		roman_nums.push_back(roman_int);
	}
	fin.close();

	size_t end_char_count = 0;

	for (std::vector<int> ::const_iterator it = roman_nums.begin(); it != roman_nums.end(); ++it) {
		std::string roman_str;
		roman_numeral_helper::convert_to_str(*it, roman_str);

		end_char_count += roman_str.size();
	}


	return (int)(start_char_count - end_char_count); // 743
}