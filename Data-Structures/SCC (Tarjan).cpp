const int N=3e5+5;
vector<int> adj[N];
int dfs_num[N], low[N], comp_id[N], is_art[N], dfn=0;
bool in_stack[N];
stack<int> st;
int id=0;
void tarjan(int u, int p) {
    dfs_num[u] = low[u] = ++dfn;
    st.push(u);
    in_stack[u] = true;
    int children=0;
    for(int v:adj[u]) {
        if (v==p) continue;
        if (dfs_num[v]==0) {
            children++;
            tarjan(v,u);
            low[u] = min(low[u], low[v]);
            if (low[v]>=dfs_num[u] && u!=p) {
                is_art[u]=1; //need only one subcomponent to be connected to another below me to be an articulation point for those two subcomponents
            }
        }
        else if (in_stack[v]) {
            low[u] = min(low[u],dfs_num[v]); //not low[v], because it can be not on the current path
        }
    }
    if (u==p && children>1) is_art[u]=1; //if root has 2 children with dfs_num=0, its an articulation point
    
    if (dfs_num[u]==low[u]) {
        while (true) {
            int v = st.top();
            st.pop();
            comp_id[v] = id;
            //do node-comp operations
            in_stack[v] = false;
            if (v==u) break;
        }
        id++;
    }
}
