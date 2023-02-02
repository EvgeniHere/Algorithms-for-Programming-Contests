#include <iostream>
#include <bits/stdc++.h>
#include <deque>

using namespace std;

int main()
{
    deque<string> d;

    string s;

    while (getline(cin, s)) {
        d.push_front(s);
    }

    for (auto val : d) {
        string rev_val;
        for (int i = val.length() - 1; i >= 0; i--)
            rev_val += val[i];

        cout << rev_val << endl;
    }
}