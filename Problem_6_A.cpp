#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
int d[1000000];

struct edge {
    int u, cost;
};

vector<edge> edges[100000];

void dijkstra(int s, int n) {
    fill(d, d + n + 1, INF);
    d[s] = 0;

    set<pair<int, int>> dst;
    dst.insert({d[s], s});

    while (!dst.empty()) {
        int v = dst.begin()->second;
        dst.erase(dst.begin());

        for (auto e: edges[v])
            if (d[v] + e.cost < d[e.u]) {
                dst.erase({d[e.u], e.u});
                d[e.u] = d[v] + e.cost;
                dst.insert({d[e.u], e.u});
            }
    }
}

int main() {
    int n, m;

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        char l;

        cin >> u >> v >> l;

        edges[u-1].push_back({v-1, l == 'l' ? 1 : 0});
    }

    dijkstra(0, n - 1);

    if (d[n - 1] == INF)
        cout << -1 << endl;
    else
        cout << d[n - 1] << endl;
}