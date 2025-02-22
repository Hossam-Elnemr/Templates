long long fact[200005];
long long subt(long long a, long long b) { return ((a % MOD) - (b % MOD) + MOD) % MOD; }
long long add(long long a, long long b) { return ((a % MOD) + (b % MOD)) % MOD; }
long long multi(long long a, long long b) { return ((a % MOD) * (b % MOD)) % MOD; }
long long fp(long long b, long long exp) {
    // b power exp;
    if (exp == 0) return 1;
    long long res = 1;
    while (exp) {
        if (exp % 2 == 1)
            res = multi(res, b);
        b = multi(b, b), exp /= 2;
    }
    return res;
}
long long INV(long long a) { return fp(a, MOD - 2); }
void calcFactorial() {
    fact[0] = 1;
    for (long long i = 1; i<200005; ++i)
        fact[i] = multi(fact[i-1], i);
}
long long divi(long long a, long long b) { return multi(a, INV(b)); }
long long nCr(long long n, long long r) {
    if (r>n || r<0 || n<0)
        return 0;
    if (r == n || r == 0)
        return 1;
    return divi(fact[n], multi(fact[r], fact[n-r]));
}
long long starsNBars(long long n, long long k) { return nCr(n+k-1, n); }
