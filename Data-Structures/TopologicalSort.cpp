pair<vector<int>, bool> TopologicalSort(const int n, vector<int> adj[], int inDeg[]) {
    queue<int> q;
    for(int i = 1; i<=n; ++i)
        if(!inDeg[i])
            q.push(i); // All nodes that are independent have priority
    vector<int> topo;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        topo.push_back(cur);
        for(auto ch : adj[cur]) {
            --inDeg[ch];
            if(!inDeg[ch])
                q.push(ch);
        }
    }
    return {topo, topo.size() == n};
}
