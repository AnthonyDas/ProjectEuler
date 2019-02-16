#include <iostream>
#include <vector> 
#include <string>
#include <algorithm> // sort
#include <set>
#include <map> 

#include "ifstream_with_path.h"

#include "prime_helper.h" 
#include "factors_helper.h" 
#include "greatest_common_divisor_helper.h" 
#include "fraction.h" 
//#include "pan_digit_helper.h"  
#include "permutation_helper.h"  
#include "fibonacci_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


/* Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called
amicable numbers. For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110;
therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
Evaluate the sum of all the amicable numbers under 10000. */
int q21() {
	int b, sum = 0;
	const int limit = 10000;

	for (int a = 1; a < limit; ++a) {
		b = factors_helper::sum_proper_divisors(a);

		// Exclude b < a - as these will have been considered by an earlier iteration
		// Exclude b == a - as per the definition of amicable numbers
		if (b > a && a == factors_helper::sum_proper_divisors(b)) {
			// cout << "Found amicable numbers a: " << a << ", b: " << b << "." << endl;
			sum += a; // a < limit by design
			if (b < limit) {
				sum += b;
			}
		}
		// if (a % 1000 == 0) { std::cout << "Processed up to: " << a << "." << endl;}
	}
	// Q21. Sum of all the amicable numbers under 10000 [31626]
	// cout << "Q21. Sum of all the amicable numbers under 10000 [" << sum << "]" << endl; 

	return sum;
}


/* Using names.txt (right click and 'Save Link/Target As...'), a 46K text file
containing over five-thousand first names, begin by sorting it into alphabetical order.
Then working out the alphabetical value for each name, multiply this value by its
alphabetical position in the list to obtain a name score. For example, when the
list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53,
is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.
What is the total of all the name scores in the file?*/
int q22() {
	ifstream_with_path fin("Problem22.txt");

	std::vector<std::string> names;
	std::string next;
	while (fin >> next) {
		names.push_back(next);
	}
	fin.close();

	sort(names.begin(), names.end()); // Use algorithm to sort

	unsigned int total_score = 0, score;
	for (unsigned int i = 0; i < names.size(); ++i) {
		next = names[i];

		score = 0;
		for (unsigned int j = 0; j < next.length(); ++j) {
			score += next[j] - 'A' + 1; // Making "A" have score 1
		}
		score *= (i+1); // Multiply by sorted position

		total_score += score;
	}

	// Q22. Total name score [871198282]
	// std::cout << "Q22. Total name score [" << totalscore << "]" << endl; 

	return total_score;
}


/* A perfect number is a number for which the sum of its proper divisors
is exactly equal to the number. For example, the sum of the proper divisors
of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
A number n is called deficient if the sum of its proper divisors is less than n
and it is called abundant if this sum exceeds n. As 12 is the smallest abundant
number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the
sum of two abundant numbers is 24. By mathematical analysis, it can be shown that
all integers greater than 28123 can be written as the sum of two abundant numbers.
However, this upper limit cannot be reduced any further by analysis even though
it is known that the greatest number that cannot be expressed as the sum of two
abundant numbers is less than this limit. Find the sum of all the positive integers
which cannot be written as the sum of two abundant numbers.*/
unsigned int q23() {
	const unsigned int limit = 28123;
	std::vector<unsigned int> abundant;
	std::vector<bool> sum_two_abundant(limit, false); // Records which numbers can be expressed as sum of 2 abundant no.s

	// std::cout << "Abundant numbers:" << endl;
	for (unsigned int i = 12; i <= limit; ++i) {
		if (factors_helper::is_abundant(i)) {
			// std::cout << i << " ";
			abundant.push_back(i);
		}
	}

	// Exhaustive pairing of all abundant numbers up to limit
	for (std::vector<unsigned int>::iterator it_i = abundant.begin(); it_i != abundant.end(); ++it_i) {
		for (std::vector<unsigned int>::iterator it_j = it_i; it_j != abundant.end(); ++it_j) {
			unsigned int sum = (*it_i) + (*it_j);
			if (sum <= limit) {
				sum_two_abundant[sum - 1] = true; // -1 offset
			}
			else {
				// Will always go above limit
				break;
			}
		}
	}

	// std::cout << "\n\nCannot be expressed as the sum of two abundant numbers:" << endl;
	unsigned int sum = 0;
	for (std::vector<bool>::iterator it = sum_two_abundant.begin(); it != sum_two_abundant.end(); ++it) {
		if (*it) {
			continue;
		}
		// std::cout << (i + 1) << " ";
		sum += (unsigned int)(it - sum_two_abundant.begin()) + 1; // +1 offset
	}

	// Q23. Sum of all +ve integers which cannot be written as sum of 2 abundant numbers [4179871]
	// cout << "Q23.Sum of all +ve integers which cannot be written as sum of 2 abundant numbers [" << sum << "]" << endl; 

	return sum;
}


