int par[maxn][30];
vector < int > adj[maxn];
int h[maxn];

void dfs(int v){
    for (auto u : adj[v]){
        if(u!=par[v][0]){
            par[u][0] = v;
            h[u] = h[v]+1;
            dfs(u);
        }
	}
}

int lca(int u , int v){
    if(h[u] > h[v]){
        swap(u , v);
    }
    for (int i = 35 ; i >= 0 ; i --){
        if(par[v][i] and h[par[v][i]]>=h[u]){
            v = par[v][i];
        }
    }
    if(v == u){
        return(v);
    }
    for (int i = 35 ; i >= 0 ; i --){
        if(par[v][i] != par[u][i]){
            v = par[v][i] , u = par[u][i];
        }
    }
    return(par[v][0]);
}

void init(){
	dfs(1);
    for (int j = 1; j < 27 ; j ++){
        for (int i = 1 ; i <= n ; i ++){
            par[i][j] = par[par[i][j - 1]][j - 1];
        }
    }
}

int dist(int u , int v){
	return(h[u] + h[v] - 2*h[lca(u, v)]);
}