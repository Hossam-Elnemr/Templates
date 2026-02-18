struct DSU {
    vector<int> sz, par;
    DSU(int n) {
        sz.resize(n + 1, 1);

        par.resize(n + 1, 0);
        iota(par.begin(), par.end(), 0);
    }

    int find(int u) { // ~O(1)
        return par[u] = u == par[u]? u : find(par[u]);
    }
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return;
        if (sz[u] > sz[v]) // always merge u into v (small to large)
            swap(u, v);
        sz[v] += sz[u];
        par[u] = v;
    }
};
