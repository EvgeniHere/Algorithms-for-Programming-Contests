#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int INF = 100000000;
string street;
vector<int> grass_fields;
int max_n;

int rabbit(int n) {
    if (n == max_n - 1)
        return 0;

    if (n >= max_n)
        return -INF;

    if (grass_fields[n])
        return grass_fields[n];

    if (street[n] == 'w') {
        grass_fields[n] = -INF;
    } else {
        grass_fields[n] = max(rabbit(n + 1), max(rabbit(n + 3), rabbit(n + 5)));

        if (street[n] == '"')
            grass_fields[n]++;
    }

    return grass_fields[n];
}

int main() {
    cin >> max_n >> street;

    vector<int> tmp_fields(max_n);
    grass_fields = tmp_fields;

    int sol = rabbit(0);

    if (sol < 0)
        sol = -1;

    cout << sol << endl;
}
