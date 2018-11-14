#include <iostream> 
#include <vector>
#include <map>
#include <string>
 
#include "prime_helper.h" 
#include "ifstream_with_path.h"
#include "pan_digit_helper.h"  
#include "shape_number.h" 
#include "permutation_helper.h"
#include "factors_helper.h"
#include "factorial_helper.h"
#include "number_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/* We shall say that an n-digit number is pandigital if it makes
use of all the digits 1 to n exactly once. For example, 2143 is
a 4-digit pandigital and is also prime. What is the largest n-digit
pandigital prime that exists? */
int q41() {
	// Primes can only be 4 and 7 digit pandigitals. This is because all
	// other length pandigits have digit sum = 0 mod 3 and hence are divisible by 3.
	// 1: 1 = 1 mod 3 (but 1 digit pandigital is 1 which is non prime)
	// 2: 3 = 0 mod 3
	// 3: 6 = 0 mod 3
	// 4: 10 = 1 mod 3
	// 5: 15 = 0 mod 3
	// 6: 21 = 0 mod 3
	// 7: 28 = 2 mod 3
	// 8: 36 = 0 mod 3
	// 9: 45 = 0 mod 3

	int largest = 0;

	// Digits arranged in decreasing order
	std::list<int> ls = { 7, 6, 5, 4, 3, 2, 1 };

	for (int i = 0; i < 2; ++i) { // Remove digits from ls

		const int max = factorial_helper::factorial((int)ls.size());
		for (int p = 1; p <= max; ++p) {
			std::string str = permutation_helper::calc_permutation(ls, p);

			int current = (int)number_helper::stringToInt(str);
			if (prime_helper::is_prime(current)) {
				largest = current;
				break;
			}
		}

		if (largest != 0) {
			break;
		}

		// 7 to 4 digits
		ls.pop_front();
		ls.pop_front();
		ls.pop_front();
	}

	 return largest;
}


/* The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1);
so the first ten triangle numbers are: 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
By converting each letter in a word to a number corresponding to its alphabetical
position and adding these values we form a word value. For example, the word value
for SKY is 19 + 11 + 25 = 55 = t10.
If the word value is a triangle number then we shall call the word a triangle word.
Using words.txt (right click and 'Save Link/Target As...'), a 16K text file
containing nearly two-thousand common English words, how many are triangle words? */
int q42() {
	ifstream_with_path fin("Problem42.txt");

	std::vector<int> word_scores; // Storage for all word scores
	int word_score_max = 0;
	std::string word;
	while (fin >> word) {
		int word_score = 0;
		for (std::string::iterator it = word.begin(); it != word.end(); ++it) {
			word_score += *it - 'A' + 1; // +1 as 'A' has score 1
		}
		word_scores.push_back(word_score);
		if (word_score_max < word_score) {
			word_score_max = word_score;
		}
	}
	fin.close();

	triangle_number<int> triangle;

	int count = 0;
	for (std::vector<int>::const_iterator it = word_scores.begin(); it != word_scores.end(); ++it) {
		if (triangle.get_n(*it) != -1) {
			++count;
		}	
	}

	// Q42. Triangle word count [162]
	// std::cout << "Q42. Triangle word count [" << count << "]" << std::endl;

	return count;
}


