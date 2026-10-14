#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
vector<int> spf(N);

// Smallest Prime Factor sieve
void build_spf() {
    for (int i = 1; i < N; i++)
        spf[i] = i;

    for (int i = 2; i * i < N; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < N; j += i) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

// Prime factorization of n: (prime, exponent)
vector<pair<int, int>> get_factorization(int n) {
    vector<pair<int, int>> factors;

    while (n > 1) {
        int p = spf[n];
        int cnt = 0;

        while (n % p == 0) {
            n /= p;
            cnt++;
        }

        factors.push_back(make_pair(p, cnt));
    }

    return factors;
}

// Exponent of prime p in n!
long long power_of_prime_in_factorial(long long n, long long p) {
    long long ans = 0;

    while (n > 0) {
        n /= p;
        ans += n;
    }

    return ans;
}

// Prime factorization of n!
vector<pair<int, long long>> factorial_factorization(int n) {
    vector<pair<int, long long>> factors;

    for (int p = 2; p <= n; p++) {
        if (spf[p] == p) {
            long long exponent =
                power_of_prime_in_factorial(n, p);

            factors.push_back(make_pair(p, exponent));
        }
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

        vector<pair<int, long long>> factors =
            factorial_factorization(n);

        cout << "Prime factorization of " << n << "!:\n";

        for (int i = 0; i < (int)factors.size(); i++) {
            int p = factors[i].first;
            long long exponent = factors[i].second;

            cout << p << "^" << exponent << '\n';
        }
    }

    return 0;
}