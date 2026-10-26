#include <bits/stdc++.h>
using namespace std;

class Dinic {
private:
    struct Edge {
        int to;
        long long cap;   // residual capacity
        long long orig;  // original capacity
    };

    int n;
    int source;
    int sink;
    bool flowComputed;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level;
    vector<int> ptr;

    void addEdge(int u, int v, long long cap) {
        Edge forward;
        forward.to = v;
        forward.cap = cap;
        forward.orig = cap;

        Edge backward;
        backward.to = u;
        backward.cap = 0;
        backward.orig = 0;

        adj[u].push_back((int)edges.size());
        edges.push_back(forward);
        adj[v].push_back((int)edges.size());
        edges.push_back(backward);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        queue<int> q;
        q.push(source);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                if (edges[id].cap > 0 && level[edges[id].to] == -1) {
                    level[edges[id].to] = level[u] + 1;
                    q.push(edges[id].to);
                }
            }
        }
        return level[sink] != -1;
    }

    long long dfs(int u, long long pushed) {
        if (pushed == 0) return 0;
        if (u == sink) return pushed;
        for (int &i = ptr[u]; i < (int)adj[u].size(); i++) {
            int id = adj[u][i];
            int v = edges[id].to;
            if (level[v] != level[u] + 1 || edges[id].cap == 0) continue;
            long long got = dfs(v, min(pushed, edges[id].cap));
            if (got == 0) continue;
            edges[id].cap -= got;
            edges[id ^ 1].cap += got;
            return got;
        }
        return 0;
    }

public:
    // graph[u] = list of {v, capacity}, nodes are 0..graph.size()-1
    Dinic(const vector<vector<pair<int,int>>> &graph, int s, int t) {
        n = (int)graph.size();
        source = s;
        sink = t;
        flowComputed = false;
        adj.assign(n, vector<int>());
        level.assign(n, 0);
        ptr.assign(n, 0);
        for (int u = 0; u < n; u++) {
            for (const pair<int,int> &p : graph[u]) {
                addEdge(u, p.first, p.second);
            }
        }
    }

    long long maxFlow() {
        for (Edge &e : edges) e.cap = e.orig;  // safe to call again
        flowComputed = true;

        long long flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(source, LLONG_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }

    // Call after maxFlow(). Prints the flow decomposed into source->sink paths.
    void printPaths() {
        if (!flowComputed) {
            cout << "Call maxFlow() first.\n";
            return;
        }

        int m = (int)edges.size();
        vector<long long> f(m, 0);
        for (int id = 0; id < m; id += 2) {
            f[id] = edges[id].orig - edges[id].cap;
        }

        int pathCount = 0;
        while (true) {
            vector<int> parentEdge(n, -1);
            vector<bool> visited(n, false);
            queue<int> q;
            q.push(source);
            visited[source] = true;
            while (!q.empty() && !visited[sink]) {
                int u = q.front();
                q.pop();
                for (int id : adj[u]) {
                    if (id % 2 == 0 && f[id] > 0 && !visited[edges[id].to]) {
                        visited[edges[id].to] = true;
                        parentEdge[edges[id].to] = id;
                        q.push(edges[id].to);
                    }
                }
            }
            if (!visited[sink]) break;

            vector<int> pathEdges;
            long long bottleneck = LLONG_MAX;
            int cur = sink;
            while (cur != source) {
                int id = parentEdge[cur];
                pathEdges.push_back(id);
                bottleneck = min(bottleneck, f[id]);
                cur = edges[id ^ 1].to;
            }
            reverse(pathEdges.begin(), pathEdges.end());

            for (int id : pathEdges) {
                f[id] -= bottleneck;
            }

            pathCount++;
            cout << "Path " << pathCount << " (flow " << bottleneck << "): " << source;
            for (int id : pathEdges) {
                cout << " -> " << edges[id].to;
            }
            cout << "\n";
        }
    }
};

int main() {
    int n = 6;
    vector<vector<pair<int,int>>> graph(n);
    graph[0].push_back({1, 10});
    graph[0].push_back({2, 10});
    graph[1].push_back({2, 2});
    graph[1].push_back({3, 4});
    graph[1].push_back({4, 8});
    graph[2].push_back({4, 9});
    graph[3].push_back({5, 10});
    graph[4].push_back({3, 6});

    int source = 0, sink = 5;

    Dinic d(graph, source, sink);
    cout << "Max flow: " << d.maxFlow() << "\n";

    // only when you need paths
    d.printPaths();

    return 0;
}


#include <bits/stdc++.h>
using namespace std;

class EdmondsKarp {
private:
    struct Edge {
        int to;
        long long cap;   // residual capacity
        long long orig;  // original capacity
    };

