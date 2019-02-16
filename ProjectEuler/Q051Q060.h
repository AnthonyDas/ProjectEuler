#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "palindrome_helper.h" 
#include "prime_helper.h"
#include "ifstream_with_path.h"
#include "combinatorics_helper.h"
#include "poker_hand.h"
#include "vector_int.h"
#include "number_helper.h" 

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


/* By replacing the 1st digit of the 2-digit number *3, it turns
out that six of the nine possible values: 13, 23, 43, 53, 73, and 83,
are all prime. By replacing the 3rd and 4th digits of 56**3 with the
same digit, this 5-digit number is the first example having seven primes
among the ten generated numbers, yielding the family: 56003, 56113, 56333,
56443, 56663, 56773, and 56993. Consequently 56003, being the first member
of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not
necessarily adjacent digits) with the same digit, is part of an eight
prime value family. */
int q51() {
	int n = 56003;
	std::vector<int> primes;

	while (primes.size() != 8) {
		n += 2; // Remain odd for prime

		if (prime_helper::is_prime(n)) {

			std::map<int, unsigned int> digit_map = number_helper::get_digit_map(n);

			for (std::map<int, unsigned int>::const_iterator it = digit_map.begin(); it != digit_map.end(); ++it) {
				primes.clear();
				primes.push_back(n);


				// Need to look both ways and not just for higher replacement values.
				// From the example given, consider starting at 56333. We would replace ALL 3s
				// and wouldn't generate 56443, 56663, 56773, and 56993. Hence, when we come onto
				// prime 56443 later on, we must consider switching the 4s with 3s etc.
				for (int replace_digit = 0; replace_digit < 10; ++replace_digit) {
					if (replace_digit == it->first) { continue; } // replace_digit not different

					int  trial = 0, remain = n, digit, power = 1;

					// Replace digits
					while (remain > 0) {
						digit = remain % 10;
						if (digit == it->first) {
							digit = replace_digit;
						}
						remain /= 10;
						trial = trial + (digit * power);
						power *= 10;
					}

					// Guard against trial having fewer digits, i.e. can't replace leading zeros.
					// E.g. Consider primes 857, 111857, 222857, 333857, 555857, 666857, 777857, 888857
					if (prime_helper::is_prime(trial) && number_helper::digits_count(trial) == number_helper::digits_count(n)) {
						// 121313 1 2 222323
						// 121313 1 3 323333
						// 121313 1 4 424343
						// 121313 1 5 525353
						// 121313 1 6 626363
						// 121313 1 8 828383
						// 121313 1 9 929393
						// std::cout << n << " " << it->first << " " << replace_digit << " " << trial << std::endl;
						primes.push_back(trial);
						if (primes.size() == 8) {
							break;
						}
					}
				}
				if (primes.size() == 8) {
					break;
				}
			}
			// std::cout << "Prime [" << n << "] count [" << count << "]" << std::endl;
		}
	}

	// Q51. The smallest prime part of an eight prime value family is [121313]
	// std::cout << "Q51. The smallest prime part of an eight prime value family is [" << primes.front() << "]" << std::endl;

	return primes.front();
}


/* It can be seen that the number, 125874, and its double,
251748, contain exactly the same digits, but in a different order.
Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
contain the same digits. */
int q52() {
	int x = 0;

	// We need x, 2x, 3x, 4x, 5x, and 6x to all contain the same digits.
	// This implies they should all have the same digit sum.

	// Now consider that the digit sum of x is equivalent to x mod 9,
	// which must be equivalent to 2x mod 9, 3x mod 9,..., and 6x mod 9.
	// It should be clear that x must be equivalent to 0 mod 9, otherwise
	// x, 2x, 3x, 4x, 5x, and 6x will not all be equivalent under mod 9.
	// Hence we can start iterating at i = 9 with increment of 9. 
	
	int i = 0;
	while (true) { // Infinite loop
		i += 9;

		std::map<int, unsigned int> map_1 = number_helper::get_digit_map(i);
		
		bool perm = true;

		for (int j = 2; j <= 6; ++j) {
			std::map<int, unsigned int> map_2 = number_helper::get_digit_map(j * i);

			if (map_1 != map_2) {
				perm = false;
				break;
			}
		}

		if (perm) {
			x = i;
			break;
		}
	}

	// Q52. The base value is [142857]
	// std::cout << "Q52. The base value is [" << x << "]" << std::endl;

	return x;
}


