const int N = 2e5 + 5, SQ = 325;
int a[N], n;
long long buckets[N / SQ];

void build(int x) { // builds a single block
    buckets[x] = 1e11;
    int start = x * SQ, end = min((x + 1) * SQ, n);
    for (int i = start; i<end; ++i)
        buckets[x] = min(buckets[x], a[i] * 1ll);
}

void update(int i, int val) { // a[i] = val
    a[i] = val;
    build(i / SQ); // rebuild my block (block contains i)
}

int get(int l, int r) { // min(a[l...r])
    long long ans = 1e11;
    for (int i = l; i<=r; ) {
        if (i%SQ == 0 && i + SQ - 1 <= r) {
            ans = min(ans, buckets[i / SQ]);
            i += SQ;
        }
        else {
            ans = min(ans, a[i] * 1ll);
            ++i;
        }
    }
    return ans;
}

void solve() {
    cin >> n;
    for (int i = 0; i<n; ++i)
        cin >> a[i];

    // Builds all the blocks
    for (int i = 0; i<n; i += SQ) 
        build(i / SQ);

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << get(l, r) << '\n';
    }
}
