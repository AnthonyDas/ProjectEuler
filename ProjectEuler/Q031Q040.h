#include <iostream> 
#include <vector> 
#include <cmath> // pow
#include <set>

#include "prime_helper.h" 
#include "factorial_helper.h"
#include "pan_digit_helper.h" 
#include "base_helper.h" 
#include "palindrome_helper.h" 
#include "number_helper.h"
#include "right_angle_triangle_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


/*int recursive_coins_ways(const int &remaining, const int *coins, const int &current_coin) {
	// If we have reached the target or we only have 1p coin option left, we have found another way
	if (remaining == 0 || current_coin == 0) {
		return 1;
	}

	// Create a cache
	static std::vector<int> row(current_coin, 0);
	static std::vector<std::vector<int> > cache(remaining, row);
	if (cache[remaining - 1][current_coin - 1] != 0) {
		return cache[remaining - 1][current_coin - 1];
	}

	int ways = 0, limit = remaining / coins[current_coin];

	for (int i = 0; i <= limit; ++i) {
		ways += recursive_coins_ways(remaining - (i * coins[current_coin]), coins, (current_coin - 1));
	}

	cache[remaining - 1][current_coin - 1] = ways;

	return ways;
}*/

/* In England the currency is made up of pound, £, and pence, p,
and there are eight coins in general circulation:
1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
It is possible to make £2 in the following way:
1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins? */
int q31() {
	// See overview for this problem on Project Euler:
	// https://projecteuler.net/overview=031

	const std::vector<int> coins = { 1, 2, 5, 10, 20, 50, 100, 200 }; // 8 coin options

	const int target = 200;

	// Cache - row index is the target amount, column index corresponds to largest available coin
	std::vector<int> row(coins.size(), 0);
	std::vector<std::vector<int> > ways(target + 1, row); // NB +1
	
	for (int j = 0; j < (int)coins.size(); ++j) { // Largest coin available, coins[j]
		for (int i = 0; i <= target; ++i) { // i = target
			// 1 way to reach a target of 0 regardless of what coins are available
			if (i == 0) {
				ways[i][j] = 1;
				continue;
			}

			// Need to find ways to make target (i + 1) with largest coin available being coin[j].
			// Either: We use zero of the largest coin available and move onto the next largest coin
			// Or: We use a single of the current coin
			ways[i][j] = (j > 0 ? ways[i][j - 1] : 0) + (i >= coins[j] ? ways[i - coins[j]][j] : 0);
		}
	}

	// Q31. Ways 2 pounds can be made using any number of coins [73682]
	//std::cout << "Q31. Ways 2 pounds can be made using any number of coins [" << ways << "]" << endl;

	return ways[target][coins.size() - 1];
}


/* We shall say that an n-digit number is pandigital if it makes use of
all the digits 1 to n exactly once; for example, the 5-digit number, 15234,
is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing
multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity
can be written as a 1 through 9 pandigital.
HINT: Some products can be obtained in more than one way so be sure to only
include it once in your sum.*/
int q32() {
	std::set<int> products;

	// Working out the limit: Consider the multiplicand,
	// if this is 4 digits then the product will also be
	// at least 4 digits and the multiplier will be at least
	// 1 digit. This gives a total of at least 9 digits.
	const int limit = 10000;
	for (int a = 1; a < limit; ++a) {

		// b >= a otherwise we'll duplicate processing
		for (int b = a; b < limit; ++b) {
			int p = a * b;

			int digits_a = number_helper::digits_count(a);
			int digits_b = number_helper::digits_count(b);
			int digits_p = number_helper::digits_count(p);
			int total_digits = digits_a + digits_b + digits_p;
			if (total_digits < 9) {
				continue;
			}
			if (total_digits > 9) {
				break;
			}

			int combined = number_helper::concat(a, b);
			combined = number_helper::concat(combined, p);

			if (pan_digit_helper::is_pan_digit(combined)) {
				// Found [4], [1738] product [6952] combined [695217384]
				// Found [4], [1963] product [7852] combined [785219634]
				// Found [12], [483] product [5796] combined [579648312]
				// Found [18], [297] product [5346] combined [534629718]
				// Found [27], [198] product [5346] combined [534619827]
				// Found [28], [157] product [4396] combined [439615728]
				// Found [39], [186] product [7254] combined [725418639]
				// Found [42], [138] product [5796] combined [579613842]
				// Found [48], [159] product [7632] combined [763215948]
				// cout << "Found [" << multiplicand << "], [" << multiplier << "] product [" << product << "] combined [" << combined << "]" << endl; 
				products.insert(p);
			}
		}
	}

	int sum = 0;
	for (std::set<int>::iterator it = products.begin(); it != products.end(); ++it) {
		sum += *it;
	}

	// Q32. The sum of the products is [45228]
	// std::cout << "Q32. The sum of the products is [" << sum << "]" << endl;

	return sum;
}


