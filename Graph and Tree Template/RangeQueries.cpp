#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
vector<int> adj[N];
int tin[N], tout[N];
int timer = 0;
long long value[N];
long long tree[4 * N];
long long lazy[4 * N];
int arr[N];

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

    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

void push(int node, int l, int r)
{
    if (lazy[node] == 0)
        return;

    if(lazy[node]%2)
        tree[node] = (r - l + 1) - tree[node];

    if (l != r)
    {
        lazy[2 * node + 1] += lazy[node];
        lazy[2 * node + 2] += lazy[node];
    }

    lazy[node] = 0;
}

void update(int node, int l, int r, int ql, int qr)
{
    push(node, l, r);

    if (r < ql || qr < l)
        return;

    if (ql <= l && r <= qr)
    {
        lazy[node] += 1;
        push(node, l, r);
        return;
    }

    int mid = (l + r) / 2;

    update(2 * node + 1, l, mid, ql, qr);
    update(2 * node + 2, mid + 1, r, ql, qr);

    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

long long query(int node, int l, int r, int ql, int qr)
{
    push(node, l, r);

    if (r < ql || qr < l)
        return 0;

    if (ql <= l && r <= qr)
        return tree[node];

    int mid = (l + r) / 2;

    return query(2 * node + 1, l, mid, ql, qr) +
           query(2 * node + 2, mid + 1, r, ql, qr);
}

void dfs(int u, int p)
{
    tin[u] = timer;
    arr[timer] = value[u];
    timer++;

    for (int v : adj[u])
    {
        if (v == p)
            continue;

        dfs(v, u);
    }

    tout[u] = timer;
}


int main()
{
    int n; cin >> n;
    for(int i = 2; i <= n; i++)
    {
        int x; cin >> x;
        adj[i].push_back(x);
        adj[x].push_back(i);
    }
    for(int i = 1; i <= n; i++)
        cin >> value[i];


    dfs(1,0);
    build(0,0,n-1);
    int q; cin >> q;
    while(q--)
    {
        string type; cin >> type;
        int u; cin >> u;
        if(type == "get")
        {
            cout << query(0,0,n-1,tin[u],tout[u] - 1) << endl;
        }
        else
        {
            update(0,0,n-1,tin[u],tout[u] - 1);
        }
    }
}


// #include <bits/stdc++.h>
// using namespace std;

// const int MAXN = 200005;

// vector<int> adj[MAXN];
// int tin[MAXN], tout[MAXN];
// int timer = 0;

// long long value[MAXN];
// long long arr[MAXN];
// long long tree[4 * MAXN];

// void build(int node, int l, int r)
// {
//     if (l == r)
//     {
//         tree[node] = arr[l];
//         return;
//     }

//     int mid = (l + r) / 2;

//     build(2 * node + 1, l, mid);
//     build(2 * node + 2, mid + 1, r);

//     tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
// }

// void update(int node, int l, int r, int idx, long long val)
// {
//     if (l == r)
//     {
//         tree[node] = val;
//         return;
//     }

//     int mid = (l + r) / 2;

//     if (idx <= mid)
//         update(2 * node + 1, l, mid, idx, val);
//     else
//         update(2 * node + 2, mid + 1, r, idx, val);

//     tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
// }

// long long query(int node, int l, int r, int ql, int qr)
// {

//     if (r < ql || qr < l)
//         return 0;

//     if (ql <= l && r <= qr)
//         return tree[node];

//     int mid = (l + r) / 2;

//     return query(2 * node + 1, l, mid, ql, qr) +
//            query(2 * node + 2, mid + 1, r, ql, qr);
// }

// void dfs(int u, int p)
// {
//     tin[u] = timer;
//     arr[timer] = value[u];
//     timer++;

//     for (int v : adj[u])
//     {
//         if (v == p)
//             continue;

//         dfs(v, u);
//     }

//     tout[u] = timer;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int n, q;
//     cin >> n >> q;

//     for (int i = 1; i <= n; i++)
//         cin >> value[i];

//     for (int i = 0; i < n - 1; i++)
//     {
//         int u, v;
//         cin >> u >> v;

//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }

//     timer = 0;
//     dfs(1, 0);

//     build(0, 0, n - 1);

//     while (q--)
//     {
//         int type;
//         cin >> type;

//         if (type == 1)
//         {
//             int u;
//             long long val;
//             cin >> u >> val;
//             update(0, 0, n - 1, tin[u], val);
//         }
//         else
//         {
//             int u;
//             cin >> u;
//             cout << query(0, 0, n - 1, tin[u], tout[u] - 1) << endl;
//         }
//     }

//     return 0;
// }