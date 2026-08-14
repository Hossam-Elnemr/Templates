// Tarjan - Articulation Points + Bridges + 2-Edge-Connected Components
// Complexity: O(N + M)
//
// Results:
// is_art[u]          -> u is an articulation point
// is_bridge[id]      -> edge id is a bridge
// comp_id[u]         -> 2-edge-connected component containing u
// dag[comp_id[u]]    -> compressed bridge tree / forest
//
// Note:
// After removing all bridges, each remaining connected component gets one comp_id.
// Compressing these components using bridges gives a TREE/FOREST, not a general DAG.

const int N = 3e5 + 5;

vector<pair<int,int>> adj[N]; // {v, edge_id}
vector<pair<int,int>> edges;

int dfs_num[N], low[N], dfn = 0;
int comp_id[N], id = 0;

bool is_art[N];
bool is_bridge[N];

vector<int> dag[N];

void addEdge(int u, int v) {
	int eid = edges.size();
	edges.push_back({u, v});

	adj[u].push_back({v, eid});
	adj[v].push_back({u, eid});
}


// Find articulation points + bridges
void tarjan(int u, int parentEdge = -1) {
	dfs_num[u] = low[u] = ++dfn;

	int children = 0;

	for(auto [v, eid] : adj[u]) {
		if(eid == parentEdge)
			continue;

		if(dfs_num[v] == 0) {
			children++;

			tarjan(v, eid);

			low[u] = min(low[u], low[v]);

			// Articulation point
			if(parentEdge != -1 && low[v] >= dfs_num[u])
				is_art[u] = 1;

			// Bridge
			if(low[v] > dfs_num[u])
				is_bridge[eid] = 1;
		}
		else {
			low[u] = min(low[u], dfs_num[v]);
		}
	}

	// Root articulation point
	if(parentEdge == -1 && children > 1)
		is_art[u] = 1;
}


// Build components after removing bridges
void buildComp(int u, int cid) {
	comp_id[u] = cid;

	for(auto [v, eid] : adj[u]) {
		if(comp_id[v] != -1)
			continue;

		if(is_bridge[eid])
			continue;

		buildComp(v, cid);
	}
}


// Compress components into bridge tree / forest
void buildDAG() {
	for(auto [u, v] : edges) {
		if(comp_id[u] != comp_id[v]) {
			dag[comp_id[u]].push_back(comp_id[v]);
			dag[comp_id[v]].push_back(comp_id[u]);
		}
	}
}


void init(int n) {
	// Run Tarjan for every connected component
	for(int i = 0; i < n; i++) {
		if(!dfs_num[i])
			tarjan(i);
	}

	// Build 2-edge-connected components
	fill(comp_id, comp_id + n, -1);

	for(int i = 0; i < n; i++) {
		if(comp_id[i] == -1) {
			buildComp(i, id);
			id++;
		}
	}

	// Build compressed bridge tree / forest
	buildDAG();
}