/* The fraction 49/98 is a curious fraction, as an inexperienced mathematician
in attempting to simplify it may incorrectly believe that 49/98 = 4/8,
which is correct, is obtained by cancelling the 9s. We shall consider fractions
like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than
one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms,
find the value of the denominator. */
int q33() {
	std::vector<fraction<int> > res_vec; // Storage for the special fractions

	for (int num = 10; num < 100; ++num) {
		for (int den = (num + 1); den < 100; ++den) { // Fraction must be less than 1

			// Exclude trivial examples
			if (num % 10 == 0 && den % 10 == 0) { continue; }

			// fraction class will reduce the numerator and denominator
			// automatically TO THE SIMPLEST REPRESENTATION,
			// eg. 49/98 = 1/2, and not 49/98 = 4/8.
			fraction<int> current(num, den);

			// Check reduction occurred - if not, fraction is already in simplest form
			if (current.get_num() == num) {continue;}

			int num_units, num_tens, den_units, den_tens;
			num_units = num % 10;
			num_tens = num / 10;
			den_units = den % 10;
			den_tens = den / 10;

			// Need a digit to be repeated within the numerator and denominator.
			// Beware there may be more than one, eg. 11/17 has two 1s in the numerator.
			// Also 27/72 has two different repeated digits.
			std::set<int> repeated_digits;
			if (num_units == den_units || num_units == den_tens) {
				repeated_digits.insert(num_units);
			}
			if ((num_units != num_tens) && (num_tens == den_units || num_tens == den_tens)) {
				repeated_digits.insert(num_tens);
			}
			// Check we have a repeated digit
			if (repeated_digits.empty()) { continue; }

			for (std::set<int>::iterator it = repeated_digits.begin(); it != repeated_digits.end(); ++it) {
				// Work out the reduced numerator and reduced denominator
				int reduced_num = *it == num_units ? num_tens : num_units;
				int reduced_den = *it == den_units ? den_tens : den_units;
				
				if (reduced_num == 0 || reduced_den == 0) { continue; } // Can't have zero numerator or denominator

				fraction<int> reduced(reduced_num, reduced_den);
				if (reduced == current) {
					// Numerator [16] Denominator [64] - Fraction [1/4]
					// Numerator [19] Denominator [95] - Fraction [1/5]
					// Numerator [26] Denominator [65] - Fraction [2/5]
					// Numerator [49] Denominator [98] - Fraction [1/2]
					// std::cout << "Numerator [" << num << "] Denominator [" << den << "] - Fraction [" << current << "]" << std::endl;
					res_vec.push_back(current);
				}
			}
		}
	}

	fraction<int> product(1, 1);
	for (std::vector<fraction<int> >::iterator it = res_vec.begin(); it != res_vec.end(); ++it) {
		product *= (*it);
	}

	// Q33. [4] special fractions with product [1/100], denominator [100]
	// std::cout << "Q33. [" << vec.size() << "] special fractions with product [" << product << "], denominator [" << product.get_den() << "]" << endl;

	return product.get_den();
}


