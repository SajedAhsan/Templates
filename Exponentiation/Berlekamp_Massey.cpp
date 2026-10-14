#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;   // must be prime

long long power(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    if (base < 0) base += MOD;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

// ---------- Berlekamp-Massey ----------
// Input : s[0..N-1]  (values mod MOD)
// Output: c[0..L-1]  such that  s[i] = c[0]*s[i-1] + c[1]*s[i-2] + ... + c[L-1]*s[i-L]
// Time  : O(N^2)
vector<long long> berlekamp_massey(const vector<long long>& s) {
    int n = s.size();
    int L = 0;      
    int m = 0;      
    vector<long long> C(n + 1, 0), B(n + 1, 0), T;
    C[0] = 1;
    B[0] = 1;
    long long b = 1;   

    for (int i = 0; i < n; i++) 
    {
        m++;
        long long d = s[i] % MOD;
        for (int j = 1; j <= L; j++)
            d = (d + C[j] * s[i - j]) % MOD;
        if (d == 0) continue;

        T = C;
        long long coef = d * power(b, MOD - 2) % MOD;
        for (int j = m; j <= n; j++)
            C[j] = ((C[j] - coef * B[j - m]) % MOD + MOD) % MOD;

        if (2 * L > i) continue;
        L = i + 1 - L;
        B = T;
        b = d;
        m = 0;
    }

    C.resize(L + 1);
    C.erase(C.begin());
    for (long long& x : C) x = (MOD - x) % MOD;
    return C;
}

// ---------- nth term of a linear recurrence ----------
// s     : first k terms (s[0..k-1]),  c : coefficients from berlekamp_massey
// n     : 0-indexed position wanted
// Time  : O(k^2 log n)
long long nth_term(const vector<long long>& s, const vector<long long>& c, long long n) {
    int k = c.size();
    if (k == 0) return 0;                  // sequence is all zeros
    if (n < (long long)s.size()) return s[n] % MOD;

    // multiply two polynomials mod (x^k - c[0]x^(k-1) - ... - c[k-1])
    auto combine = [&](const vector<long long>& a, const vector<long long>& b) {
        vector<long long> res(2 * k + 1, 0);
        for (int i = 0; i <= k; i++)
            for (int j = 0; j <= k; j++)
                res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
        for (int i = 2 * k; i > k; i--)
            for (int j = 0; j < k; j++)
                res[i - 1 - j] = (res[i - 1 - j] + res[i] * c[j]) % MOD;
        res.resize(k + 1);
        return res;
    };

    vector<long long> pol(k + 1, 0), e(k + 1, 0);
    pol[0] = 1;
    e[1] = 1;
    for (long long p = n + 1; p > 0; p >>= 1) {
        if (p & 1) pol = combine(pol, e);
        e = combine(e, e);
    }

    long long ans = 0;
    for (int i = 0; i < k; i++)
        ans = (ans + pol[i + 1] * s[i]) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example: Fibonacci terms given, recover the recurrence, then ask for a huge n
    vector<long long> s = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
    vector<long long> c = berlekamp_massey(s);

    cout << "Recurrence length: " << c.size() << "\n";
    cout << "Coefficients:";
    for (long long x : c) cout << " " << x;
    cout << "\n";

    long long n;
    cin >> n;
    cout << "term(" << n << ") = " << nth_term(s, c, n) << "\n";

    return 0;
}