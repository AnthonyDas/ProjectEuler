#include <iostream>
#include <vector>
#include <algorithm> // std::sort()

#include "palindrome_helper.h"
#include "factors_helper.h"
#include "greatest_common_divisor_helper.h"
//#include "ifstream_with_path.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*A bag contains one red disc and one blue disc. In a game of chance a
player takes a disc at random and its colour is noted. After each turn
the disc is returned to the bag, an extra red disc is added, and another
disc is taken at random. The player pays £1 to play and wins if they have
taken more blue discs than red discs at the end of the game.
If the game is played for four turns, the probability of a player winning
is exactly 11/120, and so the maximum prize fund the banker should allocate
for winning in this game would be £10 before they would expect to incur a
loss. Note that any payout will be a whole number of pounds and also includes
the original £1 paid to play the game, so in the example given the player
actually wins £9. Find the maximum prize fund that should be allocated to
a single game in which fifteen turns are played.*/
int q121() {


	return 1;
}


/*The most naive way of computing n^15 requires fourteen multiplications:
n × n × ... × n = n15
But using a "binary" method you can compute it in six multiplications:
n × n = n^2
n^2 × n^2 = n^4
n^4 × n^4 = n^8
n^8 × n^4 = n^12
n^12 × n^2 = n^14
n^14 × n = n^15
However it is yet possible to compute it in only five multiplications:
n × n = n^2
n^2 × n = n^3
n^3 × n^3 = n^6
n^6 × n^6 = n^12
n^12 × n^3 = n^15
We shall define m(k) to be the minimum number of multiplications to compute
n^k; for example m(15) = 5. For 1 <= k <= 200, find SUM{m(k)}.*/
int q122() {


	return 1;
}


bool n_radn_comparator(const std::pair<int, int> &n_radn1, const std::pair<int, int> &n_radn2) {
	// Can we determine ordering based on radn?
	if (n_radn1.second != n_radn2.second) {
		return n_radn1.second < n_radn2.second;
	}

	// Otherwise, determine ordering on n.
	return n_radn1.first < n_radn2.first;
}

/*The radical of n, rad(n), is the product of the distinct prime
factors of n. For example, 504 = 2^3 × 3^2 × 7, so rad(504) = 2 × 3 × 7 = 42.
If we calculate rad(n) for 1 <= n <= 10, then sort them on rad(n),
and sorting on n if the radical values are equal, we get:

Let E(k) be the kth element in the sorted n column; for example,
E(4) = 8 and E(6) = 9. If rad(n) is sorted for 1 <= n <= 100000, find E(10000).*/
int q124() {

	std::vector<std::pair<int, int> > n_radn;

	for (int n = 1; n <= 100000; ++n) {

		n_radn.push_back(std::pair<int, int>(n, factors_helper::rad(n)));

		// std::cout << n << " " << radn << std::endl;
	}

	std::sort(n_radn.begin(), n_radn.end(), n_radn_comparator);

	/*for (std::vector<std::pair<int, int> >::const_iterator it = n_radn.begin(); it != n_radn.end(); ++it) {
		std::cout << it->first << " " << it->second << std::endl;
	}*/

	return n_radn[10000 - 1].first; // 21417
}


/*The palindromic number 595 is interesting because it can be written as
the sum of consecutive squares: 6^2 + 7^2 + 8^2 + 9^2 + 10^2 + 11^2 + 12^2.
There are exactly eleven palindromes below one-thousand that can be written
as consecutive square sums, and the sum of these palindromes is 4164.
Note that 1 = 0^2 + 1^2 has not been included as this problem is concerned
with the squares of positive integers.
Find the sum of all the numbers less than 10^8 that are both palindromic
and can be written as the sum of consecutive squares.*/
long long int q125() {

	const int limit = 100000000;

	std::set<int> palin_consec_sqrs;

	std::vector<int> squares;
	for (int s = 1; s * s < limit; ++s) {
		squares.push_back(s * s);
	}

	for (std::vector<int>::const_reverse_iterator rit_i = squares.rbegin(); rit_i != --squares.rend(); ++rit_i) { // Ends one before rlast
		int consec_sqrs_sum = *rit_i;

		for (std::vector<int>::const_reverse_iterator rit_j = (rit_i + 1); rit_j != squares.rend(); ++rit_j) { // Start one after rit_i
			consec_sqrs_sum += *rit_j;

			if (consec_sqrs_sum > limit) {
				break;
			}

			if (palindrome_helper::is_palindrome(consec_sqrs_sum)) {
				palin_consec_sqrs.insert(consec_sqrs_sum);
			}
		}
	}


	long long int sum_palin = 0;
	for (std::set<int>::const_iterator it = palin_consec_sqrs.begin(); it != palin_consec_sqrs.end(); ++it) {
		sum_palin += *it;
	}

	return sum_palin; // 2906969179
}


