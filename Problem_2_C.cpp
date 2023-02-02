#include <iostream>
#include <bits/stdc++.h>
#include <deque>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> v;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.insert(v.end(), x);
    }

    sort(v.begin(), v.end(), greater<int>());

    for (auto x : v)
        cout << x << " ";
}