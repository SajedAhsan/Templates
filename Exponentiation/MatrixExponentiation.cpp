#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

// ---------- Matrix template ----------
struct Matrix 
{
    int n;
    vector<vector<long long>> a;

    Matrix(int n, bool identity = false) : n(n), a(n, vector<long long>(n, 0)) {
        if (identity)
            for (int i = 0; i < n; i++) a[i][i] = 1;
    }

    Matrix operator*(const Matrix& o) const 
    {
        Matrix res(n);
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++) {
                if (a[i][k] == 0) continue;         
                for (int j = 0; j < n; j++)
                    res.a[i][j] = (res.a[i][j] + a[i][k] * o.a[k][j]) % MOD;
            }
        return res;
    }
};

Matrix mat_pow(Matrix base, long long p) 
{
    Matrix result(base.n, true);                       
    while (p > 0) {
        if (p & 1) result = result * base;
        base = base * base;
        p >>= 1;
    }
    return result;
}

// ---------- Example 1: nth Fibonacci (F0 = 0, F1 = 1) ----------
long long fibonacci(long long n) {
    if (n == 0) return 0;
    Matrix M(2);
    M.a[0][0] = 1; M.a[0][1] = 1;
    M.a[1][0] = 1; M.a[1][1] = 0;
    Matrix R = mat_pow(M, n - 1);
    return R.a[0][0];                                  
}

// ---------- Example 2: general linear recurrence ----------
// f(n) = c[0]*f(n-1) + c[1]*f(n-2) + ... + c[k-1]*f(n-k)
// init[i] = f(i) for i = 0..k-1
long long linear_recurrence(const vector<long long>& c, const vector<long long>& init, long long n) {
    int k = c.size();
    if (n < k) return init[n] % MOD;

    Matrix M(k);
    for (int j = 0; j < k; j++) M.a[0][j] = c[j] % MOD; // first row = coefficients
    for (int i = 1; i < k; i++) M.a[i][i - 1] = 1;      // shift rows

    Matrix R = mat_pow(M, n - (k - 1));
    // state vector = [f(k-1), f(k-2), ..., f(0)]
    long long ans = 0;
    for (int j = 0; j < k; j++)
        ans = (ans + R.a[0][j] * init[k - 1 - j]) % MOD;
    return ans;
}

// ---------- Example 3: number of walks of length L in a graph ----------
// adjacency matrix adj, returns (adj^L)[u][v]
long long count_walks(const vector<vector<long long>>& adj, int u, int v, long long L) {
    int n = adj.size();
    Matrix M(n);
    M.a = adj;
    return mat_pow(M, L).a[u][v];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Fibonacci
    long long n;
    cin >> n;
    cout << "F(" << n << ") mod 1e9+7 = " << fibonacci(n) << "\n";

    // Tribonacci-like: f(n) = f(n-1) + f(n-2) + f(n-3), f(0)=0, f(1)=1, f(2)=1
    cout << "Tribonacci(" << n << ") = "
         << (linear_recurrence({1, 1, 1}, {0, 1, 1}, n) + MOD) % MOD << "\n";

    return 0;
}