/* The radical of n, rad(n), is the product of distinct prime factors of n.
For example, 504 = 23 × 32 × 7, so rad(504) = 2 × 3 × 7 = 42.
We shall define the triplet of positive integers(a, b, c) to be an abc-hit if:

GCD(a, b) = GCD(a, c) = GCD(b, c) = 1
a < b
a + b = c
rad(abc) < c

For example, (5, 27, 32) is an abc-hit, because:
GCD(5, 27) = GCD(5, 32) = GCD(27, 32) = 1
5 < 27
5 + 27 = 32
rad(4320) = 30 < 32

It turns out that abc-hits are quite rare and there are only thirty-one
abc-hits for c < 1000, with SUM(c) = 12523. Find SUM(c) for c < 120000. */
long long int q127() {

	long long int sum = 0;

	for (int c = 3; c < 120000; ++c) {
		if (c % 100 == 0) { std::cout << c << std::endl; }

		for (int a = 1; a <= (c / 2); ++a) {
			int b = c - a;

			if (a >= b) {
				continue;
			}

			if (!greatest_common_divisor_helper::is_coprime(a, b) ||
				!greatest_common_divisor_helper::is_coprime(a, c) ||
				!greatest_common_divisor_helper::is_coprime(b, c)) {
				continue;
			}

			if (factors_helper::rad(a * b * c) >= c) {
				continue;
			}

			sum += c;
			//std::cout << c << " " << b << " " << a << " " << sum << std::endl;
		}
	}

	return sum;
}


/*A number consisting entirely of ones is called a repunit. We shall
define R(k) to be a repunit of length k; for example, R(6) = 111111.
Given that n is a positive integer and GCD(n, 10) = 1, it can be shown
that there always exists a value, k, for which R(k) is divisible by n,
and let A(n) be the least such value of k; for example, A(7) = 6 and A(41) = 5.
The least value of n for which A(n) first exceeds ten is 17.
Find the least value of n for which A(n) first exceeds one-million.*/
int q129() {
	// Consider the case of n = 7:
	// k, R(k) mod 7 [noting that R(k) mod 7 = 10*R(k-1) + 1 mod 7]
	// 1, 1
	// 2, 11 = 4
	// 3, 41 = 6
	// 4, 61 = 5
	// 5, 51 = 9
	// 6, 91 = 0
	// 7, 1

	// We see that the mod 7 column gets to 0 when k = 6. Moreover, when k = 7,
	// we see that the mod 7 value becomse 1 again, i.e. that the chain repeats:
	// 1 -> 4 -> 6 -> 5 -> 9 -> 0 -> 1. We need this chain to be at least 1,000,000
	// in length BEFORE it repeats which means that there must at least be 1,000,000
	// possible mod n values. Therefore, n must be at least 1,000,000. 

	const int target = 1'000'000;

	int n = (target - 1), k = 0;
	while (k <= target) {

		++n;

		// Need GCD(n, 10) = 1
		if (n % 2 == 0 || n % 5 == 0) {
			continue;
		}

		int mod = 1;
		k = 1;
		while (true) {
			++k;

			mod = ((10 * mod) + 1) % n;
			if (mod == 0) {
				break;
			}
		}

		// std::cout << n << " " << k << std::endl;
	}

	return n; // 1000023
}


/*A number consisting entirely of ones is called a repunit. We shall
define R(k) to be a repunit of length k; for example, R(6) = 111111.
Given that n is a positive integer and GCD(n, 10) = 1, it can be shown
that there always exists a value, k, for which R(k) is divisible by n,
and let A(n) be the least such value of k; for example, A(7) = 6 and A(41) = 5.
You are given that for all primes, p > 5, that p - 1 is divisible by A(p).
For example, when p = 41, A(41) = 5, and 40 is divisible by 5.
However, there are rare composite values for which this is also true;
the first five examples being 91, 259, 451, 481, and 703.
Find the sum of the first twenty-five composite values of n for which
GCD(n, 10) = 1 and (n - 1) is divisible by A(n).*/
int q130() {

	int n = 90, k = 0, count = 0, sum = 0;

	while (count < 25) {

		++n;

		// Need GCD(n, 10) = 1 and needs to be composite, (i.e. not prime)
		if (n % 2 == 0 || n % 5 == 0 || prime_helper::is_prime(n)) {
			continue;
		}

		int mod = 1;
		k = 1;
		while (true) {
			++k;

			mod = ((10 * mod) + 1) % n;
			if (mod == 0) {
				break;
			}
		}

		if ((n - 1) % k == 0) {
			sum += n;
			++count;
			// std::cout << count << " " << sum << " " << n << " " << k << std::endl;
		}
	}

	return sum; // 149253
}
