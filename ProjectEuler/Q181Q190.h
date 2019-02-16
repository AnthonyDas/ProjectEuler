#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>

//#include "base_helper.h"
//#include "ifstream_with_path.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


int S(std::vector<int> &S_cache, const size_t &n) {
	int res = 0;

	if (S_cache.size() >= n) {
		res = S_cache[n - 1];
	}
	else {
		while (S_cache.size() < n) {
			size_t m = S_cache.size() + 1;
			if (1 <= m && m <= 55) {
				size_t a = (200003 * m) % 1000000;
				size_t b = (300007 * m) % 1000000;
				b = (b * m) % 1000000;
				b = (b * m) % 1000000;
				// The +1000000 is to ensure a positive number after -a
				res = (int)((100003 - a + b + 1000000) % 1000000);
			}
			else { // 65 <= m
				res = (S_cache[m - 24] + S_cache[m - 55]) % 1000000;
			}
			S_cache.push_back(res);
		}
	}

	return res;
}

/* Here are the records from a busy telephone system with one million users:

RecNr	Caller	Called
1	200007	100053
2	600183	500439
3	600863	701497
...	...	...

The telephone number of the caller and the called number in record n are
Caller(n) = S[2n-1] and Called(n) = S[2n] where S[1,2,3,...] come from the
"Lagged Fibonacci Generator":

For 1 <= k <= 55, S[k] = [100003 - 200003k + 300007.k^3] (modulo 1000000)
For 56 <= k, S[k] = [S[k-24] + S[k-55]] (modulo 1000000)

If Caller(n) = Called(n) then the user is assumed to have misdialled and
the call fails; otherwise the call is successful.

From the start of the records, we say that any pair of users X and Y are
friends if X calls Y or vice-versa. Similarly, X is a friend of a friend
of Z if X is a friend of Y and Y is a friend of Z; and so on for longer
chains.

The Prime Minister's phone number is 524287. After how many successful
calls, not counting misdials, will 99% of the users (including the PM)
be a friend, or a friend of a friend etc., of the Prime Minister? */
int q186() {
	const int PM = 524287, users = 1'000'000;

	std::vector<int> S_cache;
	
	std::vector<int> set_id(users);
	std::vector<std::unordered_set<int> > sets(users);
	for (int i = 0; i < users; ++i) {
		set_id[i] = i;
		sets[i].insert(i);
	}

	int call_n = 0, misdials = 0;
	while ((double)sets[set_id[PM]].size() / (double)users < 0.99) {
		++call_n;

		int caller = S(S_cache, (2 * call_n) - 1);
		int called = S(S_cache, (2 * call_n));

		// If Caller(n) = Called(n) then  user misdialled
		if (caller == called) {
			++misdials;
			continue;
		}
		 
		// If the caller and called are not in the same set then merge their sets.
		// This makes them friends, as well as their friends friends of each other.
		if (set_id[caller] != set_id[called]) {
			const int to = set_id[caller];
			const int from = set_id[called];

			for (auto &e : sets[from]) {
				sets[to].insert(e);
				set_id[e] = to;
			}
			sets[from].clear();
		}
	}

	return call_n - misdials;
}


/*A composite is a number containing at least two prime factors.
For example, 15 = 3 × 5; 9 = 3 × 3; 12 = 2 × 2 × 3. There are ten
composites below thirty containing precisely two, not necessarily
distinct, prime factors: 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.
How many composite integers, n < 10^8, have precisely two, not
necessarily distinct, prime factors?*/
int q187() {

	const int limit = 100000000;

	std::vector<int> primes;
	primes.reserve(limit / 10);
	primes.push_back(2);
	primes.push_back(3);

	// All primes greater than 3 can be written in the form 6k +/- 1.
	// Smallest prime is 2 so largest other prime factor of n is (limit / 2).
	// +1 as we actually test prime_helper::is_prime(n - 1).
	const int max = (limit / 2) + 1;
	for (int n = 6; n <= max; n += 6) {
		// if (n % 999996 == 0) { std::cout << n << std::endl; }

		if (prime_helper::is_prime(n - 1)) {
			primes.push_back(n - 1);
		}
		if (prime_helper::is_prime(n + 1)) {
			primes.push_back(n + 1);
		}
	}

	int count = 0;
	for (std::vector<int>::const_iterator it_i = primes.begin(); it_i != primes.end(); ++it_i) {
		for (std::vector<int>::const_iterator it_j = it_i; it_j != primes.end(); ++it_j) {
			// Multiplication needs long long int
			if ((long long int)(*it_i) * (long long int)(*it_j) > (long long int)limit) {
				break;
			}
			++count;
		}
	}
	
	return count; // 17427258
}

