#pragma once
/*
** Title: DCEPC206 - Its a Murder!
** Link: http://www.spoj.com/problems/DCEPC206/
** Tag: Binary Indexed Tree (Fenwick Tree)
*/

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
template <typename T>
class BITree {
private:
	vector<T> tree;
	int max_size;
	vector<T> arr;
	vector<T> ordered_arr;

	void convert() {      // time complexity O(nlgn), space complexity O(n)
		// copy original arr to an ordered_arr for compression
		vector<T> temp(arr.size(), 0);
		for (int i = 0; i < arr.size(); ++i) {
			temp[i] = arr[i];
		}
		sort(temp.begin(), temp.end());
		for (int i = 0; i < arr.size(); ++i) {
			// lower_bound() returns pointer to the first element
			// greater than or equal to arr[i]
			ordered_arr[i] = lower_bound(temp.begin(), temp.end(), arr[i]) - temp.begin() + 1;
		}
	}
public:
	// constructor
	BITree(vector<T> &arr) : arr(arr), max_size(arr.size() + 1), tree(arr.size() + 1, 0), ordered_arr(arr.size(), 0) {
		// compression
		convert();
	}

	// query
	long long query_sum(int idx) {
		long long sum = 0;
		while (idx > 0) {             // be careful of cases including element '0'
			sum += tree[idx];
			idx -= idx & (-idx);
		}
		return sum;
	}

	// range-query
	long long query_range_sum(int from, int to) {
		if (from >= to) return 0;
		return query_sum(to) - query_sum(from);
	}

	// update
	void update(int idx, int add = -1) {
		if (idx <= 0) return;
		while (idx < max_size) {
			tree[idx] += add;
			idx += idx & (-idx);
		}
	}

	// print the built-in array
	void print_builtin_tree() {
		for (int i = 0; i < max_size; ++i) {
			cout << tree[i] << " ";
		}
		cout << endl;
	}

	// solve a specific problem (i.e. DCEPC_206)
	long long solve() {
		long long res = 0;
		for (int i = 0; i < ordered_arr.size(); ++i) {
			++tree[ordered_arr[i]];
		}

		for (int idx = 1; idx < max_size; ++idx) {
			int idx2 = idx + (idx & -idx);
			if (idx2 < max_size) tree[idx2] += tree[idx];
		}

		for (int i = 1; i < max_size; ++i) {
			res += arr[i - 1] * query_range_sum(ordered_arr[i - 1], max_size - 1);
			update(ordered_arr[i - 1]);
		}
		return res;
	}
};

void dcepc206_FenwickTree() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int n;
		cin >> n;
		vector<int> arr;
		for (int j = 0; j < n; ++j) {
			int num;
			cin >> num;
			arr.push_back(num);
		}
		BITree<int> bitree(arr);
		cout << bitree.solve() << endl;
	}
}