/* A permutation is an ordered arrangement of objects. For example, 3124 is
one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
are listed numerically or alphabetically, we call it lexicographic order.
The lexicographic permutations of 0, 1 and 2 are: 012   021   102   120   201   210
What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?*/
std::string q24() {
	/*std::vector<long long int> res;
	res.reserve(3628800); // Performance reserve space for 10! results

	pan_digit_helper::create_pan_digits(res, 0, 9); 

	// for (int i = 999998; i < 1000001; ++i) {
	// 	cout << i << " " << res[i] << endl;
	// }

	long long int millionth = res[999999];
	//Q24. The millionth lexicographic permutation of digits 0, 1,..., 9 [2783915460]
	// cout << "Q24. The millionth lexicographic permutation of digits 0, 1,..., 9 [" << millionth << "]" << endl;

	return millionth;*/
	long long int perm = 1000000;
	std::list<int> ls = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	return permutation_helper::calc_permutation(ls, perm);
}


/*The Fibonacci sequence is defined by the recurrence relation:
F(n) = F(n−1) + F(n−2), where F(1) = 1 and F(2) = 1.
Hence the first 12 terms will be:
F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F10 = 55
F11 = 89
F12 = 144
The 12th term, F12, is the first term to contain three digits.
What is the first term in the Fibonacci sequence to contain 1000 digits? */
int q25() {
	/*int count = 2;
	vector_int a(1), b(1);

	while (true) {
		vector_int next_fib = a + b;
		a = b;
		b = next_fib;
		
		++count;

		// std::cout << next_fib << std::endl;

		if (next_fib.size() >= 1000) {
			break;
		}
	}

	// cout << "Q25. First Fibonacci term with 1000 digits" << vec[vec.size() - 1] << endl;
	// cout << "Q25. Fibonacci term [" << vec.size() << "]" << endl; // Fibonacci term [4782]

	return count;*/

	return fibonacci_helper::index_of_first_term_with_n_digits(1000);
}

/* A unit fraction contains 1 in the numerator. The decimal representation of the unit
fractions with denominators 2 to 10 are given:
1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that
1/7 has a 6-digit recurring cycle. Find the value of d < 1000 for which 1/d contains the
longest recurring cycle in its decimal fraction part.*/
int q26() {
	const int limit = 1000;
	int  max_d = 0;
	size_t max_cycle = 0;

	for (int d = 2; d < limit; ++d) {
		fraction<int> current(1, d);
		// cout << current << "  ";

		current.calc_decimal_representation();
		// current.printExactDecimalRepresentation();
		// cout << endl;

		if (current.repeat_size() > max_cycle) {
			// cout << "Denominator [" << d << "], cycle length [" << current.repeatSize() << "]" << endl;
			max_cycle = current.repeat_size();
			max_d = d;
		}
	}
	// Q26. Denomiator [983], has the max cycle length [982]
	// cout << "Q26. Denomiator [" << maxd << "], has the max cycle length [" << maxCycle << "]" << endl;

	return max_d;
}

