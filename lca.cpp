const int lg = 20;

struct LCA{
	int n;
	int par[lg+3][maxn] , h[maxn];
	void dfs(int v  , int p , vector < int > *adj){
		for(int u : adj[v]) if(u ^ p)
			h[u] = h[v] + 1 , par[0][u] = v , dfs(u , v , adj);
	}
	void init(int N , vector < int > *adj , int root = 1){
		n = N;
		dfs(root , 0 , adj);
		h[0] = -1;
		for(int j = 1 ; j <= lg ; j ++)
			for(int i = 1 ; i <= n ; i ++)
				par[j][i] = par[j - 1][par[j - 1][i]];
	}
	int lca(int u , int v){
		if(h[u] < h[v])
			swap(u , v);
		for(int i = lg ; i >= 0 ; i --)
			if(h[par[i][u]] >= h[v])
				u = par[i][u];
		if(u == v)
			return(u);
		for(int i = lg ; i >= 0 ; i --)
			if(par[i][u] ^ par[i][v])
				u = par[i][u] , v = par[i][v];
		return(par[0][v]);
	}
	int dist(int u , int v){
		return(h[u] + h[v] - 2*h[lca(u , v)]);
	}
};
