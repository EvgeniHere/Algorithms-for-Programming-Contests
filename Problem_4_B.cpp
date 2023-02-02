#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long highest_turnover(int n, vector<int> a, vector<int> w, int c) {
	if (n == 1)
		return a[0];

	vector<long long> dp(c + 1);

	for (int i = 0; i <= n; i++) {
		for (int j = c; j >= w[i]; j--) {
			dp[j] = max(dp[j], dp[j - w[i]] + a[i]);
		}
	}

	return dp[c];
}

int main() {
	int n;

	cin >> n;

	vector<int> cars_short_a;
	vector<int> cars_short_w;
	vector<int> cars_long_a;
	vector<int> cars_long_w;

	int index_cars_short = 0;
	int index_cars_long = 0;

	for (int i = 0; i < n; i++) {
		int l, w, a;
		
		cin >> l >> w >> a;

		if (l > 60)
			continue;

		if (w > 3000)
			continue;

		if (a == 2)
			a = 150;
		else if (a > 2)
			a *= 100;

		if (l <= 40) {
			cars_short_a.push_back(a);
			cars_short_w.push_back(w);
			index_cars_short++;
		} else {
			cars_long_a.push_back(a);
			cars_long_w.push_back(w);
			index_cars_long++;
		}
	}

	cars_short_a.push_back(0);
	cars_short_w.push_back(0);
	cars_long_a.push_back(0);
	cars_long_w.push_back(0);

	long long erg = highest_turnover(index_cars_short, cars_short_a, cars_short_w, 3000)
		+ highest_turnover(index_cars_long, cars_long_a, cars_long_w, 3000);

	cout << erg << "$" << endl;
}