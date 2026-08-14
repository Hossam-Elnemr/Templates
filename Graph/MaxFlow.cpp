#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// INF represents a flow value large enough to not bottleneck any path
const long long INF = 1e18;

struct Dinic {
    struct Edge {
        int to;
        long long cap;  // Capacity of the edge
        long long flow; // Current flow through the edge
        int rev;        // Index of the reverse edge in `adj[to]`
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> ptr;

    
    Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}

    // Add a directed edge from `u` to `v` with capacity `cap`.
    // For an undirected edge, you would add two directed edges or modify this.
    void addEdge(int from, int to, long long cap) {
        // Forward edge: initial flow is 0
        adj[from].push_back({to, cap, 0, (int)adj[to].size()});
        // Reverse edge: capacity 0, initial flow is 0
        // If the graph is undirected, change the `0` capacity here to `cap`
        adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
    }

    
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            
            for (auto& edge : adj[v]) {
                if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }

    
    long long dfs(int v, int t, long long pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;

        // `cid` is passed by reference to ptr[v] to remember dead ends
        for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
            auto& edge = adj[v][cid];
            int tr = edge.to;
            
            // Only traverse edges in the level graph with remaining capacity
            if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;
            
            
            long long push = dfs(tr, t, min(pushed, edge.cap - edge.flow));
            
            if (push == 0) continue;
            
            // Update flow for forward and reverse edges
            edge.flow += push;
            adj[tr][edge.rev].flow -= push;
            
            return push;
        }
        return 0; // No augmenting path found from this node
    }

    // Main function to calculate the maximum flow from s to t
    long long maxFlow(int s, int t) {
        long long flow = 0;
        
        // While a path exists from source to sink in the residual graph
        while (bfs(s, t)) {
            // Reset the pointer array for the DFS phase
            fill(ptr.begin(), ptr.end(), 0);
            
            // Push as much flow as possible along the level graph
            while (long long pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    // Optional: Find the nodes on the source side of the S-T Min Cut
    // Call this AFTER running maxFlow(s, t)
    vector<bool> getMinCut(int s) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& edge : adj[v]) {
                if (edge.cap - edge.flow > 0 && !visited[edge.to]) {
                    visited[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }
        // Returns a boolean array where true means the node is in the source set
        return visited;
    }
};
