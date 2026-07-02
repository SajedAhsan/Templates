#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

long long tree[4 * N];
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

void update(int node, int l, int r, int idx, int val)
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

    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

long long query(int node, int l, int r, int ql, int qr)
{
    // No overlap
    if (r < ql || qr < l)
        return 0;

    // Complete overlap
    if (ql <= l && r <= qr)
        return tree[node];

    int mid = (l + r) / 2;

    return query(2 * node + 1, l, mid, ql, qr) +
           query(2 * node + 2, mid + 1, r, ql, qr);
}

int main()
{

}

// lazy segemen tree

// const int N = 2e5 + 5;

// long long tree[4 * N];
// long long lazy[4 * N];
// int arr[N];

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

// void push(int node, int l, int r)
// {
//     if (lazy[node] == 0)
//         return;

//     tree[node] += (r - l + 1) * lazy[node];

//     if (l != r)
//     {
//         lazy[2 * node + 1] += lazy[node];
//         lazy[2 * node + 2] += lazy[node];
//     }

//     lazy[node] = 0;
// }

// void update(int node, int l, int r, int ql, int qr, long long val)
// {
//     push(node, l, r);

//     if (r < ql || qr < l)
//         return;

//     if (ql <= l && r <= qr)
//     {
//         lazy[node] += val;
//         push(node, l, r);
//         return;
//     }

//     int mid = (l + r) / 2;

//     update(2 * node + 1, l, mid, ql, qr, val);
//     update(2 * node + 2, mid + 1, r, ql, qr, val);

//     tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
// }

// long long query(int node, int l, int r, int ql, int qr)
// {
//     push(node, l, r);

//     if (r < ql || qr < l)
//         return 0;

//     if (ql <= l && r <= qr)
//         return tree[node];

//     int mid = (l + r) / 2;

//     return query(2 * node + 1, l, mid, ql, qr) +
//            query(2 * node + 2, mid + 1, r, ql, qr);
// }