#include <iostream>
#include <vector>
#include <map>

//#include "base_helper.h"
//#include "ifstream_with_path.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


/*A composite is a number containing at least two prime factors.
For example, 15 = 3 × 5; 9 = 3 × 3; 12 = 2 × 2 × 3. There are ten
composites below thirty containing precisely two, not necessarily
distinct, prime factors: 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.
How many composite integers, n < 10^8, have precisely two, not
necessarily distinct, prime factors?*/
int q187() {

	const int limit = 100000000;

	std::vector<int> primes;
	primes.reserve(limit / 10);
	primes.push_back(2);
	primes.push_back(3);

	// All primes greater than 3 can be written in the form 6k +/- 1.
	// Smallest prime is 2 so largest other prime factor of n is (limit / 2).
	// +1 as we actually test prime_helper::is_prime(n - 1).
	const int max = (limit / 2) + 1;
	for (int n = 6; n <= max; n += 6) {
		// if (n % 999996 == 0) { std::cout << n << std::endl; }

		if (prime_helper::is_prime(n - 1)) {
			primes.push_back(n - 1);
		}
		if (prime_helper::is_prime(n + 1)) {
			primes.push_back(n + 1);
		}
	}

	int count = 0;
	for (std::vector<int>::const_iterator it_i = primes.begin(); it_i != primes.end(); ++it_i) {
		for (std::vector<int>::const_iterator it_j = it_i; it_j != primes.end(); ++it_j) {
			// Multiplication needs long long int
			if ((long long int)(*it_i) * (long long int)(*it_j) > (long long int)limit) {
				break;
			}
			++count;
		}
	}
	
	return count; // 17427258
}

