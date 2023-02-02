#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;

    int cases[100] = {};

    for (int i = 0; i < t; i++) {
        cin >> cases[i];
    }

    for (int i = 0; i < t; i++) {

        long long x = cases[i] + 1;

        cout << x*x << endl;
    }
}
