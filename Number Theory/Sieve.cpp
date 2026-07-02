#include <bits/stdc++.h>
using namespace std;

vector<int> sieve(int n) {
    vector<int> primes;
    vector<bool> is_prime(n + 1, true);

    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }

    for (int i = 2; i <= n; i++) {
        if (is_prime[i])
            primes.push_back(i);
    }

    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> primes = sieve(n);

    for (int p : primes) {
        cout << p << " ";
    }
    cout << "\n";

    return 0;
}