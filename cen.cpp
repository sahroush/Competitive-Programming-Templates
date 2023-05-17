/*
#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,fma")
//*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int  ,int > pii;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll maxn  = 1e5 + 100;
const ll mod =1e9+7;
const ld PI = acos((ld)-1);

#define pb push_back
#define endl '\n'
#define dokme(x) cout << x , exit(0)
#define migmig ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define ms(x , y) memset(x , y , sizeof x)
ll pw(ll a, ll b, ll md = mod){ll res = 1;while(b){if(b&1){res=(a*res)%md;}a=(a*a)%md;b>>=1;}return(res);}

int n , q;
vector < int > adj[maxn];
int par[maxn];
int hide[maxn] , sz[maxn];
int ans[maxn];
int Par[23][maxn];
int h[maxn];

int lca(int u , int v){
    if(h[u] > h[v])
        swap(u , v);
    for (int i = 19 ; i >= 0 ; i --)
        if(Par[i][v] and h[Par[i][v]]>=h[u])
            v = Par[i][v];
    if(v == u)
        return(v);
    for (int i = 19 ; i >= 0 ; i --)
        if(Par[i][v] != Par[i][u])
            v = Par[i][v] , u = Par[i][u];
    return(Par[0][v]);
}

int dist(int u , int v){
	return(h[u] + h[v] - 2*h[lca(u, v)]);
}

void dfs(int v , int p = 0){
	Par[0][v] = p;
	h[v] = h[p] + 1;
	for(auto u : adj[v])if(u!=p)
		dfs(u , v);
}

void init(){
	dfs(1);
	for(int i = 1 ; i < 20 ; i ++)
		for(int j = 1 ; j <= n ; j ++)
			Par[i][j] = Par[i - 1][Par[i-1][j]];
}

void plant(int v , int par = 0){
	sz[v] = 1;
	for(auto u : adj[v])
		if(u!=par and !hide[u])
			plant(u , v) , sz[v] += sz[u];
}

int cen(int v , int n , int par = 0 , bool found = 0){
	while(!found){
		found = 1;
		for(auto u : adj[v])
			if(u!=par and !hide[u] and sz[u] * 2 > n){
				par = v , v = u , found = 0;
				break;
			}
	}
	return(v);
}

void tree(int v , int pr = 0){
	plant(v);
	v = cen(v , sz[v]);
	par[v] = pr;
	hide[v] = 1;
	for(auto u : adj[v])
		if(!hide[u])
			tree(u , v);
}

void add(int v){
	int u = v;
	while(v != 0)
		ans[v] = min(ans[v] , dist(u , v)),
		v = par[v];
}

int solve(int v){
	int u = v;
	int res = 1e6;
	while(v != 0)
		res = min(res , ans[v] + dist(u , v)),
		v = par[v];
	return(res);
}

int32_t main(){
    migmig;
	cin >> n >> q;
	for(int i = 1 ; i < n ; i ++){
		int u , v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	ms(ans , 31);
	tree(1);
	init();
	add(1);
	while(q -- ){
		int t , v;
		cin >> t >> v;
		if(t == 1)add(v);
		else cout << solve(v) << endl;
	}
    return(0);
}