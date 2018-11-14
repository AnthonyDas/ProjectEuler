#include <iostream>
#include <vector>
#include <float.h>

// #include "base_helper.h"
#include "factors_helper.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net



/*A positive fraction whose numerator is less than its denominator is called a proper fraction.
For any denominator, d, there will be d-1 proper fractions; for example, with d=12:
1/12 , 2/12 , 3/12 , 4/12 , 5/12 , 6/12 , 7/12 , 8/12 , 9/12 , 10/12 , 11/12 .
We shall call a fraction that cannot be cancelled down a resilient fraction.
Furthermore we shall define the resilience of a denominator, R(d), to be the
ratio of its proper fractions that are resilient; for example, R(12) = 4/11 .
In fact, d=12 is the smallest denominator having a resilience R(d) < 4/10 .
Find the smallest denominator d, having a resilience R(d) < 15499/94744.*/
long long int q243() {
	// See Problem 69 which employs Euler's Totient function, phi(n).
	// From observation of how to get the smallest phi(n) relative to n
	// (i.e. small phi(n)/n), it is apparent that we need n to have as
	// many distinct primes in its prime factorisation as possible. Why?
	// Consider if n already has prime p (to the power of one) in its
	// prime factorisation. By multiplying n by another p, n has increased
	// in size by p, but so too has phi(n). So the original ratio phi(n)/n
	// gets multipled by p/p = 1 and hence remains unchanged. However,
	// by multiplying n by some new prime q, n will increased in size by q,
	// and phi(n) will increase in size by only (q - 1). So the original
	// phi(n)/n is multipled by (q - 1)/q < 1, making phi(n)/n) smaller.

	// First we consider how many distinct primes we need in a prime
	// factorisation to get close to the target
	long double target = 15499.0L / 94744.0L, smallest = LDBL_MAX;

	long long int prime_prod = 2;

	int prime = 1;
	while (true) {
		prime += 2;

		if (!prime_helper::is_prime(prime)) {
			continue;
		}

		prime_prod *= prime;

		long double ratio = factors_helper::phi(prime_prod) / (prime_prod - 1.0L); // 1.0L to calc as long double 

		if (ratio < smallest) {
			smallest = ratio;
		}

		// std::cout << prime << " " << prime_prod << " " << smallest << " " << target << " " << (smallest - target) << std::endl;

		if (ratio < target) {
			// We have gone too far
			prime_prod /= prime;
			break;
		}
	}

	// The above code outputs: 
	// 3 6 0.4 0.163588 0.236412
	// 5 30 0.275862 0.163588 0.112274
	// 7 210 0.229665 0.163588 0.0660769
	// 11 2310 0.207882 0.163588 0.044294
	// 13 30030 0.191815 0.163588 0.0282264
	// 17 510510 0.180526 0.163588 0.0169375
	// 19 9699690 0.171024 0.163588 0.00743584
	// 23 223092870 0.163588 0.163588 5.3031e-10
	// 29 6469693230 0.157947 0.163588 -0.00564097

	// So we see that we need n = 2.3.5.7.11.13.17.19.23 = 223092870
	// to get ever so close to the target whilst multiplying by the last
	// prime 29 pushes us past the target.  

	// To refine n even further we note that we actually want the ratio
	// phi(n)/(n - 1). Note that by multiplying n by a positive integer, m > 1,
	// (less than or equal to the greatest prime already found in n's
	// prime factorisation), say m <= 23, both phi(n) and n would be multiplied
	// by m. However, considering the ratio phi(n)/(n - 1):
	// phi(n.m)/(n.m - 1) < phi(n.m)/(n.m - m) = m.phi(n)/m(n - 1) = phi(n)/(n - 1).
	// So mutiplying n by m helps to reduce phi(n)/(n - 1).

	long long int d = prime_prod, m = 1;
	smallest = LDBL_MAX;
	while (true) {
		long double ratio = factors_helper::phi(d) / (d - 1.0L); // 1.0L to calc as long double 

		if (ratio < smallest) {
			smallest = ratio;
		}

		// std::cout << m << " " << d << " " << smallest << " " << target << " " << (smallest - target) << std::endl;

		if (ratio < target) {
			break;
		}

		++m;
		d = prime_prod * m;
	}

	// The above code outputs:
	// 1 223092870 0.163588 0.163588 5.3031e-10
	// 2 446185740 0.163588 0.163588 1.63673e-10
	// 3 669278610 0.163588 0.163588 4.14603e-11
	// 4 892371480 0.163588 0.163588 -1.96459e-11
	
	return d; // 223092870 x 4 = 892371480
}

