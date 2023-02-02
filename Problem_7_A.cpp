#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<int> edges[150001];
int used[50000];

bool dfs(int v, int comp) {
    used[v] = 1;

    if (v == comp)
        return true;

    for (auto u : edges[v]) {
        if (used[u])
            continue;

        if (dfs(u, comp))
            return true;
    }

    return false;
}

void add_edge(int u, int v) {
    edges[u].push_back(v);
}

void rem_edge(int u, int v) {
    edges[u].erase(remove(edges[u].begin(), edges[u].end(), v), edges[u].end());
}

int main() {
    int n, m, o;

    cin >> n >> m >> o;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u - 1, v - 1);
        add_edge(v - 1, u - 1);
    }

    for (int i = 0; i < o; i++) {
        string op;
        int a, b;

        cin >> op >> a >> b;

        a--;
        b--;

        if (op == "cut") {
            rem_edge(a, b);
            rem_edge(b, a);
        }

        if (op == "ask") {
            for (int i = 0; i < 50000; i++)
                used[i] = 0;

            if (a == b)
                cout << "YES" << endl;
            else if (dfs(a, b))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
}