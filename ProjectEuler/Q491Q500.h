#include <iostream>
#include <vector>
#include <map>

#include "factors_helper.h"
#include "vector_int.h"
// #include "ifstream_with_path.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*The number of divisors of 120 is 16.
In fact 120 is the smallest number having 16 divisors.

Find the smallest number with 2^500500 divisors.
Give your answer modulo 500500507.*/
/*long long int q500() {
	// WHAT FOLLOWS BELOW FINDS N WITH 500500 FACTORS.
	// NOT N WITH 2^500500 FACTORS.

	// std::map<int, unsigned int> factors;
	// prime_helper::factorise(500500, factors);

	// 500500 = 2^2 x 5^3 x 7 x 11 x 13 = 4 x 125 x 7 x 11 x 13

	// So required powers in prime factorisation will be:
	// 12, 10, 6, ((4, 4, 4) or (4, 24), or (124)), ((1, 1) or (3))

	// Giving six possible power combinations:
	// a. 12, 10, 6, (4, 4, 4), (1, 1) = 12, 10, 6, 4, 4, 4, 1, 1
	// b. 12, 10, 6, (4, 4, 4), (3)    = 12, 10, 6, 4, 4, 4, 3
	// c. 12, 10, 6, (4, 24), (1, 1)   = 24, 12, 10, 6, 4, 1, 1
	// d. 12, 10, 6, (4, 24), (3)      = 24, 12, 10, 6, 4, 3
	// e. 12, 10, 6, (124), (1, 1)     = 124, 12, 10, 6, 1, 1
	// f. 12, 10, 6, (124), (3)        = 124, 12, 10, 6, 3

	// We can exclude options e and f since the 124 power is smaller if split,
	// i.e. even for the smallest prime 2, 2^124 = 2.12 x 10^37.

	// First 8 primes are: 2, 3, 5, 7, 11, 13, 17, 19.

	std::vector<int> primes;
	primes.push_back(2);
	int n = 3;
	while (primes.size() < 8) {
		if (prime_helper::is_prime(n)) {
			primes.push_back(n);
		}
		n += 2;
	}

	// The difference between a and b is a's 17 * 19 = 323 vs b's 17^3 = 4913.
	// Clearly a is smaller than b then.

	// The difference between c and d is c's 13 * 17 = 221 vs d's 13^3 = 2197.
	// Clearly c is smaller than d then.

	vector_int a(1);
	a *= 4096; // 2^12
	a *= 59049; // 3^10
	a *= 15625; // 5^6
	a *= 2401; // 7^4
	a *= 14641; // 11^4
	a *= 28561; // 13^4
	a *= 17;
	a *= 19;

	vector_int c(1);
	c *= 16777216; // 2^24
	c *= 531441; // 3^12
	c *= 9765625; // 5^10
	c *= 117649; // 7^6
	c *= 14641; // 11^4
	c *= 13;
	c *= 17;

	if (a < c) {
		std::cout << "a < c" << std::endl;
	}

	long long int res = 1;
	res *= 4096; // 2^12 
	res %= 500500507;
	res *= 59049; // 3^10
	res %= 500500507;
	res *= 15625; // 5^6
	res %= 500500507;
	res *= 2401; // 7^4
	res %= 500500507;
	res *= 14641; // 11^4
	res %= 500500507;
	res *= 28561; // 13^4
	res %= 500500507;
	res *= 17;
	res %= 500500507;
	res *= 19;
	res %= 500500507;

	// 500500507 = 13 x 38500039
	const int mod = 500500507;

	std::map<int, unsigned int> factors;
	factors_helper::factorise(500500, factors);

	return 1;
}*/
