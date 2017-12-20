#pragma once
#include<iostream>
#include<algorithm>

using namespace std;

int n, l;
int arr[1001];
double d;


void test() {
	cin >> n >> l;
	for (int i = 0; i < n; ++i) {
		int lntrn;
		cin >> lntrn;
		arr[i] = lntrn;
	}
	sort(arr, arr + n);
	double d = arr[0];
	for (int i = 1; i < n; ++i) {
		double cur = ((double)arr[i] - arr[i - 1]) / 2;
		d = max(d, cur);
	}
	d = max(d, (double)l - arr[n - 1]);
	printf("%.10f", d);
}
