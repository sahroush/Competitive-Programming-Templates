//O(m^2 * log(INF)). Max flow.
#include <bits/stdc++.h>

using namespace std;

struct Scaling{
	#define MAXN 1010
	int n = 0, m = 0;
	vector < int > a, b, par, adj[MAXN];
	vector < int64_t > c, d;
	queue < int > q;
	void add_edge(int u, int v, int64_t w = 1){
		u --, v --;
		adj[u].push_back(m);
		adj[v].push_back(m);
		a.push_back(u);
		b.push_back(v);
		c.push_back(w);
		m ++;
		n = max(n, max(u, v) + 1);
	}
	bool flow(int v, int source, int sink, int64_t C){
		if(v == source)
			fill(par.begin(), par.end(), 0);
		if(v == sink)
			return 1;
		par[v] = 1;
		for(auto w : adj[v])
			if(a[w] == v and c[w] - d[w] >= C and !par[b[w]] and flow(b[w] , source , sink , C)){
				d[w] += C;
				return 1;
			}
			else if (b[w] == v and d[w] >= C and !par[a[w]] and flow(a[w] , source , sink , C)){
				d[w] -= C;
				return 1;
			}
		return 0;
	}
	int64_t solve(int source, int sink){
		int64_t ans = 0, C = (1LL << 62);
		d.resize(m), fill(d.begin(), d.end(), 0);
		par.resize(n);
		for( ; C ; C >>= 1LL){
			while(flow(source - 1 , source - 1 , sink - 1 , C))
				ans += C;
		}
		return ans;
	} 
};

int n , m;

Scaling crap;

int32_t main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for(int i = 1, a , b , c ; i <= m ; i ++)
		cin >> a >> b >> c , crap.add_edge(a , b , c);
	cout << crap.solve(1, n);
	return(0);
}
