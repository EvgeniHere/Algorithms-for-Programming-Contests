#include <iostream>
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 200000;

struct edge {
    int u, cost;
};

vector<edge> edges[MAXN];

bool martinsTurn = 1;

int dfs(edge u) {
    edge nextEdge = u;

    if (martinsTurn) {
        int maxCost = u.cost;
        for (auto v : edges[u.u]) {
            if (v.cost <= maxCost)
                continue;

            maxCost = v.cost;
            nextEdge = v;
        }
    } else {
        int minCost = 100000000;
        for (auto v : edges[u.u]) {
            if (v.cost >= minCost)
                continue;

            minCost = v.cost;
            nextEdge = v;
        }

        if (nextEdge.u == u.u)
            return nextEdge.u;
    }

    martinsTurn++;
    martinsTurn %= 2;

    return dfs(nextEdge);
}

void addEdge(int u, int v, int c) {
    edges[u].push_back({ v, c });
}

int main() {
    int n;

    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, c;
        cin >> a >> c;
        a--;
        addEdge(a, i, c);
    }

    cout << dfs({0, 1}) << endl;
}