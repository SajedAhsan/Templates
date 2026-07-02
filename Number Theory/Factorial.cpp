const long long MOD = 1000000007;
const int N = 1000000 + 5;

long long fact[N];
long long invFact[N];

long long power(long long a, long long b)
{
    long long res = 1;

    while(b)
    {
        if(b & 1)
            res = res * a % MOD;

        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

void precompute()
{
    fact[0] = 1;

    for(int i = 1; i < N; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[N - 1] = power(fact[N - 1], MOD - 2);

    for(int i = N - 1; i >= 1; i--)
        invFact[i - 1] = invFact[i] * i % MOD;
}

long long nCr(int n, int r)
{
    if(r < 0 || r > n) return 0;

    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}