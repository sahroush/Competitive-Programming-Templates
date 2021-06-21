#include <bits/stdc++.h>

using namespace std;

struct EdmondsKarp{
	#define MAXN 1010
	int n = 0, m = 0;
	vector < int > a, b, par, adj[MAXN];
	vector < int64_t > c, d, mn;
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
	int64_t flow(int source, int sink){
		mn[source] = 2e18;
		fill(par.begin(), par.end(), -2);
		par[source] = -1;
		q.push(source); 
		while(q.size()){
			int v = q.front();
			q.pop();
			for(auto w : adj[v]){
				if(a[w] == v){
					if(par[b[w]] != -2)continue;
					if(c[w] - d[w] == 0)continue;
					par[b[w]] = w;
					mn[b[w]] = min(mn[v] , c[w] - d[w]);
					q.push(b[w]);
				}
				else{
					if(par[a[w]] != -2)continue;
					if(d[w] == 0)continue;
					par[a[w]] = w;
					mn[a[w]] = min(mn[v] , d[w]);
					q.push(a[w]);
				}
			}
		}
		if(par[sink] == -2)return 0;
		int cur = sink;
		while(par[cur] >= 0){
			if(cur == a[par[cur]]){
				d[par[cur]] -= mn[sink];
				cur = b[par[cur]];
			}
			else{
				d[par[cur]] += mn[sink];
				cur = a[par[cur]];
			}
		}
		return mn[sink];
	}
	int64_t solve(int source, int sink){
		int64_t ans = 0;
		d.resize(m), fill(d.begin(), d.end(), 0);
		mn.resize(n), fill(mn.begin(), mn.end(), 0);
		par.resize(n);
		for(int64_t x = flow(source - 1 , sink - 1) ; x ; x = flow(source - 1 , sink - 1))
			ans += x;
		return ans;
	} 
};

int n , m;

EdmondsKarp crap;

int32_t main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for(int i = 1, a , b , c ; i <= m ; i ++)
		cin >> a >> b >> c , crap.add_edge(a , b , c);
	cout << crap.solve(1, n);
	return(0);
}
