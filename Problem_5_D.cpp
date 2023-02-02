#include <bits/stdc++.h>
using namespace std;

// Utility method to do DFS of the graph and count edge
// deletion for even forest
int dfs(vector<int> g[], int u, bool visit[], int& res) {
    visit[u] = true;
    int currComponentNode = 0;

    //  iterate over all neighbor of node u
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];

        if (visit[v])
            continue;

        // Count the number of nodes in a subtree
        int subtreeNodeCount = dfs(g, v, visit, res);

        // if returned node count is even, disconnect
        // the subtree and increase result by one.
        if (subtreeNodeCount % 2 == 0)
            res++;

        //  else add subtree nodes in current component
        else
            currComponentNode += subtreeNodeCount;
    }

    // number of nodes in current component and one for
    // current node
    return (currComponentNode + 1);
}

/*  method returns max edge that we can remove, after which
    each  connected component will have even number of
    vertices */
int maxEdgeRemovalToMakeForestEven(vector<int> g[], int N)
{
    // Create a visited array for DFS and make all nodes
    // unvisited in starting
    bool visit[N + 1];
    for (int i = 0; i <= N; i++)
        visit[i] = false;

    int res = 0; // Passed as reference

    //  calling the dfs from node-0
    dfs(g, 0, visit, res);

    return res;
}

// Utility function to add an undirected edge (u,v)
void addEdge(vector<int> g[], int u, int v)
{
    g[u].push_back(v);
    g[v].push_back(u);
}

//  Driver code to test above methods
int main()
{
    int edges[][2] = { {0, 2}, {0, 1}, {0, 4},
                      {2, 3}, {4, 5}, {5, 6},
                      {5, 7} };
    int N = sizeof(edges) / sizeof(edges[0]);
    vector<int> g[N + 1];
    for (int i = 0; i < N; i++)
        addEdge(g, edges[i][0], edges[i][1]);

    cout << maxEdgeRemovalToMakeForestEven(g, N);
    return 0;
}