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

    vector<int> as(n);

    for (int i = 0; i < n; i++) {
        cin >> as[i];
    }

    ll res_gcd = 0;
    ll res_lcm = 1;

    for (int i = 1; i < n; i++) {
        ll cur_res_gcd = 0;
        ll cur_res_lcm = 1;
        for (int j = 0; j < i; j++) {
            ll cur_gcd = gcd(as[i], as[j]);
            ll cur_lcm = as[i] / cur_gcd * as[j];
            cur_res_gcd = gcd(res_gcd, cur_lcm);
            cur_res_lcm = lcm(res_lcm, cur_gcd);
        }
        res_gcd = gcd(res_gcd, cur_res_gcd);
        res_lcm = lcm(res_lcm, cur_res_lcm);
    }

    cout << res_gcd << " " << res_lcm << endl;
    return 0;
}
