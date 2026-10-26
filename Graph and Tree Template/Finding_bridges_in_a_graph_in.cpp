/*
Tarjan’s Algorithm (Bridge Finding):

This algorithm is used to find all bridges (critical edges) in an undirected graph.
A bridge is an edge whose removal increases the number of connected components.
It works using DFS while maintaining two arrays: tin[] (time of insertion) and
low[] (lowest reachable discovery time). An edge (u, v) is a bridge if
low[v] > tin[u], meaning v’s subtree cannot reach any ancestor of u without
using this edge. The algorithm runs in O(N + M) time and O(N + M) space,
where N is the number of nodes and M is the number of edges.
*/
#include<bits/stdc++.h>
using namespace std;

vector<int> tin, low;
int cnt = 0;

void dfs(int node, int parent, int& timer, vector<int>& vis, vector<vector<int>>& graph)
{
    vis[node] = 1;
    tin[node] = low[node] = timer++;

    for(auto child : graph[node])
    {
        if(child == parent) continue;

        if(vis[child])
        {
            low[node] = min(low[node], tin[child]);
        }
        else
        {
            dfs(child, node, timer, vis, graph);
            low[node] = min(low[node], low[child]);

            if(low[child] > tin[node])
                cnt++; // bridge found(between u child and node) now you can add logic on the bridges 
        }
    }
}

int main()
{
    int n, m; 
    cin >> n >> m;

    vector<vector<int>> graph(n+1);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);

    while(m--)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> vis(n+1, 0);
    int timer = 0;

    for(int i = 1; i <= n; i++)
    {
        if(!vis[i])
            dfs(i, -1, timer, vis, graph);
    }

    cout << cnt << endl;
}