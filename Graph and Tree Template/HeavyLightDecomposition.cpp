
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

vector<int> adj[N];

int parent[N], depth[N];
int subtreeSize[N], heavy[N];
int head[N], pos[N];

int curPos = 0;

long long value[N];
long long arr[N];
long long tree[4 * N];

// --------------------------------
// Segment Tree: Build
// --------------------------------
void build(int node, int l, int r)
{
    if (l == r)
    {
        tree[node] = arr[l];
        return;
    }

    int mid = (l + r) / 2;

    build(2 * node + 1, l, mid);
    build(2 * node + 2, mid + 1, r);

    tree[node] = tree[2 * node + 1]
               + tree[2 * node + 2];
}

// --------------------------------
// Segment Tree: Point Update
// --------------------------------
void update(int node, int l, int r, int idx, long long val)
{
    if (l == r)
    {
        tree[node] = val;
        return;
    }

    int mid = (l + r) / 2;

    if (idx <= mid)
        update(2 * node + 1, l, mid, idx, val);
    else
        update(2 * node + 2, mid + 1, r, idx, val);

    tree[node] = tree[2 * node + 1]
               + tree[2 * node + 2];
}

// --------------------------------
// Segment Tree: Range Sum Query
// --------------------------------
long long query(int node, int l, int r, int ql, int qr)
{
    if (r < ql || qr < l)
        return 0;

    if (ql <= l && r <= qr)
        return tree[node];

    int mid = (l + r) / 2;

    return query(2 * node + 1, l, mid, ql, qr)
         + query(2 * node + 2, mid + 1, r, ql, qr);
}

// --------------------------------
// 1. DFS: Find Heavy Child
// --------------------------------
void dfs(int u, int p)
{
    parent[u] = p;
    subtreeSize[u] = 1;
    heavy[u] = -1;

    int maxSize = 0;

    for (int v : adj[u])
    {
        if (v == p)
            continue;

        depth[v] = depth[u] + 1;

        dfs(v, u);

        subtreeSize[u] += subtreeSize[v];

        if (subtreeSize[v] > maxSize)
        {
            maxSize = subtreeSize[v];
            heavy[u] = v;
        }
    }
}

// --------------------------------
// 2. Decompose the Tree
// --------------------------------
void decompose(int u, int h)
{
    head[u] = h;
    pos[u] = curPos;

    arr[curPos] = value[u];
    curPos++;

    if (heavy[u] != -1)
        decompose(heavy[u], h);

    for (int v : adj[u])
    {
        if (v == parent[u] || v == heavy[u])
            continue;

        decompose(v, v);
    }
}

// --------------------------------
// 3. Initialize HLD
// Root = 1
// --------------------------------
void init(int n)
{
    curPos = 0;
    depth[1] = 0;

    dfs(1, 0);
    decompose(1, 1);

    build(0, 0, n - 1);
}

// --------------------------------
// 4. Path Sum Query
// --------------------------------
long long pathQuery(int u, int v)
{
    long long ans = 0;

    while (head[u] != head[v])
    {
        if (depth[head[u]] < depth[head[v]])
            swap(u, v);

        ans += query(
            0, 0, curPos - 1,
            pos[head[u]], pos[u]
        );

        u = parent[head[u]];
    }

    if (depth[u] > depth[v])
        swap(u, v);

    ans += query(
        0, 0, curPos - 1,
        pos[u], pos[v]
    );

    return ans;
}

// --------------------------------
// 5. Point Update
// --------------------------------
void updateNode(int u, long long val)
{
    value[u] = val;

    update(0, 0, curPos - 1, pos[u], val);
}

// --------------------------------
// 6. LCA using HLD
// --------------------------------
int lca(int u, int v)
{
    while (head[u] != head[v])
    {
        if (depth[head[u]] < depth[head[v]])
            swap(u, v);

        u = parent[head[u]];
    }

    return (depth[u] < depth[v] ? u : v);
}

// --------------------------------
// Main
// --------------------------------
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;

        adj[i].push_back(p);
        adj[p].push_back(i);
    }

    for (int i = 1; i <= n; i++)
        cin >> value[i];

    init(n);

    int q;
    cin >> q;

    while (q--)
    {
        string type;
        cin >> type;

        if (type == "get")
        {
            int u, v;
            cin >> u >> v;

            cout << pathQuery(u, v) << '\n';
        }
        else if (type == "set")
        {
            int u;
            long long val;
            cin >> u >> val;

            updateNode(u, val);
        }
        else if (type == "lca")
        {
            int u, v;
            cin >> u >> v;

            cout << lca(u, v) << '\n';
        }
    }

    return 0;
}
