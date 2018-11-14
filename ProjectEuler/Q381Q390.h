#include <iostream>
#include <vector>

#include "harshad_helper.h"
#include "factorial_helper.h"
// #include "ifstream_with_path.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*For a prime p let S(p) = (SUM(p-k)!) mod(p) for 1 = k = 5.
For example, if p = 7,
(7-1)! + (7-2)! + (7-3)! + (7-4)! + (7-5)! = 6! + 5! + 4! + 3! + 2!
= 720 + 120 + 24 + 6 + 2 = 872. As 872 mod(7) = 4, S(7) = 4.
It can be verified that SUM(S(p)) = 480 for 5 = p < 100.
Find SUM(S(p)) for 5 = p < 10^8.*/
long long int q381() {
	// [(p - 1)! + (p - 2)! + (p - 3)! + (p - 4)! + (p - 5)!] mod(p)
	// = [(p - 5)! [(p - 1)(p - 2)(p - 3)(p - 4) + (p - 2)(p - 3)(p - 4) + (p - 3)(p - 4) + (p - 4) + 1]] mod(p)
	// = [(p - 5)! [p(p - 2)(p - 3)(p - 4) + (p - 3)(p - 4) + (p - 4) + 1]] mod(p)
	// Note that within the inner bracket, any term which is multiplied by a p will be 0 mod(p).
	// = [(p - 5)! [12 - 4 + 1]] mod(p)
	// = [(p - 5)! 9] mod(p)

	long long int sum = 0;

	// All primes greater than 3 can be written in the form 6k +/- 1.
	for (long long int p = 5; p < 100; p += 6) {
		if (p % 10000 == 1) { std::cout << p << std::endl; }

		if (prime_helper::is_prime(p)) {

			long long int S_p = (9 * factorial_helper::factorial_mod(p - 5, p)) % p;

			sum += S_p;
			std::cout << p << " " << S_p << " " << sum << std::endl;
		}

		if (prime_helper::is_prime(p + 2)) {

			long long int S_p = (9 * factorial_helper::factorial_mod(p - 3, p + 2)) % (p + 2);
			std::cout << (p + 2) << " " << S_p << " " << sum << std::endl;

			sum += S_p;
		}
	}

	return sum;
}


/*A Harshad or Niven number is a number that is divisible by the sum of its digits.
201 is a Harshad number because it is divisible by 3 (the sum of its digits.)
When we truncate the last digit from 201, we get 20, which is a Harshad number.
When we truncate the last digit from 20, we get 2, which is also a Harshad number.
Let's call a Harshad number that, while recursively truncating the last digit,
always results in a Harshad number a right truncatable Harshad number. Also:

201 / 3 = 67 which is prime. Let's call a Harshad number that, when divided
by the sum of its digits, results in a prime a strong Harshad number.

Now take the number 2011 which is prime. When we truncate the last digit from it
we get 201, a strong Harshad number that is also right truncatable.
Let's call such primes strong, right truncatable Harshad primes.

You are given that the sum of the strong, right truncatable Harshad primes less
than 10000 is 90619. Find the sum of the strong, right truncatable Harshad primes
less than 10^14.*/
long long int q387() {

	const long long int limit = 100000000000000;

	long long int sum = 0;

	// We can ignore single digit n since we cannot truncate
	for (int n = 11; n < limit; n += 2) {

		// if (n % 10000000 == 1) { std::cout << n << " " << sum << std::endl; }

		if (harshad_helper::is_strong_right_truncatable_harshad_prime(n)) {
			sum += n;

			// 181 181
			// 211 392
			// 271 663
			// 277 940
			// 421 1361
			// 457 1818
			// 631 2449
			// 2011 4460
			// 2017 6477
			std::cout << n << " " << sum << std::endl;
			
		}
	}

	return sum;
}