/*The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order,
but it also has a rather interesting sub-string divisibility property.
Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:
d2d3d4=406 is divisible by 2
d3d4d5=063 is divisible by 3
d4d5d6=635 is divisible by 5
d5d6d7=357 is divisible by 7
d6d7d8=572 is divisible by 11
d7d8d9=728 is divisible by 13
d8d9d10=289 is divisible by 17
Find the sum of all 0 to 9 pandigital numbers with this property.*/
long long int q43() {

	long long int sum = 0;

	std::list<int> ls = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	// 10! = 3628800
	const int max = (int)factorial_helper::factorial(ls.size());

	for (int p = 1; p <= max; ++p) {
		std::string current = permutation_helper::calc_permutation(ls, p);

		// Guard against a zero at the front forming a 9 (and not 10) digit pandigit number
		if (current.front() == '0') { continue; }

		int substring = /*((current[1] - '0') * 100) + ((current[2] - '0') * 10) +*/ (current[3] - '0');
		if (substring % 2 != 0) {continue;} 
		// substring = ((current[2] - '0') * 100) + ((current[3] - '0') * 10) + (current[4] - '0');
		// Digit sum = 0 mod 3 implies divisible by 3
		substring = (current[2] - '0') + (current[3] - '0') + (current[4] - '0');
		if (substring % 3 != 0) {continue;} 
		substring = /*((current[3] - '0') * 100) + ((current[4] - '0') * 10) +*/ (current[5] - '0');
		if (substring % 5 != 0) {continue;} 
		substring = ((current[4] - '0') * 100) + ((current[5] - '0') * 10) + (current[6] - '0');
		if (substring % 7 != 0) {continue;} 
		substring = ((current[5] - '0') * 100) + ((current[6] - '0') * 10) + (current[7] - '0');
		if (substring % 11 != 0) {continue;} 
		substring = ((current[6] - '0') * 100) + ((current[7] - '0') * 10) + (current[8] - '0');
		if (substring % 13 != 0) {continue;} 
		substring = ((current[7] - '0') * 100) + ((current[8] - '0') * 10) + (current[9] - '0');
		if (substring % 17 != 0) {continue;} 

		// Found 1406357289
		// Found 1430952867
		// Found 1460357289
		// Found 4106357289
		// Found 4130952867
		// Found 4160357289
		// std::cout << "Found " << current << std::endl; 
		sum += number_helper::stringToInt(current);
	}

	// Q43. Sum of all 0 to 9 pandigital numbers with sub-string divisibility property [16695334890]
	// std::cout << "Q43. Sum of all 0 to 9 pandigital numbers with sub-string divisibility property [" << sum << "]" << std::endl;

	return sum;
}


/* Pentagonal numbers are generated by the formula, P(n)=n(3n−1)/2.
The first ten pentagonal numbers are:
1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...
It can be seen that P(4) + P(7) = 22 + 70 = 92 = P(8). However, their difference,
70 − 22 = 48, is not pentagonal. Find the pair of pentagonal numbers,
P(j) and P(k), for which their sum and difference are pentagonal and
D = |P(k) − P(j)| is minimised; what is the value of D? */
int q44() {
	pentagonal_number<int> pentagonal;

	int min_diff = 0, upper, lower;

	// upper_index incrementing upwards
	// Infinite loop - index starts from 2 as in second pentagonal term
	for (size_t upper_index = 2; true; ++upper_index) {
		// lower_index incrementing downwards from upper_index
		for (size_t lower_index = upper_index - 1; lower_index > 0; --lower_index) {

			upper = pentagonal.get_shape(upper_index);
			lower = pentagonal.get_shape(lower_index);

			if ((pentagonal.get_n(upper + lower) != -1) && (pentagonal.get_n(upper - lower) != -1)) {
				// std::cout << "Upper: value [" << upperValue << "] index [" << upperIndex << "], lower: value ["
				//	<< lowerValue << "] index [" << lowerIndex << "], sum [" << sum << "], diff [" << diff << "]" << std::endl;

				min_diff = upper - lower;
				break;
			}
		}
		if (min_diff != 0) {
			break;
		}
	}

	// Q44. The minimum difference is [5482660]
	// std::cout << "Q44. The minimum difference is [" << minDiff << "]" << std::endl;

	return min_diff;
}


/* Triangle, pentagonal, and hexagonal numbers are generated by the following formulae:
Triangle 	  	T(n)=n(n+1)/2 	  	1, 3, 6, 10, 15, ...
Pentagonal 	  	P(n)=n(3n−1)/2 	  	1, 5, 12, 22, 35, ...
Hexagonal 	  	H(n)=n(2n−1) 	  	1, 6, 15, 28, 45, ...
It can be verified that T(285) = P(165) = H(143) = 40755.
Find the next triangle number that is also pentagonal and hexagonal. */
long long int q45() {
	triangle_number<long long int> triangle;
	pentagonal_number<long long int> pentagonal;
	hexagonal_number<long long int> hexagonal;

	size_t n = 285;
	long long int tri;

	while (true) {
		++n;
		tri = triangle.get_shape(n);
		// std::cout << triangle << " ";
		if (pentagonal.is_shape(tri) && hexagonal.is_shape(tri)) {
			break;
		}
	}

	// Q45. Next triangle which is also a pentagonal and hexagonal is: [1533776805]
	// std::cout << "Q45. Next triangle which is also a pentagonal and hexagonal is: [" << triangle << "]" << std::endl;

	return tri;
}


