#include <iostream>
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
int used[MAXN];

struct edge {
    int u, thicc;
};

vector<edge> edges[MAXN];

int dfs(int u, int t) {
    used[u] = 1;
    int combOrs = 0;

    for (auto v : edges[u]) {
        if (used[v.u])
            continue;

        combOrs += dfs(v.u, v.thicc);
    }

    if (combOrs == 0)
        return t;

    return min(combOrs, t);
}

void addEdge(int u, int v, int c) {
    edges[u].push_back({ v, c });
}

int main() {
    int n;

    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        addEdge(a, b, t);
        addEdge(b, a, t);
    }

    cout << dfs(0, 100000000) << endl;
}