/* 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
Find the sum of all numbers which are equal to the sum of the factorial of their digits.
Note: as 1! = 1 and 2! = 2 are not sums they are not included. */
int q34() {
	// 9! = 362880 a six digit number. Hence the largest digit
	// factorial sum for an 8 digit number, corresponding to
	// (99,999,999), is only (2,903,040) which is only 7 digits.
	// Hence we only need to consider up to 7 digit numbers.
	const int limit = 7 * 362'880;

	std::vector<int> factorials = factorial_helper::factorials(9);

	int total = 0;
	for (int n = 10; n <= limit; ++n) { // Begin at 10 as we need a sum
		// if (n % 1000000 == 0) {cout << "Iteration: " << n << endl;}

		int fact_sum = 0, remaining_digits = n;
		while (remaining_digits != 0) {
			int digit = remaining_digits % 10;
			remaining_digits /= 10;
			fact_sum += factorials[digit];
		}

		if (fact_sum == n) {
			// cout << "Found: " << n << " " << factSum << endl;
			total += n;
		}
	}

	// Q34. Sum of all numbers which are equal to their digit factorial sum [40730]
	// std::cout << "Q34. Sum of all numbers which are equal to their digit factorial sum [" << total << "]" << endl;

	return total;
}


/*The number, 197, is called a circular prime because all rotations
of the digits: 197, 971, and 719, are themselves prime.
There are thirteen such primes below 100:
2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
How many circular primes are there below one million?*/
int q35() {
	int limit = 1000000, count = 13; // Count already includes 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97

	for (int i = 101; i < limit; i += 2) {
		if (prime_helper::is_prime(i)) {
			int rotation = i;
			while (true) {
				int digit = rotation % 10;
				rotation = rotation / 10;
				rotation = digit * (int)pow(10, ceil(log10(rotation + 1))) + rotation;

				// Have we checked all roations already?
				if (rotation == i) {
					++count;
					break;
				}
				if (!prime_helper::is_prime(rotation)) {
					break;
				}
			}
		}
	}

	// Q35. Circular primes below one million [55]
	// std::cout << "Q35. Circular primes below one million [" << count << "]" << endl;

	return count;
}


/* The decimal number, 585 = 1001001001_2 (binary), is palindromic
in both bases. Find the sum of all numbers, less than one million,
which are palindromic in base 10 and base 2. (Please note that the
palindromic number, in either base, may not include leading zeros.) */
int q36() {
	int sum = 0;

	for (int i = 1; i < 1'000'000; ++i) {
		if (palindrome_helper::is_palindrome(i)) {
			std::vector<int> binary = base_helper::convert_decimal_to_base(i, 2);

			if (palindrome_helper::is_palindrome(binary)) {
				// std::cout << "Found [" << i << "] base 10, [" << baseTwo << "] base 2" << endl;
				sum += i;
			}
		}
	}

	// Q36. The sum of all double base (2 and 10) palindromes [872187]
	// std::cout << "Q36. The sum of all double base (2 and 10) palindromes [" << sum << "]" << endl;

	return sum;
}