bool is_christian_goldbach_composite(const int &target, const std::vector<int> &primes) {
	for (std::vector<int>::const_iterator it = primes.begin(); it != primes.end(); ++it) {
		for (unsigned int s = 1; true; ++s) {
			const int combination = *it + (2 * s * s);
			if (target == combination) {
				return true;
			}
			if (target < combination) {
				break; // Combinations only get bigger
			}
		}
	}
	return false;
}


/* It was proposed by Christian Goldbach that every odd composite
number can be written as the sum of a prime and twice a square.
9 = 7 + 2×1^2
15 = 7 + 2×2^2
21 = 3 + 2×3^2
25 = 7 + 2×3^2
27 = 19 + 2×2^2
33 = 31 + 2×1^2
It turns out that the conjecture was false. What is the smallest odd
composite that cannot be written as the sum of a prime and twice a square? */
int q46() {
	std::vector<int> primes;

	// By examination we have: odd composite = prime + 2 * (square)
	// Hence prime must be odd so exclude p = 2
	// primes.push_back(2);
	primes.push_back(3);

	int current = 9; // First composite odd number
	while (true) {

		// Ensure composite
		if (!prime_helper::is_prime(current)) {

			// Generate more primes if we need them
			while (primes.back() < current) {
				int next = primes.back();
				while (true) {
					next += 2;
					if (prime_helper::is_prime(next)) {
						primes.push_back(next);
						break;
					}
				}
			}

			// Find a prime and twice a square combination
			if (!is_christian_goldbach_composite(current, primes)) {
				break; // Outermost while loop
			}
		}
		current += 2;
	}

	// Q46. Could not find a prime and twice a square combination for: 5777
	// std::cout << "Q46. Could not find a prime and twice a square combination for: " << current << std::endl;

	return current;
}


/* The first two consecutive numbers to have two distinct prime factors are:
14 = 2 × 7
15 = 3 × 5
The first three consecutive numbers to have three distinct prime factors are:
644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.
Find the first four consecutive integers to have four distinct prime factors.
What is the first of these numbers?*/
int q47() {
	int current = 644 - 1; // -1 as we ++current below

	while (true) {
		++current;
		// if (current % 1000 == 0) {std::cout << "Processing: " << current << std::endl;}

		// Factors of four consecutive numbers
		std::map<int, unsigned int> fact;
		factors_helper::factorise(current, fact);

		// Each number requires four distinct prime factors
		const unsigned int factor_count = 4;
		if (fact.size() != factor_count) { continue; }

		++current;
		factors_helper::factorise(current, fact);
		if (fact.size() != factor_count) { continue; }
		
		++current;
		factors_helper::factorise(current, fact);
		if (fact.size() != factor_count) { continue; }
		
		++current;
		factors_helper::factorise(current, fact);
		if (fact.size() != factor_count) { continue; }

		break;
	}

	// Q47. The four consecutive numbers are [134043] [134044] [134045] [134046]
	// std::cout << "Q47. The four consecutive numbers are [";
	// std::cout << current << "] [" << (current + 1) << "] ["
	// std::cout << (current + 2) << "] [" << (current + 3) << "]" << std::endl;

	return current - 3; // Want first of the four consecutive numbers
}


// Multiplication by doubling which is safe even when we have a and b being 10 digit numbers 
// because we we never perform a 10 digit multiplication against another 10 digit directly.
// NB. Params a and b passed by value.
template<typename T>
T multiplication_doubling_mod(T a, T b, const T &mod) {
	T result = 0;

	a %= mod;
	b %= mod;
	while (b > 0) {
		if (b % 2) {
			result += a;
			result %= mod;
		}
		a *= 2;
		a %= mod;
		b /= 2;
	}

	return result;
}

/* The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
Find the last ten digits of the series,
1^1 + 2^2 + 3^3 + ... + 1000^1000. */
unsigned long long int q48() {
	
	const unsigned long long int _10pow10 = 10000000000, _10pow9 = 1000000000; // 10^10 and 10^9

	unsigned long long int total = 1; // Start with 1^1 already added

	for (int n = 2; n <= 1000; ++n) {

		// If n has a factor of 10 then we can skip because n^n
		// will end in at least 10 zeros and not affect the result.
		if (n % 10 == 0) {
			continue;
		}

		/* Perform exponentiation via binary expansion and repeated squaring.
		This becomes tricky when current*power results in a 20 digit number
		(or greater) as it cannot be stored in a 64-bit unsigned long long int
		which is large enough for 19 digits (and partial 20th). To overcome
		this, we employ multiplication by doubling. */
		unsigned long long int current = 1, power = n;
		int m = n;
		while (m > 0) {
			if (m % 2) {

				/* We use && and not || since both current and power are
				taken mod 10^10 and hence are at most 10 digits long. So
				we only run the threat of current*power being a 20 digit
				number when both current and power are 10 digits long. */
				if (current >= _10pow9 && power >= _10pow9) {
					current = multiplication_doubling_mod(current, power, _10pow10);
				}
				else {
					current = (current * power) % _10pow10;
				}
			}

			if (power >= _10pow9) {
				power = multiplication_doubling_mod(power, power, _10pow10);
			}
			else {
				power = (power * power) % _10pow10;
			}

			m /= 2;
		}

		// Add to the total
		total = (total + current) % _10pow10;
	}

	// Q48. The last ten digits of the total is [9110846700]
	// std::cout << "Q48. The last ten digits of the total is [" << total << "]" << std::endl;

	return total; // 9110846700
}


