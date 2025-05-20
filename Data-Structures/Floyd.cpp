const int N = 504;
int dp[N][N], adj[N][N];
void floyd(int n) {
	for(int i = 1; i<=n; ++i)
		for(int j = 1; j<=n; ++j)
			adj[i][j] = (i == j? 0 : 1e13);

	// take input (adjacency matrix)
	// while(m--) {
	// 	int u, v, c; cin >> u >> v >> c;
	// 	adj[u][v] = min(adj[u][v], c);
	// 	adj[v][u] = min(adj[v][u],c);
	// }
	for(int k = 1; k<=n; ++k)
		for(int i = 1; i<=n; ++i)
			for(int j = 1; j<=n; ++j)
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
}
