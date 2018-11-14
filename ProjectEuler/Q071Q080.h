#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm> // std::min()
#include <sstream> // ostringstream

#include "fraction.h"
#include "ifstream_with_path.h"
#include "factorial_helper.h"
#include "factors_helper.h"
#include "right_angle_triangle_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*Consider the fraction, n/d, where n and d are positive integers.
If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
If we list the set of reduced proper fractions for d = 8 in ascending order of size, we get:
1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
It can be seen that 2/5 is the fraction immediately to the left of 3/7.
By listing the set of reduced proper fractions for d = 1,000,000
in ascending order of size, find the numerator of the fraction immediately to the left of 3/7.*/
int q71() {
	double upper = (3.0 / 7.0) , left = 0;
	int left_n = 0/*, left_d = 1*/;

	for (double d = 2; d <= 1000000; ++d) {
		// if ((int)d % 10000 == 0) {std::cout << d << std::endl;}

		double low = floor(d * left);
		for (double n = low; n < d; ++n) {
			double current = (n / d);
			// Will we continue to generate larger fractions than f(3, 7)?
			if (current >= upper) {
				break;
			}

			if (current > left) {
				left = current;
				left_n = (int)n;
				// left_d = (int)d;
			}
		}
	}

	return left_n;
}


/*Consider the fraction, n / d, where n and d are positive integers.
If n<d and HCF(n, d) = 1, it is called a reduced proper fraction.
If we list the set of reduced proper fractions for d = 8 in ascending order of size, we get :
1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
It can be seen that there are 21 elements in this set.
How many elements would be contained in the set of reduced proper fractions for d <= 1,000,000?*/
long long int q72() {
	// See Problem 69. We need the sum of the totients phi(d) for 2 <= d <= 1,000,000

	int limit = 1000000;
	long long int count = 0;

	for (int d = 2; d <= limit; ++d) {
		// if (d % 10000 == 0) { std::cout << d << std::endl; }

		count += factors_helper::phi(d);
	}

	return count;
}


/*Consider the fraction, n/d, where n and d are positive integers.
If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
If we list the set of reduced proper fractions for d = 8 in ascending order of size, we get:
1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
It can be seen that there are 3 fractions between 1/3 and 1/2.
How many fractions lie between 1/3 and 1/2 in the sorted set of reduced proper fractions for d <= 12,000?*/
int q73() {
	double upper = (1.0 / 2.0), lower = (1.0 / 3.0);
	std::set<double> set;

	for (double d = 2; d <= 12000; ++d) {
		// if ((int)d % 1000 == 0) {std::cout << d << std::endl;}

		double low = floor(d * lower);
		for (double n = low; n < d; ++n) {
			double current = (n / d);
			// Will we continue to generate larger fractions than f(1, 2)?
			if (current >= upper) {
				break;
			}

			if (current > lower) {
				set.insert(current);
			}
		}
	}

	return (int)set.size();
}


/*The number 145 is well known for the property that the sum of the factorial
of its digits is equal to 145:
1! + 4! + 5! = 1 + 24 + 120 = 145
Perhaps less well known is 169, in that it produces the longest chain of numbers
that link back to 169; it turns out that there are only three such loops that exist:
169 -> 363601 -> 1454 -> 169
871 -> 45361 -> 871
872 -> 45362 -> 872
It is not difficult to prove that EVERY starting number will eventually get stuck
in a loop. For example,
69 -> 363600 -> 1454 -> 169 -> 363601 (-> 1454)
78 -> 45360 -> 871 -> 45361 (-> 871)
540 -> 145 (-> 145)
Starting with 69 produces a chain of five non-repeating terms, but the longest
non-repeating chain with a starting number below one million is sixty terms.
How many chains, with a starting number below one million, contain exactly
sixty non-repeating terms?*/
int q74() {
	int count = 0;

	for (int n = 1; n < 1000000; ++n) {
		// if (n % 10000 == 0) { std::cout << n << std::endl; }

		std::vector<int> chain;
		chain.reserve(64);
		chain.push_back(n);

		int fact_sum = n;
		while (chain.size() < 61) {

			int remain = fact_sum;
			fact_sum = 0;
			while (remain > 0) {
				fact_sum += factorial_helper::factorial(remain % 10);
				remain /= 10;
			}

			// Check whether we have seen this number before in the chain
			bool repeated = false;
			for (std::vector<int>::const_iterator it = chain.begin(); it != chain.end(); ++it) {
				if (*it == fact_sum) {
					repeated = true;
					break;
				}
			}
			if (repeated) {
				if (chain.size() == 60) {
					++count;
				}
				break;
			}
			else {
				chain.push_back(fact_sum);
			}
		}
	}

	return count;
}


