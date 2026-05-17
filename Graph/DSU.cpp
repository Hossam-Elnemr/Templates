struct DSU {
    vector<int> sz, par;
    stack<array<int, 4>> st;
    DSU(int n) {
        sz.resize(n + 1, 1);

        par.resize(n + 1, 0);
        iota(par.begin(), par.end(), 0);
    }

    int find(int u) { // ~O(1)
        return par[u] = u == par[u]? u : find(par[u]); // par[u] = ..., this is called path compression
    }
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return st.push({-1, -1, -1, -1});
        
        if (sz[u] > sz[v]) // always merge u into v (small to large)
            swap(u, v);
        st.push({u, par[u], v, sz[v]});

        sz[v] += sz[u];
        par[u] = v;
    }

    //         *** NOTE ***
    //   If you want to use rollback, remove path compression first
    // void undo() {
    //     array<int, 4> cur = st.top();
    //     st.pop();
    //     if (cur[0] == -1)
    //         return;
    //     par[cur[0]] = cur[1];
    //     sz[cur[2]] = cur[3];
    // }
};
