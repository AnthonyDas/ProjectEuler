#include <iostream>
#include <vector>
#include <string>
#include <list>

// #include "base_helper.h"
// #include "string_int.h"
// #include "ifstream_with_path.h"
// #include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


void recursive_generate_absent_days(int &count, std::vector<int> &absent_days, const int &days, const int &day) {
	// Do we have a complete absent day set?
	if (!day) {
		// Determine how many possibilities there are to include an (optional) late day.
		// There are 30 possible days (1, 2,..., 30) as well as never late.
		// However, if we are absent on a given day, then it cannot be a late day.
		count += days + 1 - (int)absent_days.size();

		return;
	}

	// On time - just move onto next day
	recursive_generate_absent_days(count, absent_days, days, (day - 1));

	// Can this be an absent day?
	bool absent_day = true;
	if (absent_days.size() >= 2) {
		const int last = absent_days.back();
		const int second_last = absent_days.rbegin()[1];

		// Exclude three consecutive absent days
		if (second_last == (last + 1) && last == (day + 1)) {
			absent_day = false;
		}
	}

	if (absent_day) {
		absent_days.push_back(day);
		recursive_generate_absent_days(count, absent_days, days, (day - 1));
		absent_days.pop_back();
	}
}

/* A particular school offers cash rewards to children with good attendance
and punctuality. If they are absent for three consecutive days or late on more
than one occasion then they forfeit their prize.

During an n-day period a trinary string is formed for each child consisting of
L's (late), O's (on time), and A's (absent).

Although there are eighty-one trinary strings for a 4-day period that can be
formed, exactly forty-three strings would lead to a prize:

OOOO OOOA OOOL OOAO OOAA OOAL OOLO OOLA OAOO OAOA
OAOL OAAO OAAL OALO OALA OLOO OLOA OLAO OLAA AOOO
AOOA AOOL AOAO AOAA AOAL AOLO AOLA AAOO AAOA AAOL
AALO AALA ALOO ALOA ALAO ALAA LOOO LOOA LOAO LOAA
LAOO LAOA LAAO

How many "prize" strings exist over a 30-day period? */
int q191() {
	const int days = 30;

	int count = 0;

	// Generate all distinct sets of absent days excluding three consecutive absent days.
	std::vector<int> absent_days;
	recursive_generate_absent_days(count, absent_days, days, days);

	return count; // 1'918'080'160
}
