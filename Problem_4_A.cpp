#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> combs;

long long calc_possibs(int n) {
	combs[0][0] = 1;
	combs[0][1] = 1;
	combs[0][2] = 1;

	for (int i = 1; i < n; i++) {
		combs[i][0] = combs[i-1][0] + combs[i-1][1];
		combs[i][1] = combs[i-1][0] + combs[i-1][1] + combs[i-1][2];
		combs[i][2] = combs[i-1][0] + combs[i-1][1] + combs[i-1][2];
	}

	return combs[n-1][0] + combs[n-1][1] + combs[n-1][2];
}

int main() {
	int n;

	cin >> n;

	if (n == 0) {
		cout << 1 << "\n";
		return 0;
	}

	for (int i = 0; i < n; i++) {
		vector<long long> nums(3);
		combs.push_back(nums);
	}

	cout << calc_possibs(n) << endl;
}