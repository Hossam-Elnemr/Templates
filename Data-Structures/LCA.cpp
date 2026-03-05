struct LCA {
    const int lg = 20;
    int timer = 0;
    vector<vector<int>> par;
    vector<int> in, out, depth;

    LCA(int n, int root, vector<int> adj[]) {
        par = vector<vector<int>>(n + 1, vector<int>(lg));
        in = out = vector<int>(n + 1);
        depth = vector<int>(n + 1, -1);
        dfs(root, root, adj);
    }

    void dfs(int node, int p, vector<int> adj[]) {
        in[node] = timer++;
        depth[node] = depth[p] + 1;
        par[node][0] = p;

        for (int j = 1; j<lg; ++j) {
            int p1 = par[node][j - 1];
            par[node][j] = par[p1][j - 1];
        }

        for (const int& child : adj[node]) {
            if (child == p)
                continue;
            dfs(child, node, adj);
        }

        out[node] = timer;
    }

    bool isPar(int p, int u) { // is p parent of u?
        return in[p] <= in[u] && out[p] >= out[u];
    }

    int kth(int node, int k) {
        for (int i = 0; i<lg; ++i)
            if (k >> i & 1)
                node = par[node][i];
        return node;
    }

    int lca(int u, int v) { // move u and validate (idea: get the farthest node that isn't ancestor to both)
        if (depth[u] > depth[v]) // always u is above v or at same level
            swap(u, v);
        if (isPar(u, v))
            return u;
        for (int j = lg - 1; j>=0; --j)
            if (!isPar(par[u][j], v))
                u = par[u][j];
        return par[u][0];
    }

    int dist(int u, int v) {
        int lc = lca(u, v);
        return depth[u] - depth[lc] + depth[v] - depth[lc];
    }
};