/* There are exactly ten ways of selecting three from five, 12345:
123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
In combinatorics, we use the notation, 5C3 = 10.
In general, nCr = n! / r!(n−r)!, where r ≤ n, n! = n×(n−1)×...×3×2×1, and 0! = 1.
It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100,
are greater than one-million? */
int q53() {
	const int million = 1000000;
	int count = 0;

	for (unsigned int n = 1; n <= 100; ++n) {
		count += combinatorics_helper::combinations_greater_than(n, million);
	}

	// Q53. Number of nCr, for 1 <= n <= 100, that are greater than one-million [4075]
	// std::cout << "Q53. Number of nCr, for 1 <= n <= 100, that are greater than one-million [" << count << "]" << std::endl;

	return count;
}


/* In the card game poker, a hand consists of five cards and are
ranked, from lowest to highest, in the following way:

High Card: Highest value card.
One Pair: Two cards of the same value.
Two Pairs: Two different pairs.
Three of a Kind: Three cards of the same value.
Straight: All cards are consecutive values.
Flush: All cards of the same suit.
Full House: Three of a kind and a pair.
Four of a Kind: Four cards of the same value.
Straight Flush: All cards are consecutive values of same suit.
Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.

The cards are valued in the order:
2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

If two players have the same ranked hands then the rank made up of
the highest value wins; for example, a pair of eights beats a pair
of fives (see example 1 below). But if two ranks tie, for example,
both players have a pair of queens, then highest cards in each hand
are compared (see example 4 below); if the highest cards tie then
the next highest cards are compared, and so on.

Consider the following five hands dealt to two players:
Hand	 	Player 1	 	Player 2	 	Winner
1	 	5H 5C 6S 7S KD	 	2C 3S 8S 8D TD  Player 2
Pair of Fives       Pair of Eights

2	 	5D 8C 9S JS AC	 	2C 5C 7D 8S QH  Player 1
Highest card Ace    Highest card Queen

3	 	2D 9C AS AH AC	    3D 6D 7D TD QD  Player 2
Three Aces          Flush with Diamonds

4	 	4D 6S 9H QH QC      3D 6D 7H QD QS  Player 1
Pair of Queens      Pair of Queens
Highest card Nine   Highest card Seven

5	 	2H 2D 4C 4D 4S	 	3C 3D 3S 9S 9D	Player 1
Full House          Full House
With Three Fours    with Three Threes

The file, poker.txt, contains one-thousand random hands dealt to two
players. Each line of the file contains ten cards (separated by a
single space): the first five are Player 1's cards and the last five
are Player 2's cards. You can assume that all hands are valid (no
invalid characters or repeated cards), each player's hand is in no
specific order, and in each hand there is a clear winner.

How many hands does Player 1 win? */
int q54() {

	ifstream_with_path fin("Problem54.txt");

	std::vector<std::string> cards; // Store all the cards for both players in order
	std::string nextCard;
	while (fin >> nextCard) {
		cards.push_back(nextCard);
	}
	fin.close();

	int player_1_wins = 0;
	for (std::vector<std::string>::const_iterator it = cards.begin(); it != cards.end(); it += 10) { // Ten cards per deal
		poker_hand player_1(*it, *(it + 1), *(it + 2), *(it + 3), *(it + 4));
		poker_hand player_2(*(it + 5), *(it + 6), *(it + 7), *(it + 8), *(it + 9));

		// Should never obtain a draw - we are given that there is always a clear winner
		// std::cout << player_1 << " " << player_2 << " " << player_1.is_winner(player_2) << std::endl;
		if (player_1.is_winner(player_2)) {
			++player_1_wins;
		}

	}

	// Q54. Player 1 wins [376] poker hands out of [1000]
	// std::cout << "Q54. Player 1 wins [" << player1Wins << "] poker hands out of [" << hands << "]" << std::endl;

	return player_1_wins;
}