/*It turns out that 12 cm is the smallest length of wire that can be bent
to form an integer sided right angle triangle in exactly one way, but there
are many more examples.
12 cm: (3,4,5)
24 cm: (6,8,10)
30 cm: (5,12,13)
36 cm: (9,12,15)
40 cm: (8,15,17)
48 cm: (12,16,20)
In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer
sided right angle triangle, and other lengths allow more than one solution to be
found; for example, using 120 cm it is possible to form exactly three different
integer sided right angle triangles.
120 cm: (30,40,50), (20,48,52), (24,45,51)
Given that L is the length of the wire, for how many values of L <= 1,500,000 can
exactly one integer sided right angle triangle be formed?*/
int q75() {

	const int limit = 1500000;

	// Number of ways to form integer sided right angle triangle with perimeter = index + 1
	std::vector<int> triangle(limit), prim_triangles;

	right_angle_triangle_helper::generate_primitive_perimeters(limit, prim_triangles);

	for (std::vector<int>::iterator it = prim_triangles.begin(); it != prim_triangles.end(); ++it) {
		int multiplier = 1;

		while ((*it * multiplier) <= limit) {
			++triangle[(*it * multiplier) - 1];
			++multiplier;
		}
	}

	int count = 0;
	for (std::vector<int>::const_iterator it = triangle.begin(); it != triangle.end(); ++it) {
		if (*it == 1) {
			++count;
		}
	}

	return count; // 161667
}


template <typename T>
T recursive_sum_count(const T &remaining, const T &num, std::vector<std::vector<int> > &cache) {
	if (num == 1 || remaining == 0) {
		return 1;
	}

	if (cache[remaining - 1][num - 1] != -1) {
		return cache[remaining - 1][num - 1];
	}

	T ways = 0;

	const T limit = remaining / num;
	for (T i = 0; i <= limit; ++i) {
		ways += recursive_sum_count((remaining - (i * num)), num - 1, cache);
	}

	cache[remaining - 1][num - 1] = ways;

	return ways;
}

/*It is possible to write five as a sum in exactly six different ways:
4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1
How many different ways can one hundred be written as a sum of at least two positive integers?*/
int q76() {
	// Q76, Q77 and Q78 are all very similar!

	const int target = 100;

	std::vector<int> row(target, -1);
	std::vector<std::vector<int> > cache(target, row);

	// Largest num can be target - 1 as we need the sum of at least two integers
	return recursive_sum_count(target, target - 1, cache);
}


template <typename T>
T recursive_sum_count(const T &remaining, const typename std::vector<T>::reverse_iterator &primes_rit,
	const typename std::vector<T>::reverse_iterator &primes_rend) {
	
	if (primes_rit == primes_rend || remaining < 2) {
		// Return 1 if we succeeded and have no remainder 
		return remaining == 0 ? 1 : 0;
	}

	T ways = 0;

	const int limit = remaining / *primes_rit;
	for (int i = 0; i <= limit; ++i) {
		std::vector<int>::reverse_iterator next_rit = primes_rit;
		++next_rit;
		ways += recursive_sum_count((remaining - (i * (*primes_rit))), next_rit, primes_rend);
	}

	return ways;
}