/* The arithmetic sequence, 1487, 4817, 8147, in which each of the
terms increases by 3330, is unusual in two ways:
(i) each of the three terms are prime, and,
(ii) each of the 4-digit numbers are permutations of one another.
There are no arithmetic sequences made up of three 1-, 2-, or 3-digit
primes, exhibiting this property, but there is one other 4-digit
increasing sequence. What 12-digit number do you form by concatenating
the three terms in this sequence? */
long long int q49() {
	const int min = 1001, max = 9999; // Require 4 digit numbers

	long long int concat_number = 0;

	for (int base = min; true; base += 2) {
		// Must be prime
		if (!prime_helper::is_prime(base)) {continue;}

		// Must be at least two numbers after base
		for (int step = 2; step <= (max - base) / 2; step += 2) {

			// Must be prime
			if (!prime_helper::is_prime(base + step) ||
				!prime_helper::is_prime(base + (2 * step))) {continue;}

			// Must be permutation
			if (!permutation_helper::is_permutation(base, base + step) ||
				!permutation_helper::is_permutation(base, base + (2 * step))) {continue;}

			// Found: 1487 4817 8147
			// Found: 2969 6299 9629
			// std::cout << "Found: " << base << " " << (base + step) << " " << (base + (2 * step)) << std::endl;
			if (base != 1487) {
				concat_number = base;
				concat_number *= 10000;
				concat_number += base + step;
				concat_number *= 10000;
				concat_number += base + (2 * step);
				break;
			}
		}
		if (concat_number != 0) {
			break;
		}
	}

	// Q49. The concatenated number is: 296962999629
	// std::cout << "Q49. The concatenated number is: " << concatNumber << std::endl;

	return concat_number;
}


/* The prime 41, can be written as the sum of six consecutive primes:
41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime
below one-hundred. The longest sum of consecutive primes below
one-thousand that adds to a prime, contains 21 terms, and is equal to 953.
Which prime, below one-million, can be written as the sum of the most
consecutive primes? */
int q50() {
	const int limit = 999999;

	// Vector storing primes below 'limit'
	std::vector<int> primes;
	primes.push_back(2); // Add only even prime
	int next = 3;
	while (next < limit) {
		if (prime_helper::is_prime(next)) {
			primes.push_back(next);
		}
		next += 2; // Remain odd to be possible prime
	}

	size_t largest_count = 0;
	int largest_sum = 0;

	// Recall the objective is to the find the prime that can be written
	// as the sum of the most consecutive primes. NOT find the largest
	// prime that can be written as consecutive primes. As such we start
	// using smaller primes first to avoid going over the limit.
	for (std::vector<int>::const_iterator it_i = primes.begin(); it_i != primes.end(); ++it_i) { // Starting prime
		int sum = 0;

		for (std::vector<int>::const_iterator it_j = it_i; it_j != primes.end(); ++it_j) {
			sum += *it_j;
			if (sum > limit) {break;} // Sum exceeds limit

			if (prime_helper::is_prime(sum)) {

				// std::cout << "Consecutive primes count [" << count << "] starting prime [" << i << "] prime sum [" << sum << "]" << std::endl;
				if ((size_t)(it_j - it_i) > largest_count) {
					largest_count = (it_j - it_i);
					largest_sum = sum;
				}
			}
		}
	}

	// Q50. Largest consecutive primes count [543] starting prime [3] prime sum [997651]
	// std::cout << "Q50. Largest consecutive primes count [" << largestCount << "] starting prime [" << largestStart << "] prime sum [" << largestSum << "]" << endl;

	return largest_sum;
}
