#include <iostream>
#include <vector>
#include <cmath> // pow

#include "dice_helper.h"
#include "factors_helper.h"
#include "combinatorics_helper.h"
// #include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


/*A Hamming number is a positive number which has no prime factor larger than 5.
So the first few Hamming numbers are 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15.
There are 1105 Hamming numbers not exceeding 10^8.
We will call a positive number a generalised Hamming number of type n,
if it has no prime factor larger than n.
Hence the Hamming numbers are the generalised Hamming numbers of type 5.
How many generalised Hamming numbers of type 100 are there which don't exceed 10^9?*/
int q204() {
	const int limit = 1000000000;
	const int type = 100;
	int count = 0;

	factors_helper::generalised_hamming_count(type, limit, count);

	return count; // 2944730
}


/*Peter has nine four-sided (pyramidal) dice, each with faces numbered 1, 2, 3, 4.
Colin has six six-sided (cubic) dice, each with faces numbered 1, 2, 3, 4, 5, 6.
Peter and Colin roll their dice and compare totals: the highest total wins.
The result is a draw if the totals are equal.
What is the probability that Pyramidal Pete beats Cubic Colin? Give your answer
rounded to seven decimal places in the form 0.abcdefg */
double q205() {
	
	std::map<int, int> pyramidal_totals = dice_helper::total_counts(4, 9);
	const double pyramidal_total_occurences = pow(4, 9); // double for prob calc

	std::map<int, int> cube_totals = dice_helper::total_counts(6, 6);
	const double cube_total_occurences = pow(6, 6); // double for prob calc

	double prob = 0.0;
	for (std::map<int, int>::const_iterator it_i = cube_totals.begin(); it_i != cube_totals.end(); ++it_i) {

		int pyramidal_occurences = 0;
		for (std::map<int, int>::const_reverse_iterator rit_j = pyramidal_totals.rbegin(); rit_j != pyramidal_totals.rend(); ++rit_j) {
			if (it_i->first < rit_j->first) {
				pyramidal_occurences += rit_j->second;
			}
			else {
				break;
			}
		}

		prob += (it_i->second / cube_total_occurences) * (pyramidal_occurences / pyramidal_total_occurences);
	}

	return round(prob * 10000000) / 10000000; // 7 d.p.
}


/*Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0,
where each “_” is a single digit.*/
long long int q206() {

	// n, n^2
	// 0, 0
	// 1, 1
	// 2, 4
	// 3, 9
	// 4, 16
	// 5, 25
	// 6, 36
	// 7, 49
	// 8, 64
	// 9, 81

	// Observations on the square:
	// - ends in 0, so original integer ends in 0.
	// - starts with 1, so original integer starts in 1 (1^2 = 1) or 4 (4^2 = 16)
	// - is 19 digits long, so actually it must start in 1 and not 4.
	// - starting integer must be of the form 1 _ _ _ _ _ _ _ _ 0.
	// - second from last digit is 9, so original integer first from last is 3 or 7.

	long long int current = 1000000030;
	while (true) {
		long long int square = current * current;

		if ((square % 1000) / 100 == 9 &&
			(square % 100000) / 10000 == 8 &&
			(square % 10000000) / 1000000 == 7 &&
			(square % 1000000000) / 100000000 == 6 &&
			(square % 100000000000) / 10000000000 == 5 &&
			(square % 10000000000000) / 1000000000000 == 4 &&
			(square % 1000000000000000) / 100000000000000 == 3 &&
			(square % 100000000000000000) / 10000000000000000 == 2) {
			// std::cout << current << " " << square << std::endl;
			break;
		}

		if (current % 100 == 30) {
			current += 40; // To get to ending 70
		}
		else { // (current % 100 == 70)
			current += 60; // To get to ending 30
		}
	}

	return current; // 1389019170 1929374254627488900
}


/* A robot moves in a series of one-fifth circular arcs (72°),
with a free choice of a clockwise or an anticlockwise arc for
each step, but no turning on the spot.

One of 70932 possible closed paths of 25 arcs starting northward is

Given that the robot starts facing North, how many journeys of 70
arcs in length can it take that return it, after the final arc,
to its starting position? (Any arc may be traversed multiple times.) */
int q208() {
	const int arcs = 6;

	int count = 0;

	for (int i = 0; i <= arcs; i += 3) {
		count += combinatorics_helper::combinations(arcs, i);
	}

	return count;
}
