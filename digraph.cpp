struct dinode{
    vector < int > adj , radj;
    int indeg = 0 , outdeg = 0;
    int color = 0 , mark = 0;
    void reset(){
        adj.clear();
        radj.clear();
        indeg = outdeg = color = mark = 0;
    }
};

struct digraph{
    int n , m;
    dinode V[maxn];
    vector < pii > edge;
    vector < int > order;
    queue < int > q;
    vector < int > ans;
    int scc_cnt = 1;
    void init(){
        scc_cnt = 1;
        ans.clear();
        while(q.size())q.pop();
        edge.clear();
        for(int i = 1 ; i <= n ; i ++)
            V[i].reset();
    }
    void add_edge(int v , int u){
        V[v].adj.pb(u);
        V[u].radj.pb(v);
        V[u].indeg++;
        V[v].outdeg++;
        edge.pb({u , v});
    }
    void dfs(int v){
        V[v].mark = 1;
        for (auto u : V[v].adj)
            if(!V[u].mark)
                dfs(u);
        order.pb(v);
    }
    void sfd(int v){
        V[v].color = scc_cnt;
        for (auto u : V[v].radj)
            if(!V[u].color)
                sfd(u);
    }
    void scc(int n ){
        for (int i = 1 ; i <= n ; i ++)
            if(!V[i].mark)
                dfs(i);
        reverse(order.begin() , order.end());
        for (int i = 0 ; i < n ; i ++)
            if(V[order[i]].color == 0)
                sfd(order[i]),
                scc_cnt++;
        scc_cnt--;
    }
    
    void topo(int n){
        order = vector < int > (n+10, 0);
        for(int i = 1 ; i <= n ; i ++) if(V[i].indeg == 0) q.push(i);
        int cur = 1;
        while(!q.empty()){
            auto v = q.front();
            q.pop();
            order[v] = cur ++;
            for(auto u : V[v].adj){
                V[u].indeg--;
                if(V[u].indeg == 0)
                    q.push(u);
            }
        }
    }
    
    void make_scc_dag(int n){
        for(int i = 1 ; i <= scc_cnt ; i ++ )V[i].radj.clear();
        for(int i = 1 ; i <= n ; i ++ )
            for(auto u : V[i].adj)
                if(V[i].color!=V[u].color)
                    V[V[u].color].radj.pb(V[i].color);
        for(int i = 1 ; i <= scc_cnt ; i ++)
            sort(V[i].radj.begin() , V[i].radj.end()),
            V[i].radj.resize(unique(V[i].radj.begin() , V[i].radj.end())-V[i].radj.begin()),
            V[i].indeg = (int)V[i].radj.size();
        for(int i = 1 ; i <= scc_cnt ; i ++) V[i].adj.clear(), V[i].outdeg = 0;
        for(int i = 1 ; i <= scc_cnt ; i ++) for(auto u : V[i].radj) V[u].adj.pb(i);
        for(int i = 1 ; i <= scc_cnt ; i ++) V[i].outdeg = (int)V[i].adj.size();
    }
    
    bool sat(){
        // -v = v , v = v + n
        scc(n + n);
        for(int i = 1 ; i <= n ; i ++)
            if(V[i].color == V[i + n].color)
                return(0);
        ans.clear();
        make_scc_dag(n + n);
        topo(scc_cnt);
        for(int i = 1 ; i <= n ; i ++)
            if(order[V[i].color] < order[V[i+n].color])
                ans.pb(i);
        return(1);
    }
};