/*It is possible to write ten as the sum of primes in exactly
five different ways:
7 + 3
5 + 5
5 + 3 + 2
3 + 3 + 2 + 2
2 + 2 + 2 + 2 + 2
What is the first value which can be written as the sum of
primes in over five thousand different ways?*/
int q77() {
	// Q76, Q77 and Q78 are all very similar!

	std::vector<int> primes;
	primes.push_back(2);
	primes.push_back(3);

	int n = 9, count = 0;

	while (count < 5000) {
		++n;

		if (n % 10000 == 0) { std::cout << n << std::endl; }

		// Generate more primes
		for (int p = primes.back() + 2; p < n; p += 2) {
			if (prime_helper::is_prime(p)) {
				primes.push_back(p);
			}
		}

		count = recursive_sum_count(n, primes.rbegin(), primes.rend());

		// std::cout << n << " " << count << std::endl;
	}

	return n; // 71
}


template <typename T>
T recursive_sum_count_mod(const T &remaining, const T &num, std::map<std::string, long long int> &ways_cache, const int &mod) {
	if (num == 1 || remaining == 0) {
		return 1;
	}

	std::ostringstream stringstream;
	stringstream << remaining << "-" << num;

	const std::map<std::string, long long int>::const_iterator it = ways_cache.find(stringstream.str());
	if (it == ways_cache.end()) {
		T ways = 0;

		const T limit = remaining / num;
		for (T i = 0; i <= limit; ++i) {
			ways += recursive_sum_count_mod((remaining - (i * num)), num - 1, ways_cache, mod);
		}

		ways %= mod;

		ways_cache.insert(std::pair<std::string, long long int>(stringstream.str(), ways));

		return ways;
	}

	return it->second;
}

/*Let p(n) represent the number of different ways in which n coins can be separated
into piles. For example, five coins can be separated into piles in exactly seven
different ways, so p(5) = 7.
OOOOO
OOOO   O
OOO   OO
OOO   O   O
OO   OO   O
OO   O   O   O
O   O   O   O   O
Find the least value of n for which p(n) is divisible by one million?*/
long long int q78() {
	// Q76, Q77 and Q78 are all very similar!
	
	const int divisible = 1000000;

	std::map<std::string, long long int> ways_cache;

	long long int n = 4;

	while (true) {
		++n;

		// if (n % 10000 == 0) { std::cout << n << std::endl; }

		long long int count = recursive_sum_count_mod(n, n, ways_cache, divisible);

		// std::cout << n << " " << count << std::endl;

		if (count % divisible == 0) {
			break;
		}
	}

	return n;
}



