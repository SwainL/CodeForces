#pragma once
/*
** Title: DCEPC206 - Its a Murder!
** Link: http://www.spoj.com/problems/DCEPC206/
** Tag: divide and conquer, merge sort
*/
#include <iostream>
#include <vector>

using namespace std;

long long sum(int*, const int);
long long helper(int *arr, const int lo, const int hi);
int arr[100005], temp[100005];



long long sum(int *arr, const int s) {
	return helper(arr, 0, s - 1);
}

long long helper(int *arr, const int lo, const int hi) {
	if (lo >= hi) return 0;

	int mid = (lo + hi) >> 1;
	long long res = 0;

	// solve sub-problem recursively
	res += helper(arr, lo, mid);
	res += helper(arr, mid + 1, hi);

	// sort and merge
	int idx = lo, p1 = lo, p2 = mid + 1;
	while (p1 <= mid && p2 <= hi) {
		if (arr[p1] < arr[p2]) {
			res += arr[p1] * (hi - p2 + 1);
			temp[idx++] = arr[p1++];	
		}
		else {
			temp[idx++] = arr[p2++];
		}
	}
	while (p1 <= mid) {
		temp[idx++] = arr[p1++];
	}
	while (p2 <= hi) {
		temp[idx++] = arr[p2++];
	}
	// copy sorted temporary array back to original arr
	for (int i = lo; i <= hi; ++i) {
		arr[i] = temp[i];
	}
	return res;
}

int dcepec206() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int n;
		cin >> n;
		for (int j = 0; j < n; ++j) {
			int num;
			cin >> num;
			arr[j] = num;
		}
		cout << sum(arr, n) << endl;
	}
	return 0;
}