/*Euler published the remarkable quadratic formula: n² + n + 41
It turns out that the formula will produce 40 primes for the consecutive
values n = 0 to 39. However, when n = 40, 40^2 + 40 + 41 = 40(40 + 1) + 41
is divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly
divisible by 41. Using computers, the incredible formula  n² - 79n + 1601
was discovered, which produces 80 primes for the consecutive values n = 0 to 79.
The product of the coefficients, -79 and 1601, is -126479.

Considering quadratics of the form: n² + an + b, where |a| < 1000 and |b| < 1000
where |n| is the modulus/absolute value of n, e.g. |11| = 11 and |-4| = 4
Find the product of the coefficients, a and b, for the quadratic expression
that produces the maximum number of primes for consecutive values of n, starting with n = 0.*/
int q27() {
	int max_count = 0, product = 0;

	// Exhaustive search over all possible coefficient pairings
	// within range |a| < 1000 and |b| < 1000
	for (int a = -999; a < 1000; ++a) {
		for (int b = -999; b < 1000; ++b) {
			int n = 0;
			while (prime_helper::is_prime(n*n + a*n + b)) {
				++n;
			}
			if (n > max_count) {
				max_count = n;
				product = a * b;
			}
		}
	}

	// Q27. Max count [71] a [-61] b [971] product a*b [-59231]
	// cout << "Q27. Max count [" << maxcount << "] a [" << maxa << "] b [" << maxb << "] product a*b [" << product << "]" << endl;

	return product;
}

/* Starting with the number 1 and moving to the right in a
clockwise direction a 5 by 5 spiral is formed as follows:
21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13
It can be verified that the sum of the numbers on the diagonals
is 101. What is the sum of the numbers on the diagonals in a 1001
by 1001 spiral formed in the same way? */
int q28() {
	/*int sum = 1, step = 2, next = 1;

	for (int j = 0; j < 500; ++j) { // 500 outer rings
		for (int i = 0; i < 4; ++i) { // Each of the 4 diagonal entries
			next += step;
			// cout << next << " ";
			sum += next;
		}
		step += 2; // Step increases by 2 in next ring 
	}

	// Q28. Sum of diagonals in a 1001 by 1001 spiral [669171001]
	// cout << "Q28. Sum of diagonals in a 1001 by 1001 spiral [" << sum << "]" << endl; 

	return sum;*/

	// Diagonal sums form a difference equation with stable 3rd level difference.
	// Hence from trying equation of form f(n) = a.n^3 + b.n^2 + c.n + d 
	// and plugging in values for small n, we get:
	// f(0): d = 1
	// f(1): a + b + c + d = 25
	// f(2): 8a + 4b + 2c + d = 101
	// f(3): 27a + 9b + 3c + d = 261
	
	// Solving simultaneous equations we derive the formula as
	// f(n) = (16/3).n^3 + 10.n^2+ (26/3).n + 1, for n = 0, 1, 2,....
	// Importantly, n is the term in the sequence which
	// gives corresponding grid side length of (2n + 1)

	int len = 1001;
	int n = (len - 1) / 2;
	
	// Only div by 3 after calculating the whole numerator
	return ((16 * (int)pow(n, 3) + 26 * n) / 3) + 10 * (int)pow(n, 2) + 1; // 669171001
}


