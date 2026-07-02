#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<long long>> edges;

    for (int i = 0; i < m; i++) {
        long long u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int src;
    cin >> src;

    vector<long long> dist(n + 1, INF);
    dist[src] = 0;

    for (int i = 1; i < n; i++) {
        bool updated = false;

        for (auto &e : edges) {
            long long u = e[0];
            long long v = e[1];
            long long w = e[2];

            if (dist[u] == INF) continue;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }

        if (!updated) break;
    }

    bool negCycle = false;

    for (auto &e : edges) {
        long long u = e[0];
        long long v = e[1];
        long long w = e[2];

        if (dist[u] == INF) continue;

        if (dist[u] + w < dist[v]) {
            negCycle = true;
            break;
        }
    }

    if (negCycle) {
        cout << "Negative Cycle Found\n";
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        cout << (dist[i] == INF ? -1 : dist[i]) << ' ';
    }
    cout << '\n';

    return 0;
}