enum colour { red, green, blue };

void recursive_colour_in_row(std::map<std::vector<colour>, long long int> &curr_sig_m,
	const std::pair<std::vector<colour>, long long int> &prior_sig_r, std::vector<colour> &current_row,
	const int &i, const int &j) {

	// Recursion termination: Append signature of current_row into the curr_sig_m
	if (j > (2 * i)) {
		// Create the signature for current_row - take even index values only
		std::vector<colour> new_sig;
		for (size_t i = 0; i < current_row.size(); i += 2) {
			new_sig.push_back(current_row[i]);
		}
		curr_sig_m[new_sig] += prior_sig_r.second;

		return;
	}

	// First element along row - no constraints
	if (j == 0) {
		for (auto &c : { red, green, blue }) {
			current_row[j] = c;
			recursive_colour_in_row(curr_sig_m, prior_sig_r, current_row, i, (j + 1));
		}
	}
	// Elements with even index inc. final element along row - one constraint, (i.e. on lhs)
	else if (j % 2 == 0) {
		for (auto &c : { red, green, blue }) {
			if (c != current_row[j - 1]) {
				current_row[j] = c;
				recursive_colour_in_row(curr_sig_m, prior_sig_r, current_row, i, (j + 1));
			}
		}
	}
	// Mid row with odd index - two constraints, (i.e on lhs and above)
	else {
		for (auto &c : { red, green, blue }) {
			if (c != current_row[j - 1] && c != prior_sig_r.first[(j - 1) / 2]) {
				current_row[j] = c;
				recursive_colour_in_row(curr_sig_m, prior_sig_r, current_row, i, (j + 1));
			}
		}
	}
}

/* Consider the following configuration of 64 triangles:

We wish to colour the interior of each triangle with one of three colours:
red, green or blue, so that no two neighbouring triangles have the same colour.
Such a colouring shall be called valid. Here, two triangles are said to be
neighbouring if they share an edge.

Note: if they only share a vertex, then they are not neighbours.

For example, here is a valid colouring of the above grid:

A colouring C' which is obtained from a colouring C by rotation or reflection
is considered distinct from C unless the two are identical.

How many distinct valid colourings are there for the above configuration? */
long long int q189() {
	const int rows = 8;

	/* Our approach is to produce and count valid colourings starting
	from the top row and colouring in each subsequent row. Note that when
	we colour in a given row, we need to know the colours of elements in
	the row above which share an edge with an element in the current row
	and ONLY those elements. Let these special elements in the row above
	denote a "signature".

	To prevent repeat processing, we count the number of times a given
	"signature" for the row above appears. Based on each signature, we 
	colour in the current row and generate a signature of the result. This
	signature along with its correspinding appearance count is then stored
	within a map. We repeat for the next row and so on.

	As way of example, consider coming onto colouring in the 8th (final) row 
	which has 15 elements. This row has 7 elements which share edges with
	elements in the row above. With 3 colours, there will be at most 3^7 = 2187
	possible signatures for the row above. This is a relatively small number
	and each colouring for the final row can be computed in turn via brute-force. */

	// Top row is a single triange which can be red, green or blue all with frequency 1
	std::map<std::vector<colour>, long long int> curr_sig_m(
		{ {{red}, 1}, {{green}, 1}, {{blue}, 1} });
	std::map<std::vector<colour>, long long int> prior_sig_m;

	// For second row until the bottom row
	for (int i = 1; i < rows; ++i) {
		prior_sig_m.swap(curr_sig_m);
		curr_sig_m.clear();

		std::vector<colour> current_row((2 * i) + 1, red);

		for (auto &prior_sig_r : prior_sig_m) {
			// Fill in the current row given the signature of the row above
			recursive_colour_in_row(curr_sig_m, prior_sig_r, current_row, i, 0);
		}
	}

	long long int count = 0;
	for (auto &e : curr_sig_m) {
		count += e.second;
	}

	return count; // 10'834'893'628'237'824
}