struct Fenwick {
    int n;
    vector<long long> bit;
    Fenwick(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    // a[idx] += val
    void add(int idx, long long val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }

    // sum of a[1..idx]
    long long sum(int idx) const {
        long long s = 0;
        for (; idx > 0; idx -= idx & -idx) s += bit[idx];
        return s;
    }

    // sum of a[l..r]
    long long sum(int l, int r) const {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};
