#include <iostream>
#include <vector>

//#include "base_helper.h"
//#include "ifstream_with_path.h"
//#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*Some positive integers n have the property that the sum [ n + reverse(n) ] consists entirely
of odd (decimal) digits. For instance, 36 + 63 = 99 and 409 + 904 = 1313. We will call such numbers
reversible; so 36, 63, 409, and 904 are reversible. Leading zeroes are not allowed in either n
or reverse(n).
There are 120 reversible numbers below one-thousand.
How many reversible numbers are there below one-billion (10^9)?*/
int q145() {
	const long long int limit = 1000000000;
	int count = 0;
	
	for (long long int i = 1; i < limit; ++i) {
		// if (i % 1000000 == 0) { std::cout << i << std::endl; }

		long long int carry = i, rev = 0;
		while (carry > 0) {
			rev = (rev * 10) + (carry % 10);
			carry /= 10;
		}

		if (rev < i) {
			continue; // Already considered
		}

		long long int sum = i + rev;
		bool all_odd_digits = true;

		while (sum > 0) {
			if (sum % 2 == 0) {
				all_odd_digits = false;
				break;
			}
			sum /= 10;
		}

		if (all_odd_digits) {
			count += 2; // Plus two because we count abcd and reverse dcba
			// std::cout << count << " " << i << " " << rev << std::endl;
		}
	}

	return count;
}
