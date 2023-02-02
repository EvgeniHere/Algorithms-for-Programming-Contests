#include <iostream>
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
int gifts_received[MAXN];
int gifts_send[MAXN];

int main() {
    int n, m;

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        gifts_send[x]++;
        gifts_received[y]++;
    }

    int missing = 0;

    for (int i = 0; i < n; i++) {
        if (gifts_send[i] >= gifts_received[i])
            continue;

        missing += gifts_received[i] - gifts_send[i];
    }

    cout << missing << endl;
}