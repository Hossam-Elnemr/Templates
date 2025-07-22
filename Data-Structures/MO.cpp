int SQ;
struct Query{
    int l, r, i;
    bool operator <(Query &other) {
        if (l/SQ != other.l/SQ)
            return l < other.l;
        return l/SQ%2? r>other.r : r < other.r;
    }
};
void MO() {
    int n, q; cin >> n >> q;
    SQ = sqrt(n) + 1;
    Query queries[q];
    int a[n];
    for (auto &i : a)
        cin >> i;
    for (int i = 0; i<q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        --queries[i].l, --queries[i].r;
        queries[i].i = i;
    }
    int f[(int)1e6+5]{};
    sort(queries, queries + q);
    int ans = 0;
    auto add = [&](int i) {
        ans += a[i];
    };
    auto remove = [&](int i) {
        ans -= a[i];
    };
    auto get = [&]() {
        return ans;
    };
    int curL = 0, curR = -1;
    int final[q];
    for (auto [l, r, i] : queries) {
        while (curL > l)
            add(--curL);
        while (curR < r)
            add(++curR);
        while (curL < l)
            remove(curL++);
        while (curR > r)
            remove(curR--);
        final[i] = get();
    }
    for (auto i : final)
        cout << i << '\n';
}