/* Consider all integer combinations of a^b for 2 = a = 5 and 2 = b = 5:
2^2=4, 2^3=8, 2^4=16, 2^5=32
3^2=9, 3^3=27, 3^4=81, 3^5=243
4^2=16, 4^3=64, 4^4=256, 4^5=1024
5^2=25, 5^3=125, 5^4=625, 5^5=3125
If they are then placed in numerical order, with any repeats removed,
we get the following sequence of 15 distinct terms:
4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125
How many distinct terms are in the sequence generated by a^b
for 2 = a = 100 and 2 = b = 100? */
int q29() {
	const int limit = 100;
	/*
	// Creating and storing string representations of the prime factorisations within the
	// set is faster than storing vectors of the same prime factorisations
	std::set<std::string> my_set;

	for (int a = 2; a <= limit; ++a) {
		std::map<int, unsigned int> factors;
		factors_helper::factorise(a, factors);

		for (int b = 2; b <= limit; ++b) {
			std::ostringstream stringstream;
			
			for (std::map<int, unsigned int>::const_iterator it = factors.begin(); it != factors.end(); ++it) {
				stringstream << "[" << it->first << "," << (it->second * b) << "]";
			}

			my_set.insert(stringstream.str());
		}
	}

	// Q29. Distinct terms in the sequence [9183]
	// cout << "Q29. Distinct terms in the sequence [" << count << "]" << endl; 

	return (int)my_set.size();*/

	// This question hinges on working out when some base value "a" is in fact some
	// smaller value "b" to some power. E.g. when we consider a = 9, we will already
	// have seen many of the numbers it generates in the series 9^n, 2 <= n <= 100,
	// beause 9 = 3^2 and we will have already generation the series 3^n, 2 <= n <= 100.

	// First, work out the maximum power that some base value "a" coule be up to the limit.
	// As 2 is the smallest possibe base "a", we simply work out the maximum power of 2.
	int max_pow = (int)(log(limit) / log(2));

	// Now we deduce how many new (i.e. distinct) numbers a base value "a" generates
	// depending on what power "a" is, (i.e. is it a square, cube, etc).
	std::set<int> pow;
	for (int i = 2; i <= limit; ++i) {
		pow.insert(i);
	}
	std::vector<int> pow_count;
	pow_count.push_back((int)pow.size());
	int total = (int)pow.size();
	for (int i = 2; i <= max_pow; ++i) {
		for (int j = 2; j <= limit; ++j) {
			// Add all the powers that will be generated.
			// As pow is a set, it only stores distinct power values.
			pow.insert(i * j); 
		}
		// Add the count on the ADDITIONAL powers
		pow_count.push_back((int)pow.size() - total);
		total = (int)pow.size();
	}

	int count = 0;
	for (int a = 2; a <= limit; ++a) {
		auto factors = factors_helper::factorise(a);

		// Calculate the gdc of the powers within the prime factorisation.
		// This will determine whether "a" is in fact a square, cube etc.
		unsigned int gcd = factors.begin()->second;
		for (auto it = ++factors.begin(); it != factors.end(); ++it) {
			gcd = greatest_common_divisor_helper::gcd(gcd, it->second);
		}

		// Add the appropriate count of distinct values this "a" will generate
		count += pow_count[gcd - 1];
	}

	return count;
}


/* Surprisingly there are only three numbers that can be written
as the sum of fourth powers of their digits:
1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 1^4 is not a sum it is not included. The sum of these numbers
is 1634 + 8208 + 9474 = 19316. Find the sum of all the numbers that
can be written as the sum of fifth powers of their digits. */
int q30() {
	// The hardest part to this problem is deciding the upper limit.
	// Consider the sum of fourth powers of digits case. We have 9^4 = 6561.
	// The largest sum of any fourth powers of a 5 digit number corresponds to 99999:
	// 5 * 9^4 = 32805 a five digit number, (i.e. same order as starting number).
	// The largest sum of any fourth powers of a 6 digit number corresponds to 999999:
	// 6 * 9^4 = 39366 a FIVE digit number, (i.e. smaller order than starting number).
	// Hence, is becomes clear that we only need to consider 5 digit numbers
	// as we can NEVER get a 6 digit number to have a 6 digit sum of fourth powers.

	// Consider the sum of fifth powers of digits case. We have 9^5 = 59049.
	// The largest sum of fifth powers of a 7 digit number corresponds to 9999999:
	// 7 * 9^5 = 413343 a SIX digit number (i.e. smaller order than starting number).
	// Hence, is becomes clear that we only need to consider up to 6 digit numbers.

	const int power = 5;

	int digits = 1;
	while (digits <= number_helper::digits_count(digits * (int)pow(9, power))) {
		++digits;
	}

	// digits is too big now so -1
	--digits;

	const int limit = digits * (int)pow(9, power);
	// cout << digits << " " << limit << endl;

	int sum = 0;

	for (int i = 2; i <= limit; ++i) { // Exclude 1 as not a sum
		int sum_digit_pow = 0, carry = i;

		while (carry > 0) {
			int digit = carry % 10;
			carry /= 10;
			sum_digit_pow += (int)pow(digit, power);
		}

		if (i == sum_digit_pow) {
			// Found: [+4 1 5 0 ]
			// Found: [+4 1 5 1 ]
			// Found: [+5 4 7 4 8 ]
			// Found: [+9 2 7 2 7 ]
			// Found: [+9 3 0 8 4 ]
			// Found: [+1 9 4 9 7 9 ]
			// std::cout << "Found: " << next << endl;
			sum += i;
		}
	}

	// Q30. Sum of all numbers that can be written as sum of fifth powers of their digits [443839]
	// cout << "Q30. Sum of all numbers that can be written as sum of fifth powers of their digits [" << numberSum << "]" << endl;

	return sum;
}