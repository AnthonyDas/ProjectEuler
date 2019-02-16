#include <iostream>
#include <vector>
#include <set>
#include <numeric> // std::accumulate

#include "factors_helper.h"
// #include "ifstream_with_path.h"
// #include "prime_helper.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net


void recursive_next_batch(const std::vector<int> &sheet_counts, const int &remaining_batches,
	const long long int &prob_num, const long long int &prob_den, int single_sheet_count, double &single_sheet_expectation) {

	if (remaining_batches == 1) {
		single_sheet_expectation += (double)(single_sheet_count * prob_num) / (double)prob_den;
		return; // Use the last remaining A5 sheet
	}

	// Total sheets in envelope
	const int total_sheets = std::accumulate(sheet_counts.begin(), sheet_counts.end(), 0);
	if (total_sheets == 1) {
		++single_sheet_count;
	}

	// Select A2
	if (sheet_counts[0] > 0) {
		// Cut the sheet and use up an A5
		std::vector<int> next_sheet_counts(sheet_counts);
		--next_sheet_counts[0];
		++next_sheet_counts[1];
		++next_sheet_counts[2];
		++next_sheet_counts[3];

		recursive_next_batch(next_sheet_counts, (remaining_batches - 1), (prob_num * sheet_counts[0]),
			(prob_den * total_sheets), single_sheet_count, single_sheet_expectation);
	}

	// Select A3
	if (sheet_counts[1] > 0) {
		// Cut the sheet and use up an A5
		std::vector<int> next_sheet_counts(sheet_counts);
		--next_sheet_counts[1];
		++next_sheet_counts[2];
		++next_sheet_counts[3];

		recursive_next_batch(next_sheet_counts, (remaining_batches - 1), (prob_num * sheet_counts[1]),
			(prob_den * total_sheets), single_sheet_count, single_sheet_expectation);
	}

	// Select A4
	if (sheet_counts[2] > 0) {
		// Cut the sheet and use up an A5
		std::vector<int> next_sheet_counts(sheet_counts);
		--next_sheet_counts[2];
		++next_sheet_counts[3];

		recursive_next_batch(next_sheet_counts, (remaining_batches - 1), (prob_num * sheet_counts[2]),
			(prob_den * total_sheets), single_sheet_count, single_sheet_expectation);
	}

	// Select A5
	if (sheet_counts[3] > 0) {
		// Cut the sheet and use up an A5
		std::vector<int> next_sheet_counts(sheet_counts);
		--next_sheet_counts[3];

		recursive_next_batch(next_sheet_counts, (remaining_batches - 1), (prob_num * sheet_counts[3]),
			(prob_den * total_sheets), single_sheet_count, single_sheet_expectation);
	}
}

/*A printing shop runs 16 batches (jobs) every week and each batch requires a
sheet of special colour-proofing paper of size A5. Every Monday morning, the
foreman opens a new envelope, containing a large sheet of the special paper with
size A1. He proceeds to cut it in half, thus getting two sheets of size A2. Then he
cuts one of them in half to get two sheets of size A3 and so on until he obtains
the A5-size sheet needed for the first batch of the week. All the unused sheets
are placed back in the envelope. At the beginning of each subsequent batch, he
takes from the envelope one sheet of paper at random. If it is of size A5, he uses
it. If it is larger, he repeats the 'cut-in-half' procedure until he has what he
needs and any remaining sheets are always placed back in the envelope.
Excluding the first and last batch of the week, find the expected number of times
(during each week) that the foreman finds a single sheet of paper in the envelope.
Give your answer rounded to six decimal places using the format x.xxxxxx .*/
double q151() {
	// A2, A3, A4, A5
	std::vector<int> sheet_counts;
	sheet_counts.push_back(1);
	sheet_counts.push_back(1);
	sheet_counts.push_back(1);
	sheet_counts.push_back(1);

	int remaining_batches = 15, single_sheet_count = 0;
	long long int prob_num = 1, prob_den = 1;

	double single_sheet_expectation = 0;

	recursive_next_batch(sheet_counts, remaining_batches, prob_num, prob_den, single_sheet_count, single_sheet_expectation);

	return round(single_sheet_expectation * 1000000) / 1000000; // 6 d.p.
}


/* An electric circuit uses exclusively identical capacitors of the same value C. 
The capacitors can be connected in series or in parallel to form sub-units, which
can then be connected in series or in parallel with other capacitors or other sub-units
to form larger sub-units, and so on up to a final circuit.

Using this simple procedure and up to n identical capacitors, we can make circuits
having a range of different total capacitances. For example, using up to n=3 capacitors
of 60 muF each, we can obtain the following 7 distinct total capacitance values:

If we denote by D(n) the number of distinct total capacitance values we can obtain when
using up to n equal-valued capacitors and the simple procedure described above,
we have: D(1)=1, D(2)=3, D(3)=7 ...

Find D(18).

Reminder: When connecting capacitors C1, C2 etc in parallel, the total capacitance
is CT = C1 + C2 +..., whereas when connecting them in series, the overall capacitance
is given by: 1/CT = 1/C1 + 1/C2 + ... */

inline fraction<int> in_series(fraction<int> a, fraction<int> b) {
	return (a.reciprocal() + b.reciprocal()).reciprocal();
}

inline fraction<int> in_parallel(const fraction<int> &a, const fraction<int> &b) {
	return a + b;
}

int q155() {
	const int limit = 18;

	// Map: Total capacitors, possible capacitances
	std::map<int, std::set<fraction<int>>> options; 
	options[1].insert(60);

	for (int i = 2; i <= limit; ++i) { // Total capacitors
		for (int j = 1; j <= (i / 2); ++j) { // Group 1 size, Group 2 size will be (i - j)
			// std::cout << "Total capacitors: " << i << ", group size: " << j << std::endl;

			// Brute search for combining Group 1 and Group 2
			for (auto &o1 : options[j]) {
				for (auto &o2 : options[i - j]) {
					options[i].insert(in_series(o1, o2));
					options[i].insert(in_parallel(o1, o2));
				}
			}

		}
	}

	std::set<fraction<int>> set;
	for (auto &pair : options) {
		for (auto &f : pair.second) {
			set.insert(f);
		}
	}

	return (int)(set.size()); // 3'857'447
}