#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

int main() {
    int t;
    cin >> t;

    int n;
    for (int i = 0; i < t; i++) {
        cin >> n;
        int c = 0;
        for (int k = 2; k < n; k++) {
            if (gcd(n, k) > 1)
                c++;
        }
        cout << c << endl;
    }

    return 0;
}