/* The number 3797 has an interesting property. Being prime itself, it is
possible to continuously remove digits from left to right, and remain prime
at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left:
3797, 379, 37, and 3. Find the sum of the only eleven primes that are both
truncatable from left to right and right to left.
NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes. */
long long int q37() {
	long long int n = 11, sum = 0;
	int count = 0;

	while (count < 11) {
		if (prime_helper::is_prime(n)) {
			bool all_prime = true;
			
			long long int right = n;
			while (right > 9) {
				right /= 10;
				if (!prime_helper::is_prime(right)) {
					all_prime = false;
					break;
				}
			}

			if (all_prime) {
				long long int left = n;
				while (left > 9) {
					left %= (long long int)pow(10, number_helper::digits_count(left) - 1);
					if (!prime_helper::is_prime(left)) {
						all_prime = false;
						break;
					}
				}
			}
			if (all_prime) {
				++count;
				sum += n;
			    //Found: 23 23
				//Found : 37 60
				//Found : 53 113
				//Found : 73 186
				//Found : 313 499
				//Found : 317 816
				//Found : 373 1189
				//Found : 797 1986
				//Found : 3137 5123
				//Found : 3797 8920
				//Found : 739397 748317
				//std::cout << "Found: " << n << " " << sum << std::endl;
			}
		}
		n += 2; // Remain odd to be prime
	}
	// Q37. Sum of truncatable primes [748317]
	// std::cout << "Q37. Sum of truncatable primes [" << sum << "]" << endl;

	return sum;
}


/* Take the number 192 and multiply it by each of 1, 2, and 3:
192 × 1 = 192
192 × 2 = 384
192 × 3 = 576
By concatenating each product we get the 1 to 9 pandigital, 192384576.
We will call 192384576 the concatenated product of 192 and (1,2,3)
The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5,
giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).
What is the largest 1 to 9 pandigital 9-digit number that can be formed as
the concatenated product of an integer with (1,2, ... , n) where n > 1? */
long long int q38() {
	const int limit = 10000; // Must have n >= 2 hence base cannot be greater than 4 digits
	long long int largest = 0;

	for (int base = 1; base < limit; ++base) {
		long long int concat_prod = 0;
		
		for (int n = 1; n < 10; ++n) {
			concat_prod = concat_prod * (long long int)pow(10, ceil(log10((base * n) + 1))) + (base * n);

			long long int digits = number_helper::digits_count(concat_prod);
			if (digits == 9) {
				if (pan_digit_helper::is_pan_digit(concat_prod)) {
					largest = concat_prod;
					break;
				}
			}
			else if (digits > 9) {
				break;
			}
		}
	}

	return largest;
}


/* If p is the perimeter of a right angle triangle with integral length sides,
{a,b,c}, there are exactly three solutions for p = 120.
{20,48,52}, {24,45,51}, {30,40,50}
For which value of p ≤ 1000, is the number of solutions maximised? */
int q39() {
	const int limit = 1000; // Perimeter length

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

	int max_count = 0, max_p = 0;
	for (int i = 0; i < (int)triangle.size(); ++i) {
		if (max_count < triangle[i]) {
			max_count = triangle[i];
			max_p = (i + 1);
		}
	}

	// Q39. Perimeter length [840] maximises integer solutions [8]
	// std::cout << "Q39. Perimeter length [" << maxp << "] maximises integer solutions [" << maxcount << "]" << endl;

	return max_p; // 840
}


/* Champernowne's constant
An irrational decimal fraction is created by concatenating the positive integers:
0.123456789101112131415161718192021...
It can be seen that the 12th digit of the fractional part is 1. If d(n) represents
the nth digit of the fractional part, find the value of the following expression.
d(1) × d(10) × d(100) × d(1000) × d(10000) × d(100000) × d(1000000) */
int q40() {
	std::vector<int> decimal, temp; // temp is used to reverse the digits of the next added number
	int n = 0, part;

	while (decimal.size() < 1000000) {
		++n;
		part = n;
		temp.clear();
		while (part != 0) {
			temp.push_back(part % 10);
			part /= 10;
		}

		for (std::vector<int>::reverse_iterator rit = temp.rbegin(); rit != temp.rend(); ++rit) {
			decimal.push_back(*rit);
		}
	}

	int product = 1;
	for (int i = 0; i < 7; ++i) {
		int n = (int)pow(10, i);
		// std::cout << decimal[n - 1] << " ";
		product *= decimal[n - 1];
	}

	// Q40. Product of required decimal digits [210]
	// std::cout << "Q40. Product of required decimal digits [" << product << "]" << endl;

	return product;
}
