#include <bits/stdc++.h>
using namespace std;

long long merge_sort(vector<int> &a, vector<int> &temp, int l, int r) {
    if (l >= r) return 0;

    int mid = l + (r - l) / 2;

    long long inv = 0;

    inv += merge_sort(a, temp, l, mid);
    inv += merge_sort(a, temp, mid + 1, r);

    int i = l;
    int j = mid + 1;
    int k = l;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
            inv += mid - i + 1;
        }
    }

    while (i <= mid) {
        temp[k++] = a[i++];
    }

    while (j <= r) {
        temp[k++] = a[j++];
    }

    for (int p = l; p <= r; p++) {
        a[p] = temp[p];
    }

    return inv;
}

long long inversion_count(vector<int> &a) {
    int n = (int)a.size();

    if (n == 0) return 0;

    vector<int> temp(n);
    return merge_sort(a, temp, 0, n - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << inversion_count(a) << '\n';

    return 0;
}