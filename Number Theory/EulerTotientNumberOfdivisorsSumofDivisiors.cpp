
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

// Prime factorization: (prime, exponent)
vector<pair<int, int>> get_factorization(int n) {
    vector<pair<int, int>> factors;

    while (n > 1) {
        int p = spf[n];
        int cnt = 0;

        while (n % p == 0) {
            n /= p;
            cnt++;
        }

        factors.push_back({p, cnt});
    }

    return factors;
}

// Number of positive divisors
long long number_of_divisors(int n) {
    auto factors = get_factorization(n);

    long long ans = 1;

    for (int i = 0; i < (int)factors.size(); i++) {
        ans *= (factors[i].second + 1);
    }

    return ans;
}

// Sum of positive divisors
long long sum_of_divisors(int n) {
    auto factors = get_factorization(n);

    long long ans = 1;

    for (int i = 0; i < (int)factors.size(); i++) {
        int p = factors[i].first;
        int exponent = factors[i].second;

        long long sum = 1;
        long long power = 1;

        for (int j = 1; j <= exponent; j++) {
            power *= p;
            sum += power;
        }

        ans *= sum;
    }

    return ans;
}

// Euler Totient Function
long long euler_totient(int n) {
    if (n == 1) return 1;

    auto factors = get_factorization(n);

    long long ans = n;

    for (int i = 0; i < (int)factors.size(); i++) {
        int p = factors[i].first;

        ans -= ans / p;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_spf();

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        cout << "Number of divisors: "
             << number_of_divisors(n) << '\n';

        cout << "Sum of divisors: "
             << sum_of_divisors(n) << '\n';

        cout << "Euler totient: "
             << euler_totient(n) << '\n';
    }

    return 0;
}
