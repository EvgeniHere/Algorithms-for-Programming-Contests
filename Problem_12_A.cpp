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
    int n;
    cin >> n;

    ll res = 0;

    ll input;
    for (int i = 0; i < n; i++) {
        cin >> input;
        res = gcd(res, input);
    }

    cout << (res - 1) << endl;
    return 0;
}