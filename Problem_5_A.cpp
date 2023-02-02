#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<int> edges[10000];
int used[1000];

void dfs(int v) {
    used[v] = 1;
    
    for (auto u : edges[v])
        if (!used[u])
            dfs(u);
}

void add_edge(int u, int v) {
    edges[u].push_back(v);
}

int main() {
    int n, m;

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u - 1, v - 1);
        add_edge(v - 1, u - 1);
    }

    dfs(0);

    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;

        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
}