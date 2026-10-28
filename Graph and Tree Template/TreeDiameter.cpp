
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];
int dist[MAXN];
int farthestNode;

void dfs(int u, int p, int d) {
    dist[u] = d;

    if (d > dist[farthestNode]) {
        farthestNode = u;
    }

    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
    }
}

int findFarthest(int start, int n) {
    fill(dist + 1, dist + n + 1, -1);

    farthestNode = start;
    dfs(start, 0, 0);

    return farthestNode;
}

int treeDiameter(int n) {
    int endpoint1 = findFarthest(1, n);
    int endpoint2 = findFarthest(endpoint1, n);

    return dist[endpoint2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        // Clear the previous test case
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }

        // Read the tree
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        cout << treeDiameter(n) << '\n';
    }

    return 0;
}
