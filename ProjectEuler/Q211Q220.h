#include <iostream>
#include <vector>
#include <map>
//#include <cmath> // pow

#include "factors_helper.h"
// #include "ifstream_with_path.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


/*Let phi be Euler's totient function, i.e. for a natural number n,
phi(n) is the number of k, 1 <= k <= n, for which gcd(k,n) = 1.
By iterating phi, each positive integer generates a decreasing
chain of numbers ending in 1.
E.g. if we start with 5 the sequence 5,4,2,1 is generated.
Here is a listing of all chains with length 4:
5,4,2,1
7,6,2,1
8,4,2,1
9,6,2,1
10,4,2,1
12,4,2,1
14,6,2,1
18,6,2,1
Only two of these chains start with a prime, their sum is 12. What is the
sum of all primes less than 40000000 which generate a chain of length 25?*/
long long int q214() {
	const int limit = 40000000, size = 25;

	long long int sum = 0;

	for (int n = size - (size % 2 == 0 ? 1 : 0); n < limit; n += 2) { // Remain odd for prime
		// if ((n - 1) % 1000000 == 0) { std::cout << n << " " << sum << std::endl; }

		if (!prime_helper::is_prime(n)) {
			continue;
		}

		if (factors_helper::phi_chain_length_for_prime(n) == size) {
			sum += n;
		}
	}

	return sum; // 1677366278943
}


long long int recursive_crack_free_wall_count(const int &wall_len, const int &remaining, const int &layers_remaining,
	std::set<int> crack_prior_layer_pos, std::set<int> crack_current_layer_pos) {

	static std::map<std::string, long long int> count_cache; // Static

	if (remaining == 0) {
		if (layers_remaining == 0) {
			return 1;
		}
		else {
			crack_prior_layer_pos = crack_current_layer_pos;
			crack_current_layer_pos.clear();
			return recursive_crack_free_wall_count(wall_len, wall_len, (layers_remaining - 1), crack_prior_layer_pos, crack_current_layer_pos);
		}
	}
	else if (remaining == 1) {
		// Incorrect length - cannot be finished with 2x1 or 3x1 bricks
		return 0;
	}

	if (remaining == wall_len) {
		std::ostringstream stringstream;
		stringstream << layers_remaining;

		for (std::set<int>::const_iterator it = crack_prior_layer_pos.begin(); it != crack_prior_layer_pos.end(); ++it) {
			stringstream << "-" << *it;
		}

		std::map<std::string, long long int>::const_iterator it = count_cache.find(stringstream.str());
		if (it == count_cache.end()) {

			long long int count = 0;

			// Use 2x1 brick - if there is enough space left and it wouldn't cause a running crack
			if (remaining >= 2 && (remaining - 2 == 0 || crack_prior_layer_pos.find(wall_len - remaining + 2) == crack_prior_layer_pos.end())) {
				crack_current_layer_pos.insert(wall_len - remaining + 2);
				count += recursive_crack_free_wall_count(wall_len, remaining - 2, layers_remaining, crack_prior_layer_pos, crack_current_layer_pos);
				crack_current_layer_pos.erase(wall_len - remaining + 2);
			}

			// Use 3x1 brick - if there is enough space left and it wouldn't cause a running crack
			if (remaining >= 3 && (remaining - 3 == 0 || crack_prior_layer_pos.find(wall_len - remaining + 3) == crack_prior_layer_pos.end())) {
				crack_current_layer_pos.insert(wall_len - remaining + 3);
				count += recursive_crack_free_wall_count(wall_len, remaining - 3, layers_remaining, crack_prior_layer_pos, crack_current_layer_pos);
				crack_current_layer_pos.erase(wall_len - remaining + 3);
			}

			count_cache.insert(std::pair<std::string, long long int>(stringstream.str(), count));

			return count;
		}

		return it->second;
	}

	long long int count = 0;

	// Use 2x1 brick - if there is enough space left and it wouldn't cause a running crack
	if (remaining >= 2 && (remaining - 2 == 0 || crack_prior_layer_pos.find(wall_len - remaining + 2) == crack_prior_layer_pos.end())) {
		crack_current_layer_pos.insert(wall_len - remaining + 2);
		count += recursive_crack_free_wall_count(wall_len, remaining - 2, layers_remaining, crack_prior_layer_pos, crack_current_layer_pos);
		crack_current_layer_pos.erase(wall_len - remaining + 2);
	}

	// Use 3x1 brick - if there is enough space left and it wouldn't cause a running crack
	if (remaining >= 3 && (remaining - 3 == 0 || crack_prior_layer_pos.find(wall_len - remaining + 3) == crack_prior_layer_pos.end())) {
		crack_current_layer_pos.insert(wall_len - remaining + 3);
		count += recursive_crack_free_wall_count(wall_len, remaining - 3, layers_remaining, crack_prior_layer_pos, crack_current_layer_pos);
		crack_current_layer_pos.erase(wall_len - remaining + 3);
	}

	return count;
}

/*Consider the problem of building a wall out of 2×1 and 3×1 bricks (horizontal
× vertical dimensions) such that, for extra strength, the gaps between
horizontally-adjacent bricks never line up in consecutive layers, i.e. never form
a "running crack". For example, the following 9×3 wall is not acceptable due to
the running crack shown in red:
There are eight ways of forming a crack-free 9×3 wall, written W(9,3) = 8.
Calculate W(32,10).*/
long long int q215() {

	const int wall_len = 32, wall_height = 10;

	std::set<int> crack_prior_layer_pos, crack_current_layer_pos;
	long long int count = recursive_crack_free_wall_count(wall_len, wall_len, (wall_height - 1), crack_prior_layer_pos, crack_current_layer_pos);

	return count; // 806844323190414
}