/* If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
Not all numbers produce palindromes so quickly. For example,
349 + 943 = 1292,
1292 + 2921 = 4213
4213 + 3124 = 7337
That is, 349 took three iterations to arrive at a palindrome.
Although no one has proved it yet, it is thought that some numbers,
like 196, never produce a palindrome. A number that never forms a palindrome
through the reverse and add process is called a Lychrel number. Due to the
theoretical nature of these numbers, and for the purpose of this problem,
we shall assume that a number is Lychrel until proven otherwise. In addition
you are given that for every number below ten-thousand, it will either (i)
become a palindrome in less than fifty iterations, or, (ii) no one, with all
the computing power that exists, has managed so far to map it to a palindrome.
In fact, 10677 is the first number to be shown to require over fifty iterations
before producing a palindrome: 4668731596684224866951378664 (53 iterations, 28-digits).

Surprisingly, there are palindromic numbers that are themselves Lychrel numbers;
the first example is 4994.

How many Lychrel numbers are there below ten-thousand?

NOTE: Wording was modified slightly on 24 April 2007 to emphasise the theoretical
nature of Lychrel numbers. */
int q55() {
	const int limit = 10000;
	int non_lychrel_count = 0;

	for (int i = 1; i < limit; ++i) {
		long long int current(i);

		// Try to obtain a palindrome in 50 iterations
		for (int j = 0; j < 50; ++j) {
			current += number_helper::reverse(current);

			if (palindrome_helper::is_palindrome(current)) {
				++non_lychrel_count;
				break;
			}
		}
	}

	// Q55. The number of lychrel numbers below 10000 is [249]
	// std::cout << "Q55. The number of lychrel numbers below 10000 is [" << lychrelCount << "]" << std::endl;

	return (limit - 1) - non_lychrel_count;
}


/* A googol (10^100) is a massive number: one followed by one-hundred zeros;
100^100 is almost unimaginably large: one followed by two-hundred zeros.
Despite their size, the sum of the digits in each number is only 1.
Considering natural numbers of the form, a^b, where a, b < 100,
what is the maximum digital sum? */
int q56() {
	int max_sum = 0, limit = 100;

	for (int a = 2; a < limit; ++a) {
		vector_int current(a);
		for (int b = 2; b < limit; ++b) {
			current *= a;
			int sum = current.digit_sum();
			if (sum > max_sum) {
				max_sum = sum;
				//  std::cout << "Max digit sum [" << maxsum << "] a [" << maxa << "] b [" << maxb << "]" <<  std::endl;
			}
		}
	}

	// Q56. Max digit sum [972] a [99] b [95]
	// std::cout << "Q56. Max digit sum [" << maxsum << "] a [" << maxa << "] b [" << maxb << "]" << std::endl;

	return max_sum;
}


