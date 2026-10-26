#include <bits/stdc++.h>
using namespace std;

/*
 * Binary Lifting (LCA) - beginner friendly template
 * --------------------------------------------------
 * Idea: up[v][j] = the 2^j-th ancestor of v.
 *   up[v][0] = parent, up[v][1] = grandparent, up[v][2] = 4 levels up, ...
 *
 * You pass the graph (adjacency list) from outside:
 *     BinaryLifting bl(adj, root);
 *
 * Complexity: build O(N log N), each query O(log N).
 * Nodes are 0-indexed. Root's parent is the root itself.
 * Uses BFS (no recursion), so no stack overflow on deep trees.
 */
class BinaryLifting {
public:
    int n;                       // current number of nodes
    int LOG;                     // number of levels in the table
    vector<vector<int>> up;      // up[v][j] = 2^j-th ancestor of v
    vector<int> depth;           // depth[root] = 0

    // adj      : adjacency list of the tree (undirected, 0-indexed)
    // root     : root node
    // maxNodes : only needed if you will call add_leaf (max size of the tree)
    BinaryLifting(const vector<vector<int>>& adj, int root = 0, int maxNodes = -1) {
        n = adj.size();
        if (maxNodes < n) maxNodes = n;
        LOG = 1;
        while ((1 << LOG) <= maxNodes) LOG++;

        up.assign(n, vector<int>(LOG, root));
        depth.assign(n, 0);
        build(adj, root);
    }

    // add a new leaf under node 'parent'; returns the new node's id
    int add_leaf(int parent) {
        int v = n++;
        up.push_back(vector<int>(LOG, 0));
        depth.push_back(depth[parent] + 1);
        fill_up(v, parent);
        return v;
    }

    // k-th ancestor of v (returns root if k is too big)
    int kth_ancestor(int v, int k) const {
        for (int j = 0; j < LOG; j++)
            if (k >> j & 1) v = up[v][j];
        return v;
    }

    // lowest common ancestor of u and v
    int lca(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        u = kth_ancestor(u, depth[u] - depth[v]);   // 1) same depth
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; j--) {        // 2) jump together
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];                            // parent = LCA
    }

    // number of edges on the path u - v
    int dist(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    // is u an ancestor of v?
    bool is_ancestor(int u, int v) const {
        return depth[u] <= depth[v] && kth_ancestor(v, depth[v] - depth[u]) == u;
    }

private:
    // fill row of v given its parent p
    void fill_up(int v, int p) {
        up[v][0] = p;
        for (int j = 1; j < LOG; j++)
            up[v][j] = up[up[v][j - 1]][j - 1];
    }

    // BFS from root, fills depth and up
    void build(const vector<vector<int>>& adj, int root) {
        vector<bool> seen(n, false);
        queue<int> q;
        q.push(root);
        seen[root] = true;
        fill_up(root, root);          // root points to itself

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : adj[v]) {
                if (seen[u]) continue;
                seen[u] = true;
                depth[u] = depth[v] + 1;
                fill_up(u, v);        // v is the parent of u
                q.push(u);
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input: n, then n-1 edges (0-indexed), then q queries "u v"
    int n, q;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    BinaryLifting bl(adj, 0);       // pass graph + root
    // BinaryLifting bl(adj, 0, maxNodes);  // use this if you need add_leaf

    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << bl.lca(u, v) << "\n";
    }
    return 0;
}
