#include <iostream>
#include <vector>

// #include "base_helper.h"
// #include "ifstream_with_path.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*If we calculate a^2 mod 6 for 0 <= a <= 5 we get: 0,1,4,3,4,1.
The largest value of a such that a^2 = a mod 6 is 4.
Let's call M(n) the largest value of a < n such that a^2 = a (mod n).
So M(6) = 4. Find SUM(M(n)) for 1 <= n <= 10^7.*/
long long int q407() {
	
	const int limit = 10000000;
	
	long long int sum = 0;

	for (int n = 1; n <= limit; ++n) {
		if (n % 100000 == 0) { std::cout << n << " " << sum << std::endl; }

		// If n is prime then a = 1
		if (prime_helper::is_prime(n)) {
			sum += 1;

			std::cout << n << " " << 1 << std::endl;
			continue;
		}


		for (int a = n - 1; a >= 0; --a) {
			if ((a * a) % n == a) {
				sum += a;

				std::cout << n << " " << a << std::endl;
				break;
			}
		}
	}

	return sum;
}
