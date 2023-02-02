#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<int> edges[200001];
int dp[50001];
int used[50001];

int dfs(int v, int t) {
    if (v == t) {
        dp[v] = 1;
        return dp[v];
    }

    if (used[v])
        return dp[v];

    dp[v] = 0;
    used[v] = 1;

    for (auto u : edges[v])
        if (!used[u])
            dp[v] += dfs(u, t);
        else
            dp[v] += dp[u];

    return dp[v];
}

void add_edge(int u, int v) {
    edges[u].push_back(v);
}

int main() {
    int n, m, s, t;

    cin >> n >> m >> s >> t;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u - 1, v - 1);
    }

    int erg = dfs(s - 1, t - 1);

    cout << erg << endl;
}