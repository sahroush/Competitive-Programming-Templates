//O(m^2 * n). Max flow from 1 to n.
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1010;
const ll INF = 1e17;

#define pb push_back
#define endl '\n'
#define ms(x , y) memset(x , y , sizeof x)

int n , m;
ll a[maxn] , b[maxn] , c[maxn] , d[maxn];
vector < int > adj[maxn];
ll ans = 0;
queue < int > q;
ll par[maxn] , mn[maxn];

bool chk(){
	mn[1] = INF;ms(par , -1);par[1] = 0;q.push(1);
	while(q.size()){
		int v = q.front();
		q.pop();
		for(auto w : adj[v]){
			if(a[w] == v){
				if(par[b[w]] != -1)continue;
				par[b[w]] = w;
				mn[b[w]] = min(mn[v] , c[w] - d[w]);
				q.push(b[w]);
			}
			else{
				if(par[a[w]] != -1)continue;
				par[a[w]] = w;
				mn[a[w]] = min(mn[v] , d[w]);
				q.push(a[w]);
			}
		}
	}
	if(par[n] == -1)return 0;
	ans += mn[n];
	int cur = n;
	while(par[cur] > 0){
		if(cur == a[par[cur]]){
			d[par[cur]] -= mn[n];
			cur = b[par[cur]];
		}
		else{
			d[par[cur]] += mn[n];
			cur = a[par[cur]];
		}
	}
	return 1;
}

int32_t main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for(int i = 1 ; i <= m ; i ++)
		cin >> a[i] >> b[i] >> c[i];
	while(1){
		for(int i = 1 ; i <= n ; i ++)adj[i].clear();
		for(int i = 1 ; i <= m ; i ++)if(c[i] - d[i] > 0)adj[a[i]].pb(i);
		for(int i = 1 ; i <= m ; i ++)if(d[i] > 0)adj[b[i]].pb(i);
		if(!chk())break;
	}
	cout << ans;
	return(0);
}
