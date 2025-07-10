const int p[] = {31, 97}, mod = 1e9+7, N = 1e6+5;
int add(int a, int b) {
    return (a + b + 0ll + mod)%mod;
}
int mul(int a, int b) {
    return a * 1ll * b %mod;
}
int fp(int b, int p) {
    if (p == 0)
        return 1;
    int res = fp(b, p>>1);
    res = mul(res, res);
    if (p&1)
        res = mul(res,  b);
    return res;
}
int modInv(int a) {
    return fp(a, mod-2);
}
int pw[N][2], inv[N][2];
void pre() {
    for (int j = 0; j<2; ++j) {
        pw[0][j] = inv[0][j] = 1;
        int inver = modInv(p[j]);
        for (int i = 1; i<N; ++i) {
            pw[i][j] = mul(pw[i-1][j], p[j]);
            inv[i][j] = mul(inv[i-1][j], inver);
        }
    }
}
vector<pair<int, int>> getHash(string &s) {
    vector<pair<int, int>> res(s.size() + 1);
    int sz = s.size();
    for (int i = 1; i<=sz; ++i) {
        res[i].first = add(res[i-1].first, mul(s[i-1] - 'a' + 1, pw[i-1][0]));
        res[i].second = add(res[i-1].second, mul(s[i-1] - 'a' + 1, pw[i-1][1]));
    }
    return res;
}
pair<int, int> getRange(int l, int r, vector<pair<int, int>> &h) { // give params one-based
    if (l > r)
        return {0, 0};
    pair<int, int> res;
    res.first = mul(add(h[r].first ,-h[l-1].first), inv[l-1][0]);
    res.second = mul(add(h[r].second ,-h[l-1].second), inv[l-1][1]);
    return res;
}
