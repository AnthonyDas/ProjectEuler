#include <iostream>
#include <vector>

// #include "base_helper.h"
// #include "string_int.h"
// #include "ifstream_with_path.h"
#include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/* There are some prime values, p, for which there exists a positive integer,
n, such that the expression n^3 + (n^2)p is a perfect cube.
For example, when p = 19, 8^3 + (8^2)×19 = 12^3.
What is perhaps most surprising is that for each prime with this property
the value of n is unique, and there are only four such primes below one-hundred.
How many primes below one million have this remarkable property? */
int q131() {
	/* 
	(n^3) + (n^2).p = C^3 for some integer C
	(n^3) . (1 + p/n) = C^3
	(n^3) . ((n + p)/n) = C^3

	Take cube roots on both sides:
	
	n . cube_rt((n + p)/n) = C
	n . (cube_rt(n + p)/cube_rt(n)) = C

	Since n and C are integers, we must have (cube_rt(n + p)/cube_rt(n))
	being an integer. Now cube roots are irrational if their operands are
	not perfect cubes. Therefore, (n + p) and n must be perfect cubes.
	Let (n + p) = y^3 and n = x^3 for some integers y and x.

	p = (n + p) - n
	p = (y^3) - (x^3)
	p = (y - x) . (y^2 + xy + x^2)

	But since p is prime, this implies (y - x) = 1, so y = (x + 1).

	p = (y^3) - (x^3)
	p = ((x + 1)^3) - (x^3)
	*/

	const int limit = 1'000'000;

	int count = 0, x = 0, p = 0;
	while (p < limit) {
		if (prime_helper::is_prime(p)) {
			++count;
		}
		++x;
		p = (x + 1) * (x + 1) * (x + 1) - (x * x * x);
	}

	return count; // 173
}
