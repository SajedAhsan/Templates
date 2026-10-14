#include <bits/stdc++.h>
using namespace std;

class Kosaraju {
public:
    void DFS1(int u, vector<vector<int>> &adj,
              vector<bool> &visited, stack<int> &st) {
        visited[u] = true;

        for (int v : adj[u]) {
            if (!visited[v]) {
                DFS1(v, adj, visited, st);
            }
        }

        st.push(u);
    }

    void DFS2(int u, vector<vector<int>> &revAdj,
              vector<bool> &visited, vector<int> &scc) {
        visited[u] = true;
        scc.push_back(u);

        for (int v : revAdj[u]) {
            if (!visited[v]) {
                DFS2(v, revAdj, visited, scc);
            }
        }
    }

    vector<vector<int>> getSCCs(int V, vector<vector<int>> &adj) {
        vector<bool> visited(V, false);
        stack<int> st;

        // Step 1: DFS on the original graph
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS1(i, adj, visited, st);
            }
        }

        // Step 2: Build the reversed graph
        vector<vector<int>> revAdj(V);

        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                revAdj[v].push_back(u);
            }
        }

        // Step 3: Reset visited
        fill(visited.begin(), visited.end(), false);

        // Step 4: DFS on the reversed graph
        vector<vector<int>> SCCs;

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            if (!visited[u]) {
                vector<int> scc;
                DFS2(u, revAdj, visited, scc);
                SCCs.push_back(scc);
            }
        }

        return SCCs;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    Kosaraju obj;
    vector<vector<int>> SCCs = obj.getSCCs(V, adj);

    cout << "Total SCCs: " << SCCs.size() << '\n';

    for (int i = 0; i < (int)SCCs.size(); i++) {
        cout << "SCC " << i + 1 << ": ";

        for (int node : SCCs[i]) {
            cout << node << " ";
        }

        cout << '\n';
    }

    return 0;
}


// iterative

// #include <bits/stdc++.h>
// using namespace std;

// class Kosaraju {
// public:
//     vector<vector<int>> getSCCs(int V, const vector<vector<int>> &adj) {
//         vector<bool> visited(V, false);
//         vector<int> order;
//         order.reserve(V);

//         // Pass 1: iterative DFS on the original graph to get finish order
//         for (int s = 0; s < V; s++) {
//             if (visited[s]) continue;

//             vector<pair<int, int>> stk; // (node, next edge index)
//             stk.push_back({s, 0});
//             visited[s] = true;

//             while (!stk.empty()) {
//                 int u = stk.back().first;
//                 int &i = stk.back().second;

//                 if (i < (int)adj[u].size()) {
//                     int v = adj[u][i++];
//                     if (!visited[v]) {
//                         visited[v] = true;
//                         stk.push_back({v, 0});
//                     }
//                 } else {
//                     order.push_back(u); // u finished
//                     stk.pop_back();
//                 }
//             }
//         }

//         // Build the reversed graph
//         vector<vector<int>> revAdj(V);
//         for (int u = 0; u < V; u++)
//             for (int v : adj[u])
//                 revAdj[v].push_back(u);

//         // Pass 2: process nodes in decreasing finish time on the reversed graph
//         fill(visited.begin(), visited.end(), false);
//         vector<vector<int>> SCCs;

//         for (int k = V - 1; k >= 0; k--) {
//             int s = order[k];
//             if (visited[s]) continue;

//             vector<int> scc;
//             vector<int> stk = {s};
//             visited[s] = true;

//             while (!stk.empty()) {
//                 int u = stk.back();
//                 stk.pop_back();
//                 scc.push_back(u);

//                 for (int v : revAdj[u]) {
//                     if (!visited[v]) {
//                         visited[v] = true;
//                         stk.push_back(v);
//                     }
//                 }
//             }

//             SCCs.push_back(move(scc));
//         }

//         return SCCs;
//     }
// };

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int V, E;
//     cin >> V >> E;

//     vector<vector<int>> adj(V);
//     for (int i = 0; i < E; i++) {
//         int u, v;
//         cin >> u >> v;
//         adj[u].push_back(v);
//     }

//     Kosaraju obj;
//     vector<vector<int>> SCCs = obj.getSCCs(V, adj);

//     cout << "Total SCCs: " << SCCs.size() << '\n';
//     for (int i = 0; i < (int)SCCs.size(); i++) {
//         cout << "SCC " << i + 1 << ": ";
//         for (int node : SCCs[i]) cout << node << " ";
//         cout << '\n';
//     }

//     return 0;
// }