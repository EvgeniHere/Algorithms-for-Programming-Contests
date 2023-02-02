
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string s, int m) {
    vector<int> p(m);
    for (int i = 1; i < m; i++) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j])
            j = p[j - 1];
        if (s[i] == s[j])
            j++;
        p[i] = j;
    }
    return p;
}

int main() {
    string s;
    cin >> s;

    vector<int> p = prefix_function(s, (int)s.size());

    int last_index = 0;
    int x = 1;
    bool t = false;
    for (int i = 0; i < (int)p.size(); i++) {
        if (p[i] == 1) {
            last_index = i;
            t = true;
        }

        if (p[i] == 0)
            t = false;
    }
    cout << (t ? last_index : (int)s.size()) << endl;
}