    int n;
    int source;
    int sink;
    bool flowComputed;
    vector<Edge> edges;
    vector<vector<int>> adj;

    void addEdge(int u, int v, long long cap) {
        Edge forward;
        forward.to = v;
        forward.cap = cap;
        forward.orig = cap;

        Edge backward;
        backward.to = u;
        backward.cap = 0;
        backward.orig = 0;

        adj[u].push_back((int)edges.size());
        edges.push_back(forward);
        adj[v].push_back((int)edges.size());
        edges.push_back(backward);
    }

public:
    // graph[u] = list of {v, capacity}, nodes are 0..graph.size()-1
    EdmondsKarp(const vector<vector<pair<int,int>>> &graph, int s, int t) {
        n = (int)graph.size();
        source = s;
        sink = t;
        flowComputed = false;
        adj.assign(n, vector<int>());
        for (int u = 0; u < n; u++) {
            for (const pair<int,int> &p : graph[u]) {
                addEdge(u, p.first, p.second);
            }
        }
    }

    long long maxFlow() {
        for (Edge &e : edges) e.cap = e.orig;  // safe to call again
        flowComputed = true;

        long long flow = 0;
        while (true) {
            // BFS to find the shortest augmenting path (fewest edges)
            vector<int> parentEdge(n, -1);
            vector<bool> visited(n, false);
            queue<int> q;
            q.push(source);
            visited[source] = true;
            while (!q.empty() && !visited[sink]) {
                int u = q.front();
                q.pop();
                for (int id : adj[u]) {
                    if (edges[id].cap > 0 && !visited[edges[id].to]) {
                        visited[edges[id].to] = true;
                        parentEdge[edges[id].to] = id;
                        q.push(edges[id].to);
                    }
                }
            }
            if (!visited[sink]) break;

            // Find bottleneck along the path
            long long bottleneck = LLONG_MAX;
            int cur = sink;
            while (cur != source) {
                int id = parentEdge[cur];
                bottleneck = min(bottleneck, edges[id].cap);
                cur = edges[id ^ 1].to;
            }

            // Augment
            cur = sink;
            while (cur != source) {
                int id = parentEdge[cur];
                edges[id].cap -= bottleneck;
                edges[id ^ 1].cap += bottleneck;
                cur = edges[id ^ 1].to;
            }
            flow += bottleneck;
        }
        return flow;
    }

    // Call after maxFlow(). Prints the flow decomposed into source->sink paths.
    void printPaths() {
        if (!flowComputed) {
            cout << "Call maxFlow() first.\n";
            return;
        }

        int m = (int)edges.size();
        vector<long long> f(m, 0);
        for (int id = 0; id < m; id += 2) {
            f[id] = edges[id].orig - edges[id].cap;
        }

        int pathCount = 0;
        while (true) {
            vector<int> parentEdge(n, -1);
            vector<bool> visited(n, false);
            queue<int> q;
            q.push(source);
            visited[source] = true;
            while (!q.empty() && !visited[sink]) {
                int u = q.front();
                q.pop();
                for (int id : adj[u]) {
                    if (id % 2 == 0 && f[id] > 0 && !visited[edges[id].to]) {
                        visited[edges[id].to] = true;
                        parentEdge[edges[id].to] = id;
                        q.push(edges[id].to);
                    }
                }
            }
            if (!visited[sink]) break;

            vector<int> pathEdges;
            long long bottleneck = LLONG_MAX;
            int cur = sink;
            while (cur != source) {
                int id = parentEdge[cur];
                pathEdges.push_back(id);
                bottleneck = min(bottleneck, f[id]);
                cur = edges[id ^ 1].to;
            }
            reverse(pathEdges.begin(), pathEdges.end());

            for (int id : pathEdges) {
                f[id] -= bottleneck;
            }

            pathCount++;
            cout << "Path " << pathCount << " (flow " << bottleneck << "): " << source;
            for (int id : pathEdges) {
                cout << " -> " << edges[id].to;
            }
            cout << "\n";
        }
    }
};

int main() {
    int n = 6;
    vector<vector<pair<int,int>>> graph(n);
    graph[0].push_back({1, 10});
    graph[0].push_back({2, 10});
    graph[1].push_back({2, 2});
    graph[1].push_back({3, 4});
    graph[1].push_back({4, 8});
    graph[2].push_back({4, 9});
    graph[3].push_back({5, 10});
    graph[4].push_back({3, 6});

    int source = 0, sink = 5;

    EdmondsKarp ek(graph, source, sink);
    cout << "Max flow: " << ek.maxFlow() << "\n";

    // only when you need paths
    ek.printPaths();

    return 0;
}