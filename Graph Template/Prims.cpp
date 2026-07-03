#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // for descending 
    // priority_queue<vector<int>> pq;

    priority_queue<
        vector<int>,
        vector<vector<int>>,
        greater<vector<int>>
    > pq;

    vector<bool> vis(n + 1, false);
    vector<pair<int, int>> mst_edges;

    long long mst_cost = 0;

    // {weight, node, parent}
    pq.push({0, 1, -1});

    while (!pq.empty()) {
        vector<int> cur = pq.top();
        pq.pop();

        int w = cur[0];
        int u = cur[1];
        int par = cur[2];

        if (vis[u])
            continue;

        vis[u] = true;
        mst_cost += w;

        if (par != -1)
            mst_edges.push_back({par, u});

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int wt = edge.second;

            if (!vis[v])
                pq.push({wt, v, u});
        }
    }

    if ((int)mst_edges.size() != n - 1) {
        cout << "Graph is not connected\n";
        return 0;
    }

    cout << "MST Cost: " << mst_cost << '\n';

    // MST edges
    for (auto &e : mst_edges) {
        cout << e.first << " " << e.second << '\n';
    }

    return 0;
}