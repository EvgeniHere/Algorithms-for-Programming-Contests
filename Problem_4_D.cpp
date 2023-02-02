#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int counter = 0;

struct STAR {
    int id;
    int weight;
};

vector<vector<long long>> dp;
vector<int> orig_seq;

long long most_energy(int current_index, vector<STAR> seq) {
    if (current_index <= 0 || current_index >= seq.size() - 1)
        return 0;

    int left_cur_index = current_index;
    int right_cur_index = current_index;
    
    if (left_cur_index > 0)
        left_cur_index = current_index - 1;

    if (right_cur_index + 1 < seq.size())
        right_cur_index = current_index + 1;

    int left_cur_weight = seq[left_cur_index].weight;
    int right_cur_weight = seq[right_cur_index].weight;

    int left_index = find(orig_seq.begin(), orig_seq.end(), left_cur_weight) - orig_seq.begin();
    int right_index = find(orig_seq.begin(), orig_seq.end(), right_cur_weight) - orig_seq.begin();

    if (dp[left_index][right_index])
        return dp[left_index][right_index];

    long long erg = left_cur_weight * right_cur_weight;

    vector<STAR> next_seq(seq);

    next_seq.erase(next_seq.begin() + current_index);
        
    long long left_erg = most_energy(current_index - 1, next_seq);
    long long right_erg = most_energy(current_index, next_seq);

    long long max_erg = erg + max(left_erg, right_erg);

    dp[left_index][right_index] = max_erg;

    return max_erg;
}

int main() {
    int n;

    cin >> n;

    vector<STAR> seq;

    vector<vector<int>> tmp_dp;

    for (int i = 0; i < n; i++) {
        STAR star;
        star.id = i;
        cin >> star.weight;
        seq.push_back(star);
        orig_seq.push_back(star.weight);
    }

    for (int i = 0; i < n; i++) {
        vector<long long> nums(n);
        dp.push_back(nums);
    }

    long long max_erg = 0;

    for (int i = 1; i + 1 < seq.size(); i++) {
        long long erg = seq[i - 1].weight * seq[i + 1].weight;

        vector<STAR> next_seq(seq);

        next_seq.erase(next_seq.begin() + i);

        long long left_erg = most_energy(i - 1, next_seq);
        long long right_erg = most_energy(i, next_seq);

        max_erg = max(max_erg, erg + max(left_erg, right_erg));

        //dp[i - 1][i + 1] = max_erg;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }

    cout << max_erg << endl;
}
