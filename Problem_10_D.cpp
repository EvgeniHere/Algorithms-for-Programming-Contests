#include <iostream>
#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> men(n);

    for (int i = 0; i < n; i++)
        men[i] = n - i;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        for (int i = b - a; i >= 0; i--)
            men.push_back(men[n - (a + i) - 1]);

        men.erase(men.begin() + (n - b - 1), men.begin() + (n - a));
    }

    for (int i = n - 1; i >= 0; i--)
        cout << men[i] << " ";
}