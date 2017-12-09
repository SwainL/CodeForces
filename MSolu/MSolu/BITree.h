#pragma once
#pragma once
#include <vector>

using namespace std;
class BITree {
	// Implementation of a Binary Indexed Tree (Fenwick Tree)
private:
	vector<int> tree;

public:
	BITree(const vector<int> &list) {
		// Initialize BITree with list in O(n)
		tree = vector<int>(list.size() + 1, 0);
		for (int idx = 0; idx < list.size(); ++idx) {
			tree[idx + 1] = list[idx];
		}

		for (int idx = 1; idx < tree.size(); ++idx) {
			int idx2 = idx + (idx & -idx);
			if (idx2 < tree.size()) {
				tree[idx2] += tree[idx];
			}
		}
	}

	int prefix_query(int idx) {
		// Computes prefix sum of elements from 1 up to the idx-th inclusively
		int result = 0;
		while (idx > 0) {
			result += tree[idx];
			idx -= idx & -idx;
		}
		return result;
	}

	int range_query(int start, int end) {
		// Computes the range sum between two indices (both inclusive)
		return prefix_query(end) - prefix_query(start - 1);
	}

};
