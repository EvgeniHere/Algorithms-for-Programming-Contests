#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;

    cin >> n;

    vector<int> seq(n);

    for (int i = 0; i < n; i++) {
        cin >> seq[i];
    }

    int inc = 1;
    int dec = 1;

    for (int i = 1; i < n; i++) {
        if (seq[i] > seq[i - 1])
            inc = dec + 1;
        else if (seq[i] < seq[i - 1])
            dec = inc + 1;
    }

    cout << max(inc, dec) << endl;
}
