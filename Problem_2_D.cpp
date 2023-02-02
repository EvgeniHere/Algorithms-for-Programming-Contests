#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n;
    long long m;

    cin >> n;
    cin >> m;

    vector<long long> hashes;
    vector<long long> output;

    for (long long i = 0; i < n; i++) {
        signed long long x;
        cin >> x;
        hashes.insert(hashes.end(), x);
    }

    sort(hashes.begin(), hashes.end());

    for (long long i = 0; i < m; i++) {
        signed long long lookup;
        cin >> lookup;

        long long pos = upper_bound(hashes.begin(), hashes.end(), lookup) - hashes.begin();

        if (hashes[pos - 1] != lookup)
            pos = 0;

        output.insert(output.end(), pos);
    }

    for (long long x : output)
        cout << x << endl;
}