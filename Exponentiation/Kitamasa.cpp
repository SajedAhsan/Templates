#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

// ---------- Kitamasa ----------
// Recurrence: s[i] = c[0]*s[i-1] + c[1]*s[i-2] + ... + c[k-1]*s[i-k]
// init[0..k-1] are the first k terms, n is the 0-indexed position wanted.
// Time: O(k^2 log n), Memory: O(k)

// multiply two polynomials (degree < k) and reduce modulo the characteristic polynomial
vector<long long> multiply(const vector<long long>& a, const vector<long long>& b,
                           const vector<long long>& c) {
    int k = c.size();
    vector<long long> res(2 * k, 0);

    for (int i = 0; i < k; i++) {
        if (a[i] == 0) continue;
        for (int j = 0; j < k; j++)
            res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
    }

    // x^k = c[0]*x^(k-1) + c[1]*x^(k-2) + ... + c[k-1]
    for (int i = 2 * k - 2; i >= k; i--) {
        if (res[i] == 0) continue;
        for (int j = 0; j < k; j++)
            res[i - 1 - j] = (res[i - 1 - j] + res[i] * c[j]) % MOD;
        res[i] = 0;
    }

    res.resize(k);
    return res;
}

long long kitamasa(const vector<long long>& c, const vector<long long>& init, long long n) {
    int k = c.size();
    if (k == 0) return 0;
    if (n < k) return init[n] % MOD;

    // result = 1, base = x (reduced if k == 1)
    vector<long long> result(k, 0), base(k, 0);
    result[0] = 1;
    if (k == 1) base[0] = c[0] % MOD;
    else base[1] = 1;

    // compute x^n mod P(x) by binary exponentiation
    long long p = n;
    while (p > 0) {
        if (p & 1) result = multiply(result, base, c);
        base = multiply(base, base, c);
        p >>= 1;
    }

    // s[n] = sum result[i] * s[i]
    long long ans = 0;
    for (int i = 0; i < k; i++)
        ans = (ans + result[i] * (init[i] % MOD)) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    // Fibonacci: s[i] = s[i-1] + s[i-2], s[0] = 0, s[1] = 1
    cout << "Fibonacci(" << n << ") = "
         << kitamasa({1, 1}, {0, 1}, n) << "\n";

    // Tribonacci: s[i] = s[i-1] + s[i-2] + s[i-3], s[0] = 0, s[1] = 1, s[2] = 1
    cout << "Tribonacci(" << n << ") = "
         << kitamasa({1, 1, 1}, {0, 1, 1}, n) << "\n";

    return 0;
}