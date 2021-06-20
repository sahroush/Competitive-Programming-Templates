//O(m^2 * log(INF)). Max flow from 1 to n.
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1010;
static ll INF = 1e17;

#define pb push_back
#define endl '\n'
#define ms(x , y) memset(x , y , sizeof x)

int n , m;
bool mark[maxn];
ll a[maxn] , b[maxn] , c[maxn] , d[maxn];
vector < int > adj[maxn];
ll ans = 0;

bool chk(int v = 1){
	mark[v] = 1;
	if(v == n)return 1;
	for(auto w : adj[v]){
		if(a[w] == v and !mark[b[w]] and chk(b[w])){
			 d[w] += INF;
			 return 1;
		}
		if(b[w] == v and !mark[a[w]] and chk(a[w])){
			d[w] -= INF;
			return 1;
		}
	}
	return 0;
}

int32_t main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for(int i = 1 ; i <= m ; i ++)
		cin >> a[i] >> b[i] >> c[i];
	while(INF){
		while(1){
			for(int i = 1 ; i <= n ; i ++)adj[i].clear();
			for(int i = 1 ; i <= m ; i ++)if(c[i] - d[i] >= INF)adj[a[i]].pb(i);
			for(int i = 1 ; i <= m ; i ++)if(d[i] >= INF)adj[b[i]].pb(i);
			ms(mark , 0);
			if(!chk())break;
			ans += INF;
		}
		INF>>=1;
	}
	cout << ans;
	return(0);
}