/* It is possible to show that the square root of two can
be expressed as an infinite continued fraction.
√ 2 = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...
By expanding this for the first four iterations, we get:
1 + 1/2 = 3/2 = 1.5
1 + 1/(2 + 1/2) = 7/5 = 1.4
1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...
The next three expansions are 99/70, 239/169, and 577/408,
but the eighth expansion, 1393/985, is the first example where
the number of digits in the numerator exceeds the number of digits
in the denominator. In the first one-thousand expansions, how many 
fractions contain a numerator with more digits than denominator? */
int q57() {
	// Firstly, considering just the infinite fraction part, it can be seen
	// that given current fraction f(num_n / dec_n), the next term in the
	// expansion is given by f(1 / (2 + (num_n / dec_n))), which can be simplified
	// by multiplying both top and botton by dec_n to give f(dec_n, 2 * dec_n + num_n).
	// Hence we have the relationships: num_(n+1) = dec_n and dec_(n+1) = 2 * dec_n + num_n.

	vector_int inf_num(1), inf_den(2);

	int count = 0;
	for (int i = 0; i < 1000; ++i) {
		vector_int full_num(inf_num + inf_den); // +1
		
		if (full_num.size() > inf_den.size()) {
			++count;
		}

		vector_int inf_num_sav(inf_num);
		inf_num = inf_den;
		// Need (inf_den * 2) and not (2 * inf_den) to call the * operator on vector_int
		inf_den = (inf_den * 2) + inf_num_sav;
	}

	// std::cout << "Q57. There are [" << count << "] fractions whose numerator contains more digits than their denominator" << std::endl;

	return count;
}


/* Starting with 1 and spiralling anticlockwise in the following way,
a square spiral with side length 7 is formed.
37 36 35 34 33 32 31
38 17 16 15 14 13 30
39 18  5  4  3 12 29
40 19  6  1  2 11 28
41 20  7  8  9 10 27
42 21 22 23 24 25 26
43 44 45 46 47 48 49
It is interesting to note that the odd squares lie along the bottom
right diagonal, but what is more interesting is that 8 out of the 13
numbers lying along both diagonals are prime; that is, a ratio of 8/13 ≈ 62%.

If one complete new layer is wrapped around the spiral above, a square
spiral with side length 9 will be formed. If this process is continued,
what is the side length of the square spiral for which the ratio of
primes along both diagonals first falls below 10%? */
long long int q58() {
	// This is similar to Q28
	long long int next = 1, step = 2, count = 1, prime_count = 0, side_length = 1;

	for (int j = 1; true; ++j) { // Infinite loop

		long long int next_sav = next; // Overflow test

		for (int i = 0; i < 4; ++i) { // Each of the 4 diagonal entries
			next += step;
			if (prime_helper::is_prime(next)) {
				++prime_count;
			}
		}

		if (next < next_sav) {
			std::cout << "Overflow next " << next << " " << next_sav << " " << step << std::endl;
		}

		count += 4;

		side_length = 1 + (2 * j);

		// Work out ratio for the size of grid just completed
		// if ((prime_count / count) < percent) {
		if ((prime_count * 100) < (10 * count)) {
			break;
		}

		step += 2; // Step increases by 2 in next ring 
	}

	// Q58. Side length ofsquare spiral for primes ratio along both diagonals first below 10% [26241]
	// std::cout << "Q58. Side length ofsquare spiral for primes ratio along both diagonals first below 10% [" << sideLength << "]" << std::endl;

	return side_length;
}


