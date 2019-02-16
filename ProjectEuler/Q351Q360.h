#include <iostream>
#include <vector>

// #include "base_helper.h"
// #include "string_int.h"
#include "factors_helper.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

// NB. Pass param divisor by value
bool recursive_check_divisors_prime(const std::map<int, unsigned int>::const_iterator &it,
	const std::map<int, unsigned int>::const_iterator &it_end, const int &n, int divisor) {
	if (it == it_end) {
		if (prime_helper::is_prime((divisor)+n / divisor)) {
			return true;
		}
		return false;
	}

	int prime_prod = 1;
	for (unsigned int i = 0; i <= it->second; ++i) {
		if (i != 0) {
			prime_prod *= it->first;
		}

		divisor *= prime_prod;

		std::map<int, unsigned int>::const_iterator next_it = it;
		++next_it;
		if (!recursive_check_divisors_prime(next_it, it_end, n, divisor)) {
			return false;
		}

		divisor /= prime_prod;
	}

	return true;
}

/*Consider the divisors of 30: 1,2,3,5,6,10,15,30.
It can be seen that for every divisor d of 30, d + (30 / d) is prime.

Find the sum of all positive integers n not exceeding 100,000,000
such that for every divisor d of n, d + (n / d) is prime.*/
long long int q357() {

	const int limit = 100000000;
	long long int sum = 1; // Include n=1

	// Clearly if n is odd, then with d = 1, d + (n / d) is even which is non-prime
	// unless it is 2. However, it can only be 2 when n = 1. Therefore, we can increment
	// n by 2 skipping all the odd numbers.

	// Furthermore, if n (which is even) has a factor of 2^2 = 4 in it, then with d = 2,
	// d + (n / d) is even + even which is even and non-prime. Therefore, we can increment
	// n by 4 skipping all the n values divisible by 4.

	for (int n = 2; n < limit; n += 4) {
		// if (n % 1000000 == 2) { std::cout << n << " " << sum << std::endl; }

		auto factors = factors_helper::factorise(n);

		if (recursive_check_divisors_prime(factors.begin(), factors.end(), n, 1)) {
			sum += n;

			// Found 2 3
			// Found 6 9
			// Found 10 19
			// Found 22 41
			// Found 30 71
			// Found 42 113
			// Found 58 171
			// Found 70 241
			// std::cout << "Found " << n << " " << sum << std::endl;
		}
	}

	return sum; // 1739023853137
}
