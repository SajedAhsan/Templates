#include <bits/stdc++.h>
using namespace std;

class Dinic {
private:
    struct Edge {
        int to;
        long long cap;  
        long long orig;  
    };

    int n;
    int source;
    int sink;
    bool flowComputed;

    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level;
    vector<int> ptr;

    unordered_map<long long, int> edgeId;

    long long getKey(int u, int v) const {
        return 1LL * u * n + v;
    }

    void addEdge(int u, int v, long long cap) {
        if (u < 0 || u >= n || v < 0 || v >= n || cap < 0) {
            throw invalid_argument("Invalid edge or capacity");
        }

        long long key = getKey(u, v);
        auto it = edgeId.find(key);

        if (it != edgeId.end()) {
            int id = it->second;
            edges[id].orig += cap;
            edges[id].cap += cap;
            flowComputed = false;
            return;
        }

        Edge forward;
        forward.to = v;
        forward.cap = cap;
        forward.orig = cap;

        Edge backward;
        backward.to = u;
        backward.cap = 0;
        backward.orig = 0;

        int id = (int)edges.size();

        adj[u].push_back(id);
        edges.push_back(forward);

        adj[v].push_back(id + 1);
        edges.push_back(backward);

        edgeId[key] = id;
        flowComputed = false;
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
                int v = edges[id].to;
                if (edges[id].cap > 0 && level[v] == -1) {
                    level[v] = level[u] + 1;
                    q.push(v);
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
    Dinic(const vector<vector<pair<int, int>>> &graph, int s, int t) {
        n = (int)graph.size();
        source = s;
        sink = t;
        flowComputed = false;

        if (n == 0 || source < 0 || source >= n || sink < 0 || sink >= n) {
            throw invalid_argument("Invalid graph, source, or sink");
        }

        adj.assign(n, vector<int>());
        level.assign(n, -1);
        ptr.assign(n, 0);

        for (int u = 0; u < n; u++) {
            for (const pair<int, int> &p : graph[u]) {
                addEdge(u, p.first, p.second);
            }
        }
        flowComputed = false;
    }

    void increaseCapacity(int u, int v, long long val) {
        if (u < 0 || u >= n || v < 0 || v >= n || val < 0) {
            throw invalid_argument("Invalid vertices or capacity increment");
        }
        if (val == 0) return;

        long long key = getKey(u, v);
        auto it = edgeId.find(key);

        if (it == edgeId.end()) {
            addEdge(u, v, val);
        } else {
            int id = it->second;
            edges[id].orig += val;
            edges[id].cap += val;
            flowComputed = false;
        }
    }

    long long continueFlow() {
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

    long long maxFlow() {
        for (Edge &e : edges) e.cap = e.orig;
        return continueFlow();
    }

    void addResidual(int u, int v, long long val) {
        edges[edgeId[getKey(u, v)]].cap += val;
    }

    vector<long long> saveState() const {
        vector<long long> s(edges.size());
        for (size_t i = 0; i < edges.size(); i++) s[i] = edges[i].cap;
        return s;
    }

    void loadState(const vector<long long> &s) {
        for (size_t i = 0; i < edges.size(); i++) edges[i].cap = s[i];
    }

    void printPaths() {
        if (!flowComputed) {
            cout << "Call maxFlow() first after the latest graph update.\n";
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
                    int v = edges[id].to;
                    if (id % 2 == 0 && f[id] > 0 && !visited[v]) {
                        visited[v] = true;
                        parentEdge[v] = id;
                        q.push(v);
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
            for (int id : pathEdges) f[id] -= bottleneck;

            pathCount++;
            cout << "Path " << pathCount << " (flow " << bottleneck << "): " << source;
            for (int id : pathEdges) cout << " -> " << edges[id].to;
            cout << '\n';
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k;
    cin >> m >> n >> k;
    int S = 0, T = m + n + 1;
    vector<vector<pair<int, int>>> graph(T + 1);

    for (int i = 1; i <= m; i++) 
        graph[S].push_back({i, 1});
    for (int j = 1; j <= n; j++) 
        graph[m + j].push_back({T, 1});
    for (int i = 0; i < k; i++) 
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back({m + y, 1});
    }

    Dinic d(graph, S, T);
    long long ans = d.maxFlow();               
    vector<long long> saved = d.saveState();   
    long long best = 0;                        

    for (int s = 1; s <= m && best < 2; s++) {
        d.loadState(saved);                    
        d.addResidual(S, s, 2);                
        best = max(best, d.continueFlow());    
    }

    cout << ans + best << endl;

}