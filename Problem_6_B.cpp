#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> edges[10000];
int used[10000];

void dfs(int v, int cur_deep) {
    used[v] = cur_deep;

    for (auto u : edges[v])
        if (!used[u.first])
            dfs(u.first, cur_deep + u.second);
}

void add_edge(int u, int v, int h) {
    edges[u].push_back({ v, h });
}

int main() {
    int n;

    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int p, h;
        cin >> p >> h;
        add_edge(p - 1, i + 1, h);
    }

    dfs(0, 0);

    int max_deep = 0;

    for (auto u: used) {
        max_deep = max(u, max_deep);
    }

    cout << max_deep << endl;
}