#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// CHANGE 1: If capacities can sum to > 1e18, use a larger value or __int128. 
// If capacities are strictly small, you can change this to 1e9 and use standard 'int' for speed.
const long long INF = LLONG_MAX;

struct Dinic {
    struct Edge {
        int to;
        // CHANGE 2: Change 'long long' to 'int' for `cap` and `flow` if max possible flow fits in 32-bit integer. 
        // This saves memory and significantly reduces constant factor time.
        long long cap;  
        long long flow; 
        int rev;        
    };

    int n; 
    vector<vector<Edge>> adj; 
    vector<int> level;        
    vector<int> ptr;          

    // CHANGE 3: Ensure 'n' accounts for 1-based indexing if your graph uses it (pass N+1).
    // If you need to create a super-source and super-sink, pass N+2 (or more).
    Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}

    void addEdge(int from, int to, long long cap) {
        adj[from].push_back({to, cap, 0, (int)adj[to].size()});
        
        // CHANGE 4: For DIRECTED edges, reverse capacity is 0.
        // For UNDIRECTED edges, change the '0' below to 'cap'.
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

        for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
            auto& edge = adj[v][cid];
            int tr = edge.to;
            
            if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;
            
            long long push = dfs(tr, t, min(pushed, edge.cap - edge.flow));
            
            if (push == 0) continue; 
            
            edge.flow += push;
            adj[tr][edge.rev].flow -= push;
            
            return push;
        }
        return 0; 
    }

    // CHANGE 5: Change return type to 'int' if flows are guaranteed to fit in 32-bit integers.
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    /* 
     * WHAT IS A MIN CUT?
     * A "cut" partitions the graph's nodes into two disjoint sets: S (contains source) and T (contains sink).
     * The capacity of a cut is the sum of capacities of all edges going FROM set S TO set T.
     * A Min Cut is the cut with the smallest possible capacity among all valid cuts.
     * 
     * Max-Flow Min-Cut Theorem: The Maximum Flow is EXACTLY EQUAL to the capacity of the Minimum Cut.
     * 
     * Intuition: Imagine the graph is a water pipe system. If you want to destroy pipes (edges) to 
     * completely disconnect the source from the sink as cheaply as possible (cost = capacity), 
     * the Min Cut is that exact cheapest set of pipes.
     * 
     * CP Usage: Use Min Cut when problems ask for the minimum cost to disconnect two sets of nodes,
     * or for two-choice decision problems with penalties (often called Project Selection problems).
     */
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
        // Returns a boolean array: true means the node is in the source set (S), false means sink set (T).
        // The actual edges in the Min Cut are the original graph edges going from a 'true' node to a 'false' node.
        return visited;
    }
};
