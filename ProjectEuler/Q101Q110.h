#include <iostream>
#include <vector>
#include <unordered_set>

#include "pan_digit_helper.h"
#include "ifstream_with_path.h"
#include "darts_helper.h"
#include "triangle.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

/*Three distinct points are plotted at random on a Cartesian plane,
for which -1000 = x, y = 1000, such that a triangle is formed.

Consider the following two triangles:
A(-340,495), B(-153,-910), C(835,-947)
X(-175,41), Y(-421,-714), Z(574,-645)

It can be verified that triangle ABC contains the origin, whereas triangle
XYZ does not. Using triangles.txt (right click and 'Save Link/Target As...'),
a 27K text file containing the co-ordinates of one thousand "random" triangles,
find the number of triangles for which the interior contains the origin.
NOTE: The first two examples in the file represent the triangles in the
example given above.*/
int q102() {

	ifstream_with_path fin("Problem102.txt");

	int x1, y1, x2, y2, x3, y3, count = 0;
	while (fin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
		
		triangle<int> t(std::pair<int, int>(x1, y1), std::pair<int, int>(x2, y2), std::pair<int, int>(x3, y3));

		//std::cout << t << " " << t.contains_origin() << std::endl;

		if (t.contains_origin()) {
			++count;
		}
	}
	fin.close();

	return count; // 228
}


/*The Fibonacci sequence is defined by the recurrence relation:
F(n) = F(n-1) + F(n-2), where F(1) = 1 and F(2) = 1.
It turns out that F(541), which contains 113 digits, is the first Fibonacci
number for which the last nine digits are 1-9 pandigital (contain all the
digits 1 to 9, but not necessarily in order). And F(2749), which contains
575 digits, is the first Fibonacci number for which the first nine digits
are 1-9 pandigital. Given that F(k) is the first Fibonacci number for which
the first nine digits AND the last nine digits are 1-9 pandigital, find k.*/
int q104() {
	int n = 2;

	vector_int  x(1), y(1), z(0);
	while (true) {

		z = x + y;
		x = y;
		y = z;

		++n;

		// if (n % 10000 == 0) { std::cout << n << " " << y.size() << std::endl; }

		if (y.size() >= 9) {
			if (pan_digit_helper::is_pan_digit(y.last_digits(9)) &&
				pan_digit_helper::is_pan_digit(y.first_digits(9))) {
				break;
			}
		}
	}

	return n; // 329468
}

/* The following undirected network consists of seven vertices and twelve
edges with a total weight of 243.

The same network can be represented by the matrix below.

		A	B	C	D	E	F	G
A	-	16	12	21	-	-	-
B	16	-	-	17	20	-	-
C	12	-	-	28	-	31	-
D	21	17	28	-	18	19	23
E	-	20	-	18	-	-	11
F	-	-	31	19	-	-	27
G	-	-	-	23	11	27	-

However, it is possible to optimise the network by removing some edges and
still ensure that all points on the network remain connected. The network
which achieves the maximum saving is shown below. It has a weight of 93,
representing a saving of 243 - 93 = 150 from the original network.

Using network.txt, a 6K text file containing a network with forty vertices,
and given in matrix form, find the maximum saving which can be achieved by
removing redundant edges whilst ensuring that the network remains connected. */
int q107() {
	const int size = 40;
	int	edge_count = 0, row = 0, col = 0, weight;

	std::vector<std::tuple<int, int, int> > edges;

	ifstream_with_path fin("Problem107.txt");
	while (fin >> weight) {
		// Edges have non-zero weight in the matrix and don't doulbe count edges.
		// E.g. Matrix[i][j] is the same as Matrix[j][i]
		if (weight && row <= col) {
			edges.push_back(std::make_tuple(row, col, weight)); // node1, node2, weight
		}
		++col;
		if (col == size) {
			++row;
			col = 0;
		}
	}
	fin.close();

	// Sort by weight ascending
	std::sort(edges.begin(), edges.end(), [](const std::tuple<int, int, int> &a, const std::tuple<int, int, int> &b) {
		return std::get<2>(a) < std::get<2>(b);}
	);

	int weight_saved = 0;

	// To begin with, every node belongs to a (disjoint) set containing just itself
	std::vector<int> node_set_id(size); // Vector indicating which set a node belongs to
	std::vector<std::unordered_set<int> > node_sets(size); // Vector of node sets
	for (int i = 0; i < size; ++i) {
		node_set_id[i] = i;
		node_sets[i].insert(i);
	}

	// Now start adding in the edges, connecting up the (disjoint) sets.
	// Ultimately, we want all the nodes to be in a single set, (i.e. network is connected).
	for (auto &e : edges) {
		const int node1 = std::get<0>(e);
		const int node2 = std::get<1>(e);
		
		// Exclude edges if the two nodes it connects already live in the same set.
		if (node_set_id[node1] == node_set_id[node2]) {
			weight_saved += std::get<2>(e);
		}
		// Otherwise, the edge connects up two disjoint sets. Merge the sets.
		else {
			const int set_id1 = node_set_id[node1];
			const int set_id2 = node_set_id[node2];

			for (auto &node : node_sets[set_id2]) {
				node_sets[set_id1].insert(node);
				node_set_id[node] = set_id1;
			}
			node_sets[set_id2].clear();
		}
	}

	return weight_saved; // 259679
}


/* In the game of darts a player throws three darts at a target board which
is split into twenty equal sized sections numbered one to twenty.
The score of a dart is determined by the number of the region that the dart
lands in. A dart landing outside the red/green outer ring scores zero. The
black and cream regions inside this ring represent single scores. However,
the red/green outer ring and middle ring score double and treble scores respectively.
At the centre of the board are two concentric circles called the bull region,
or bulls-eye. The outer bull is worth 25 points and the inner bull is a double,
worth 50 points.
There are many variations of rules but in the most popular game the players will
begin with a score 301 or 501 and the first player to reduce their running total
to zero is a winner. However, it is normal to play a "doubles out" system, which
means that the player must land a double (including the double bulls-eye at the
centre of the board) on their final dart to win; any other dart that would reduce
their running total to one or lower means the score for that set of three darts is "bust".
When a player is able to finish on their current score it is called a "checkout"
and the highest checkout is 170: T20 T20 D25 (two treble 20s and double bull).
There are exactly eleven distinct ways to checkout on a score of 6:

D3	
D1	D2	 
S2	D2	 
D2	D1	 
S4	D1	 
S1	S1	D2
S1	T1	D1
S1	S3	D1
D1	D1	D1
D1	S2	D1
S2	S2	D1

Note that D1 D2 is considered different to D2 D1 as they finish on different doubles.
However, the combination S1 T1 D1 is considered the same as T1 S1 D1.
In addition we shall not include misses in considering combinations; for example, D3 is
the same as 0 D3 and 0 0 D3.
Incredibly there are 42336 distinct ways of checking out in total.
How many distinct ways can a player checkout with a score less than 100? */
int q109() {

	int count = 0;

	for (int target = 2; target < 100; ++target) {
		int ways = darts_helper::check_out_count(target);
		// std::cout << target << " " << ways << std::endl;
		count += ways;
	}

	return count; // 38182
}
