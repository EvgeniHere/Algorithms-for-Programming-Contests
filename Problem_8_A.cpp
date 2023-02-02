#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100002;
vector<int> edges[MAXN];
bool used[MAXN];
int dp[MAXN];

void dfs(int u) {
    used[u] = true;

    for (auto v: edges[u]) {
        if (!used[v])
            dfs(v);

        dp[u] = max(dp[u], dp[v] + 1);
    }
}

int findLongestPath(int n) {
    for (int i = 1; i <= n; i++) {
        dfs(i);
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }

    return ans;
}

void addEdge(int u, int v) {
    edges[u].push_back(v);
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int b, e;
        cin >> b >> e;
        addEdge(b, e);
    }

    cout << findLongestPath(n) << endl;
    return 0;
}