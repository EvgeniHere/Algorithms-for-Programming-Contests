#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;

int m;

vector<int> f;

vector<int> min_pyr(300001);

int least_pyramids(int m) {
    if (m == 0)
        return 0;

    if (min_pyr[m])
        return min_pyr[m];

    int min = INF;

    for (int i = 0; i < f.size(); i++) {
        if (f[i] > m)
            break;

        int pyramids_when_using_f_of_i_balls_now = least_pyramids(m - f[i]);

        if (pyramids_when_using_f_of_i_balls_now < min)
            min = pyramids_when_using_f_of_i_balls_now;
    }

    min_pyr[m] = min + 1;

    if (min == INF)
        return INF;

    return min + 1;
}

int main() {
    int t;

    cin >> t;

    vector<int> tests(t);

    for (int i = 0; i < t; i++) {
        cin >> tests[i];
    }

    f.push_back(1);
    for (int i = 2; f[i - 2] < 300001; i++) {
        f.push_back((i * (i + 1) * (i + 2)) / 6);
    }

    for (int i = 0; i < t; i++) {
        int sol = least_pyramids(tests[i]);
        cout << sol << endl;
    }
}
