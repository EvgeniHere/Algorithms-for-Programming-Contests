#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    string a, b;

    cin >> n >> a >> b;

    for (int i = 0; i < a.length(); i++) {
        if (a[i] == '.' || b[i] == '.')
            continue;

        cout << "NO";
        return 0;
    }

    cout << "YES";
    return 0;
}