#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int dp[501][501];

int main() {
    int n, s1, s2, gain, weight;

    cin >> n >> s1 >> s2;

    for (int i = 0; i < n; i++) {
        cin >> weight >> gain;
        for (int w1 = s1; w1 >= 0; w1--) {
            for (int w2 = s2; w2 >= 0; w2--) {
                if (w1 >= weight && w2 >= weight) {
                    dp[w1][w2] = max(dp[w1][w2], 
                        max(dp[w1 - weight][w2] + gain, dp[w1][w2 - weight] + gain));
                } else if (w1 >= weight) {
                    dp[w1][w2] = max(dp[w1][w2], dp[w1 - weight][w2] + gain);
                } else if (w2 >= weight) {
                    dp[w1][w2] = max(dp[w1][w2], dp[w1][w2 - weight] + gain);
                }
            }
        }
    }

    int result = 0;

    for (int i = 0; i <= s1; i++) {
        for (int j = 0; j <= s2; j++) {
            if (dp[i][j] > result) {
                result = dp[i][j];
            }
        }
    }

    cout << result << endl;
}