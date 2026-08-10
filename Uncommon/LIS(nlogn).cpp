#include <bits/stdc++.h>
using namespace std;

int LIS(vector<int>& a) {
    vector<int> v;

    for (int x : a) {
        auto it = lower_bound(v.begin(), v.end(), x);

        if (it == v.end())
            v.push_back(x);
        else
            *it = x;
    }

    return v.size();
}

vector<int> getLIS(vector<int>& a) {
    int n = a.size();

    vector<int> tail;       // values
    vector<int> tailIdx;    // indices in a
    vector<int> parent(n, -1);

    for (int i = 0; i < n; i++) {
        int pos = lower_bound(tail.begin(), tail.end(), a[i]) - tail.begin();

        if (pos == tail.size()) {
            tail.push_back(a[i]);
            tailIdx.push_back(i);
        } else {
            tail[pos] = a[i];
            tailIdx[pos] = i;
        }

        // Previous element of current LIS
        if (pos > 0)
            parent[i] = tailIdx[pos - 1];
    }

    // Reconstruct LIS
    vector<int> lis;

    int cur = tailIdx.back();

    while (cur != -1) {
        lis.push_back(a[cur]);
        cur = parent[cur];
    }

    reverse(lis.begin(), lis.end());

    return lis;
}
int main(){}