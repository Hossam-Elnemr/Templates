const int N = 2e5 + 5;
bool vis[N];


vector<int> adj[N]; // For each node on the LEFT side, store all reachable nodes on the RIGHT side

// m_to[rightNode] → which LEFT node is currently matched to this RIGHT node
// -1 means this right node is currently free
vector<int> m_to(N, -1);
bool can(int node) {
    if (vis[node])
        return false;
    vis[node] = true;
    
    // Try every possible RIGHT node connected to this LEFT node
    for (auto i: adj[node]) {
        if (m_to[i] == -1 || can(m_to[i])) { // If this right node is free → match immediately, if right node is taken, try to rematch its current owner
            m_to[i] = node;
            return true;
        }
    }
    return false;
};

void solve() {
    int n; cin >> n;
    int cnt = 0;
    
    // Try to match each LEFT node
    for (int i = 1; i<=n; i++) {
        memset(vis, 0, sizeof vis);
        cnt += can(i);
    }

    // Check if perfect matching exists
    bool canMatchThisBipartite = cnt == n;
}
