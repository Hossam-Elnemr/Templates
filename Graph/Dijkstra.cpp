const int N = 1e5+5;
vector<int> dist(N, LLONG_MAX);
vector<pair<int, int>> adj[N];
void Dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[1] = 0;
    pq.emplace(0, 1);
    while(!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();
        if(dist[node] < cost)
            continue;
        for(auto [ch, c] : adj[node]) {
            if(dist[ch] > cost + c) {
                // cout << "node " << ch << " has " << dist[ch] << '\n';
                dist[ch] = cost + c;
                // cout << "Became " << dist[ch] << '\n';
                pq.emplace(dist[ch], ch);
            }
        }
    }
}
