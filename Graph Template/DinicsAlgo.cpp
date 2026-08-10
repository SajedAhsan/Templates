#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    int cap;
    int originalCap;
};

class Dinic {
public:
    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;

    Dinic(int n) : n(n) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void addEdge(int u, int v, int cap) {
        Edge a = {v, (int)adj[v].size(), cap, cap};
        Edge b = {u, (int)adj[u].size(), 0, 0};

        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);

        queue<int> q;
        q.push(s);
        level[s] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto &e : adj[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[t] != -1;
    }

    int dfs(int u, int t, int flow) {
        if (u == t)
            return flow;

        for (int &i = ptr[u]; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];

            if (e.cap > 0 && level[e.to] == level[u] + 1) {

                int pushed = dfs(
                    e.to,
                    t,
                    min(flow, e.cap)
                );

                if (pushed > 0) {
                    e.cap -= pushed;
                    adj[e.to][e.rev].cap += pushed;

                    return pushed;
                }
            }
        }

        return 0;
    }

    int maxFlow(int s, int t) {
        const int INF = 1e9;
        int flow = 0;

        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);

            while (int pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }

        return flow;
    }

    // Prints one path carrying flow from s to t
    bool dfsPath(int u, int t, vector<int>& path, vector<bool>& vis) {
        if (u == t)
            return true;

        vis[u] = true;

        for (auto &e : adj[u]) {

            // Original edge has flow if:
            // original capacity > remaining capacity
            int usedFlow = e.originalCap - e.cap;

            if (e.originalCap > 0 &&
                usedFlow > 0 &&
                !vis[e.to]) {

                path.push_back(e.to);

                if (dfsPath(e.to, t, path, vis))
                    return true;

                path.pop_back();
            }
        }

        return false;
    }

    // Print all flow paths
    void printPaths(int s, int t) {
        cout << "\nFlow Paths:\n";

        while (true) {
            vector<int> path;
            vector<bool> vis(n, false);

            path.push_back(s);

            if (!dfsPath(s, t, path, vis))
                break;

            cout << "Path: ";

            for (int i = 0; i < path.size(); i++) {
                cout << path[i];

                if (i + 1 < path.size())
                    cout << " -> ";
            }

            cout << '\n';

            // Remove one unit of flow from this path
            for (int i = 0; i + 1 < path.size(); i++) {
                int u = path[i];
                int v = path[i + 1];

                for (auto &e : adj[u]) {
                    if (e.to == v && e.originalCap > 0) {
                        e.cap++;
                        break;
                    }
                }
            }
        }
    }
};

int main() {
    Dinic dinic(6);

    dinic.addEdge(0, 1, 16);
    dinic.addEdge(0, 2, 13);
    dinic.addEdge(1, 2, 10);
    dinic.addEdge(2, 1, 4);
    dinic.addEdge(1, 3, 12);
    dinic.addEdge(3, 2, 9);
    dinic.addEdge(2, 4, 14);
    dinic.addEdge(4, 3, 7);
    dinic.addEdge(3, 5, 20);
    dinic.addEdge(4, 5, 4);

    int maxflow = dinic.maxFlow(0, 5);

    cout << "Maximum Flow = " << maxflow << '\n';

    dinic.printPaths(0, 5);

    return 0;
}