/*A common security method used for online banking is to ask the user for three
random characters from a passcode. For example, if the passcode was 531278, they
may ask for the 2nd, 3rd, and 5th characters; the expected reply would be: 317.

The text file, keylog.txt, contains fifty successful login attempts.
Given that the three characters are always asked for in order, analyse the file
so as to determine the shortest possible secret passcode of unknown length.*/
int q79() {

	// std::set will auto remove duplicates and order elements.
	// These sets will house our test conditions. The only time we need
	// to test using three digits is if all three digits are the same.
	// E.g. testing 3 digit combo "123" is equivalent to testing 2 digit
	// combo "12" and 2 digit combo "23".
	std::set<int> attempts_3_digits, attempts_2_digits;

	// To work out minimum number of passcode digits
	std::map<int, int> digits;

	ifstream_with_path fin("Problem79.txt");
	for (int i = 0; i < 50; ++i) {
		int n;
		fin >> n;

		int first = n / 100;
		int second = (n / 10) % 10;
		int third = n % 10;

		// Deal with digit repeated three times
		if (first == second && second == third) {
			digits[first] = 3;
			attempts_3_digits.insert(n);
		}

		attempts_2_digits.insert(n / 10); // Front two digits
		attempts_2_digits.insert(n % 100); // Back two digits

		// Deal with digit repeated two times
		if (first == second) {
			digits[first] = std::max(digits[first], 2);
			digits[third] = std::max(digits[third], 1);
		}
		else if (second == third) {
			digits[second] = std::max(digits[second], 2);
			digits[first] = std::max(digits[first], 1);
		}
		else if (first == third) {
			digits[first] = std::max(digits[first], 2);
			digits[second] = std::max(digits[second], 1);
		}
		else {
			digits[first] = std::max(digits[first], 1);
			digits[second] = std::max(digits[second], 1);
			digits[third] = std::max(digits[third], 1);
		}
	}
	fin.close();

	int min_passcode_digits = 0;
	for (std::map<int, int>::const_iterator it = digits.begin(); it != digits.end(); ++it) {
		min_passcode_digits += it->second;
	}

	// Brute force by seeing whether each trial obeys the attempts given
	int trial = (int)pow(10, min_passcode_digits - 1);
	while (true) {
		// if (trial % 1000000 == 0) { std::cout << trial << std::endl; }
		
		bool all_attempts_pass = true;

		// Go through the three digit combo attempts
		if (!attempts_3_digits.empty()) {
			for (std::set<int>::const_iterator it = attempts_3_digits.begin(); it != attempts_3_digits.end(); ++it) {
				int remain = trial;

				bool first_found = false, second_found = false, third_found = false;
				while (remain > 0) {
					int digit = remain % 10;
					remain /= 10;

					if (!third_found) {
						if (digit == *it % 10) {
							third_found = true;
						}
					}
					else if (!second_found) {
						if (digit == (*it / 10) % 10) {
							second_found = true;
						}
					}
					else if (digit == *it / 100) {
						first_found = true;
						break;
					}
				}

				if (!first_found) {
					all_attempts_pass = false;
					break;
				}
			}
		}

		// Go through the two digit combo attempts
		if (!attempts_2_digits.empty() && all_attempts_pass) {
			for (std::set<int>::const_iterator it = attempts_2_digits.begin(); it != attempts_2_digits.end(); ++it) {
				// Find front digit and second digit's position within trial

				int remain = trial;
				bool first_found = false, second_found = false;
				while (remain > 0) {
					int digit = remain % 10;
					remain /= 10;

					if (!second_found) {
						if (digit == *it % 10) {
							second_found = true;
						}
					}
					else if (digit == *it / 10) {
						first_found = true;
						break;
					}
				}

				if (!first_found) {
					all_attempts_pass = false;
					break;
				}
			}
		}

		if (all_attempts_pass) {
			break;
		}
		else {
			++trial;
		}
	}

	return trial;
}

/*It is well known that if the square root of a natural number is not an integer,
then it is irrational. The decimal expansion of such square roots is infinite without
any repeating pattern at all. The square root of two is 1.41421356237309504880...,
and the digital sum of the first one hundred decimal digits is 475.
For the first one hundred natural numbers, find the total of the digital sums
of the first one hundred decimal digits for all the irrational square roots.*/
int q80() {
	/* Use Newton - Raphson method for calculating square roots.
	in sqrt method to initialize Newton - Raphson variables to speed things up.
		
	
		cache all calculated square roots
		only use Newton - Raphson to calculate the square roots of prime numbers.
		for numbers which are squares, calculate the square root the easy way.
		And don't store lots of trailing zeros, since these don't add anything to the digit sum in the end.
		for all other numbers, multiply two already calculated square roots.
		But choose carefully and prefer multiplying a simple square root over multiplying
		two long square roots(example : sqrt(12) = 2 * sqrt(3) is faster than sqrt(12) = sqrt(2) * sqrt(6))
		calculate some extra digits(say 10) to make sure that multiplication etc doesn't lead to wrong answers
		of course, when summing the final answer, only look at the requested number of digits
		use BigInteger.toString() to get all the digits.This is faster than calculating them in some other ways.
		*/

	return 1;
}
