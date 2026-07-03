#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1);

        for (int i = 1; i <= n; i++)
            make_set(i);
    }

    void make_set(int v) {
        parent[v] = v;
        sz[v] = 1;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);

        if (a != b) {
            if (sz[a] < sz[b])
                swap(a, b);

            parent[b] = a;
            sz[a] += sz[b];
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges;

    // {weight, u, v}
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }

    // for descending sort
    // sort(edges.begin(), edges.end(), greater<vector<int>>());
    
    sort(edges.begin(), edges.end());

    DSU dsu(n);

    long long mst_cost = 0;
    vector<pair<int, int>> mst_edges;

    for (auto &e : edges) {
        int w = e[0];
        int u = e[1];
        int v = e[2];

        if (dsu.find_set(u) != dsu.find_set(v)) {
            dsu.union_sets(u, v);
            mst_cost += w;
            mst_edges.push_back({u, v});
        }
    }

    cout << "MST Cost: " << mst_cost << '\n';

    // MST edges
    for (auto &e : mst_edges) {
        cout << e.first << " " << e.second << '\n';
    }

    return 0;
}