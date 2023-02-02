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
    dst.insert({ d[s], s });

    while (!dst.empty()) {
        int v = dst.begin()->second;
        dst.erase(dst.begin());

        for (auto e : edges[v])
            if (d[v] + e.cost < d[e.u]) {
                dst.erase({ d[e.u], e.u });
                d[e.u] = d[v] + e.cost;
                dst.insert({ d[e.u], e.u });
            }
    }
}

int main() {
    int s, t, f;

    cin >> s >> t >> f;

    vector<int> finals(f);
    for (int i = 0; i < f; i++) {
        cin >> finals[i];
    }

    for (int i = 0; i < t; i++) {
        int b, a, p;

        cin >> b >> a >> p;

        edges[b - 1].push_back({ a - 1, p });
    }

    int index = 0;
    int min_points = INF;

    dijkstra(0, s - 1);

    for (int i = 0; i < f; i++) {
        if (min_points > d[finals[i] - 1]) {
            min_points = d[finals[i] - 1];
            index = finals[i];
        }
    }

    if (min_points == INF)
        cout << "IMPOSSIBLE" << endl;
    else
        cout << min_points << " " << index << endl;
}