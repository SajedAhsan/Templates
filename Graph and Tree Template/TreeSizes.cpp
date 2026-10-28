
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];

int parent[MAXN];
int depth[MAXN];
int subtreeSize[MAXN];
int childCount[MAXN];
int leafCount[MAXN];

void dfs(int u, int p) {
    parent[u] = p;
    subtreeSize[u] = 1;
    childCount[u] = 0;
    leafCount[u] = 0;

    for (int v : adj[u]) {
        if (v == p) continue;

        depth[v] = depth[u] + 1;
        childCount[u]++;

        dfs(v, u);

        // Merge information from child v
        subtreeSize[u] += subtreeSize[v];
        leafCount[u] += leafCount[v];
    }

    // A leaf has no children (root included if it's the only node)
    if (childCount[u] == 0) {
        leafCount[u] = 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = 1;
    depth[root] = 0;

    dfs(root, 0);

    // Example output
    for (int i = 1; i <= n; i++) {
        cout << "Node " << i
             << ": parent=" << parent[i]
             << ", depth=" << depth[i]
             << ", subtreeSize=" << subtreeSize[i]
             << ", children=" << childCount[i]
             << ", leafCount=" << leafCount[i]
             << '\n';
    }

    return 0;
}
