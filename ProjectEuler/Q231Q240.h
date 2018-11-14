#include <iostream>
#include <map>

#include "factors_helper.h"
// #include "ifstream_with_path.h"
// #include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


/*The binomial coefficient 10C3 = 120.
120 = 2^3 × 3 × 5 = 2 × 2 × 2 × 3 × 5, and 2 + 2 + 2 + 3 + 5 = 14.
So the sum of the terms in the prime factorisation of 10C3 is 14. 
Find the sum of the terms in the prime factorisation of 20000000C15000000.*/
long long int q231() {

	// nCr = n! / r!(n-r)!
	// 20000000C15000000 = 20000000! / 15000000! * 5000000!

	std::map<int, unsigned int> numerator_factors, denominator_factors;

	for (int n = 15000001; n <= 20000000; ++n) {

		std::map<int, unsigned int> factors;
		factors_helper::factorise(n, factors);

		for (std::map<int, unsigned int>::const_iterator it = factors.begin(); it != factors.end(); ++it) {
			numerator_factors[it->first] += it->second;
		}
	}

	for (int n = 2; n <= 5000000; ++n) {

		std::map<int, unsigned int> factors;
		factors_helper::factorise(n, factors);

		for (std::map<int, unsigned int>::const_iterator it = factors.begin(); it != factors.end(); ++it) {
			denominator_factors[it->first] += it->second;
		}
	}

	// Divide the numerator by the denominator
	for (std::map<int, unsigned int>::const_iterator it = denominator_factors.begin(); it != denominator_factors.end(); ++it) {
		numerator_factors[it->first] -= it->second;
	}

	long long int sum = 0;
	for (std::map<int, unsigned int>::const_iterator it = numerator_factors.begin(); it != numerator_factors.end(); ++it) {
		sum += (it->first * it->second);
	}
	return sum; // 7526965179680
}

/*Let f(N) be the number of points with integer coordinates
that are on a circle passing through (0,0), (N,0),(0,N), and (N,N).
It can be shown that f(10000) = 36.
What is the sum of all positive integers N <= 10^11 such that f(N) = 420?*/
int q233() {
	
	// Circle centre is point (N/2, N/2)
	// Radius^2 = (N^2)/4 + (N^2)/4 = (N^2)/2
	// Equation: (x - N/2)^2 + (y - N/2)^2 = (N^2)/2

	return 1; // 
}

