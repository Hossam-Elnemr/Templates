const int N = 504;
int n, m;
vector<vector<int>> dist(N, vector<int>(N, 1e14));
void floyd() {
	for(int i = 1; i<=n; ++i)
		dist[i][i] = 0;

	// take input (adjacency matrix)
	// while(m--) {
	// 	int u, v, c; cin >> u >> v >> c;
	// 	dist[u][v] = min(dist[u][v], c);
	// 	dist[v][u] = min(dist[v][u],c);
	// }
	for(int k = 1; k<=n; ++k)
		for(int i = 1; i<=n; ++i)
			for(int j = 1; j<=n; ++j)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
