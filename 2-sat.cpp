struct sat{ //~x = 2*x+1 , x = 2*x --> ~x = x^1
	int n , c;
	vector < vector < int > > in , out;
	vector < int >  mark , col , topo;
	sat(int N):
		n(N) , c(0) , in(n*2+5) , out(n*2+5) , mark(n*2+5 , 0) , col(n*2+5, 0){}
	bool operator [] (int x){ return(col[2*x] > col[2*x + 1]);};
	void add_edge(int v , int u){in[u].pb(v) , out[v].pb(u);}
	void add(int u , int v){add_edge(u^1 , v) , add_edge(v^1 , u);}
	void sfd(int v){
		mark[v] = 1;
		col[v] = c;
		for(int u : in[v]) if(!mark[u])
			sfd(u);
	}
	void dfs(int v){
		mark[v] = 1;
		for(int u : out[v]) if(!mark[u])
			dfs(u);
		topo.pb(v);
	}
	inline bool validate(){
		for(int i = 1 ; i <= 2*n + 1 ; i ++)if(!mark[i])dfs(i);
		reverse(topo.begin() , topo.end());
		memset(&mark[0] , 0 , sizeof(mark[0]) * mark.size());
		for(auto v : topo)
			if(!mark[v])
				c++ , sfd(v);
		for(int i = 1 ; i <= n ; i ++)if(col[2*i] == col[2*i+1])return(0);
		return(1);
	}
};
