#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
vector<int> spf(N);

void build_spf() {
    for (int i = 1; i < N; i++) spf[i] = i;

    for (int i = 2; i * i < N; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < N; j += i) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

vector<int> get_factors(int n) {
    vector<int> factors;

    while (n != 1) {
        factors.push_back(spf[n]);
        n /= spf[n];
    }

    return factors;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    build_spf(); 

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> factors = get_factors(n);

        for (int x : factors)
            cout << x << " ";
        cout << "\n";
    }

    return 0;
}