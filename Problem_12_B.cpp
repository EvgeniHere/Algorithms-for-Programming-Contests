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

ll mulmod(ll a, ll b, ll mod) {
    return (a * b) % mod;
}

ll binpow(ll a, ll n, ll mod) {
    if (!n)
        return 1;
    ll res = binpow(a, n / 2, mod);
    res = mulmod(res, res, mod);
    if (n & 1LL)
        res = mulmod(res, a, mod);
    return res;
}

ll inverse(ll a, ll mod) {
    return binpow(a, mod - 2, mod);
}

ll summod(ll a, ll b, ll mod) {
    return (a + b) % mod;
}

ll crt(vector<ll>& a, vector<ll>& m) {
    int k = (int)a.size();
    ll M = 1, x = 0;
    for (int i = 0; i < k; i++)
        M *= m[i];
    for (int i = 0; i < k; i++)
        x = summod(x, inverse(M / m[i], m[i]) * (M / m[i]) * a[i], M);
    return x;
}



int main() {
    ll n;
    cin >> n;
    n--;

    vector<ll> nums = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43 };
    vector<ll> a;
    vector<ll> m;

    for (int i = 0; i < n; i++) {
        a.push_back(nums[i]);
        m.push_back(nums[i+1]);
    }

    n = crt(a, m);

    cout << n << endl;
    return 0;
}