/* Each character on a computer is assigned a unique code and the preferred standard
is ASCII (American Standard Code for Information Interchange). For example,
uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR
each byte with a given value, taken from a secret key. The advantage with the XOR function
is that using the same encryption key on the cipher text, restores the plain text;
for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain text message, and the
key is made up of random bytes. The user would keep the encrypted message and the encryption
key in different locations, and without both "halves", it is impossible to decrypt the message.

Unfortunately, this method is impractical for most users, so the modified method is to use a
password as a key. If the password is shorter than the message, which is likely, the key is
repeated cyclically throughout the message. The balance for this method is using a sufficiently
long password key for security, but short enough to be memorable.

Your task has been made easy, as the encryption key consists of three lower case characters.
Using cipher1.txt (right click and 'Save Link/Target As...'), a file containing the encrypted
ASCII codes, and the knowledge that the plain text must contain common English words, decrypt
the message and find the sum of the ASCII values in the original text. */
// http://www.cplusplus.com/articles/36A0RXSz/
int q59() {

	ifstream_with_path fin("Problem59.txt");

	std::vector<int> encrypted;
	int next;
	while (fin >> next) {
		encrypted.push_back(next);
	}
	fin.close();

	std::vector<int> ascii_totals; // Assume there may be multiple possible decryptions

	// Encryption key consists of three lower case characters
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < 26; ++j) {
			for (int k = 0; k < 26; ++k) {

				// Create a decryption key
				std::string key, decrypted;
				key.push_back((char)('a' + i));
				key.push_back((char)('a' + j));
				key.push_back((char)('a' + k));

				int ascii_total = 0;

				for (std::vector<int>::const_iterator it = encrypted.begin(); it != encrypted.end(); ++it) {
					// Detection of any of these chars will fail a decryption attempt
					static std::string failure_chars("#/\\{}`~%");

					// Decrypt the next ASCII number to produce a char
					// Note the use of XOR ^ (bitwise exclusive OR) operator being used upon two ints
					char next = char(*it ^ (int)key[(it - encrypted.begin()) % 3]);
					if (failure_chars.find(next) != std::string::npos) { // npos = -1 means not found
						break;
					}
					ascii_total += (int)next;
					decrypted.push_back(next);
				}

				if (encrypted.size() == decrypted.size()) {
					// std::cout << decrypted << std::endl;
					ascii_totals.push_back(ascii_total);
				}
				// We allow the function to continue assuming there may be multiple possible decryptions
			}
		}
	}

	// Q59. The ASCII total is [107359]
	// std::cout << "Q59. The ASCII total is [" << asciiTotals[0] << "]" << std::endl;

	return ascii_totals.front();
}


/* The primes 3, 7, 109, and 673, are quite remarkable. By taking any
two primes and concatenating them in any order the result will always
be prime. For example, taking 7 and 109, both 7109 and 1097 are prime.
The sum of these four primes, 792, represents the lowest sum for a set
of four primes with this property.

Find the lowest sum for a set of five primes for which any two primes
concatenate to produce another prime. */
int q60() {
	const int required_set_size = 5;

	// Sets of primes, such that any two elements in the set, A and B, can be concated as AB and BA to form two new primes
	std::vector<std::set<int> > concatable_primes, temp;

	// Discard prime = 2 since any multi digit no. ending in 2 is even and thus non-prime
	int n = 1, sum = 0;

	while (sum == 0) {
		n += 2;
		if (!prime_helper::is_prime(n)) {
			continue;
		}

		// Decide whether new prime is concatable with any existing set of primes
		if (!concatable_primes.empty()) {
			for (std::vector<std::set<int> >::iterator it_i = concatable_primes.begin(); it_i != concatable_primes.end(); ++it_i) {
				bool all_concat_primes = true;
				for (std::set<int>::iterator it_j = it_i->begin(); it_j != it_i->end(); ++it_j) {
					if (!prime_helper::is_prime(number_helper::concat(*it_j, n)) || !prime_helper::is_prime(number_helper::concat(n, *it_j))) {
						all_concat_primes = false;
						break;
					}
				}
				// Replicate and insert the enlarged set
				if (all_concat_primes) {
					std::set<int> new_set(*it_i);
					new_set.insert(n);

					// Check whether any set has 8 elements
					if (new_set.size() == required_set_size) {
						for (std::set<int>::iterator it = new_set.begin(); it != new_set.end(); ++it) {
							// std::cout << *it_j << std::endl;
							sum += *it;
						}
						break;
					}

					// Can't push_back direct into concatable_primes due to iterator validity
					temp.push_back(new_set);
				}
			}
		}

		if (!temp.empty()) {
			concatable_primes.insert(concatable_primes.begin(), temp.begin(), temp.end());
			temp.clear();
		}

		// Only push_back after checking whether concatable with existing
		// sets of primes as can't be concated with itself
		std::set<int> new_set;
		new_set.insert(n);
		concatable_primes.push_back(new_set);
	}

	// Q60. The sum of the [5] concatable primes is [26033]
	// std::cout << "Q60. The sum of the [" << requiredPrimesInConcatSet << "] concatable primes is [" << sum << "]" << std::endl;

	return sum;
}