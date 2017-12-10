#pragma once
/*
** Title: DCEPC206 - Its a Murder!
** Link: http://www.spoj.com/problems/DCEPC206/
** Tag: Binary Indexed Tree (Fenwick Tree)
*/

#include <algorithm>
#include <vector>

using namespace std;
template <typename T>
class BITree {
private:
	vector<T> tree;
	int max_size;
	vector<T> &arr;
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
	BITree(vector<T> &arr) : arr(arr), max_size(arr.size() + 1) {
		// initialize private arrays
		for (int i = 0; i < max_size; ++i) {
			ordered_arr.push_back(0);
			tree.push_back(0);
		}
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

	// update
	void update(int idx, int add = 1) {
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
		for (int i = max_size - 1; i >= 0; --i) {  // Attention : travese in reverse order
			update(ordered_arr[i]);
		}
		for (int i = 0; i < max_size; ++i) {
			res += arr[ordered_arr[i]] * query_sum(ordered_arr[i]);
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
		vector<int> arr(n);
		for (int j = 0; j < n; ++j) {
			int num;
			cin >> num;
			arr[j] = num;
		}
		BITree<int> bitree(arr);
		cout << bitree.solve() << endl;
		bitree.print_builtin_tree();
	}
}