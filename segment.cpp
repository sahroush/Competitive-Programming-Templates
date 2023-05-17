/*
#pragma GCC optimize("O2")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,fma,tune=native")
//*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int  ,int > pii;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll maxn  = 3e5+10;
const ll mod =1e9+7;
const ld PI = acos((ld)-1);

#define int ll
#define pb push_back
#define endl '\n'
#define dokme(x) return(cout << x , 0);
#define migmig ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ms(x , y) memset(x , y , sizeof x);
#define file_init freopen("input.txt", "r+", stdin); freopen("output.txt", "w+", stdout);
ll pw(ll a, ll b, ll md = mod){ll res = 1;while(b){if(b&1){res=(a*res)%md;}a=(a*a)%md;b>>=1;}return(res);}

pii pos[maxn];
int a[maxn];
int n;

stack < int > mn , mx;

struct segment{
    int lazy[maxn*4] , seg[maxn*4] , cnt[maxn*4];
    int& ans = cnt[1];
    void build(int v = 1 , int l = 1 , int r = maxn){
        if(r - l == 1){
            cnt[v] = 1;
            return;
        }
        int mid = (l + r) /2;
        build(2*v , l , mid);
        build(2*v + 1 , mid , r);
        cnt[v] = cnt[2*v] + cnt[2*v + 1];
    }
    void shift(int v , int l , int r){
        if(lazy[v] == 0)
            return;
        seg[v] += lazy[v];
        if(r - l == 1){
            lazy[v] = 0;return;}
        lazy[2*v] += lazy[v];
        lazy[2*v + 1] += lazy[v];
        lazy[v] = 0;
    }
    void update(int L , int R , int val , int v = 1 , int l = 1 , int r = maxn){
        shift(v , l , r);
        if(l >= R or r <= L)
            return;
        if(l >= L and r <= R){
            lazy[v] += val;
            shift(v, l , r);
            return;
        }
        int mid = (l + r)/2;
        update(L , R , val , 2*v , l , mid);
        update(L , R , val , 2*v+1 , mid , r);
        if(seg[2*v] < seg[2*v + 1]){
            seg[v] = seg[2*v];
            cnt[v] = cnt[2*v];
        }
        else if(seg[2*v] == seg[2*v + 1]){
            seg[v] = seg[2*v];
            cnt[v] = cnt[2*v] + cnt[2*v + 1];
        }
        else{
            seg[v] = seg[2*v+1];
            cnt[v] = cnt[2*v+1];
        }
    }
}seg;

int32_t main(){
    migmig
    cin >> n;
    for(int i = 0 ; i < n ; i ++)
        cin >> pos[i].second >> pos[i].first;
    sort(pos , pos + n);
    for(int i = 1 ; i <= n ; i ++ )
        a[i] = pos[i-1].second;
    for(int i = 0 ; i < 4*maxn ; i ++)
        seg.seg[i] = n+1;
    seg.build();
    int ans = 0;
    for(int i = 1 ; i <= n ; i ++){
        seg.update(i , i+1 , -(n+1));
        seg.update(1 , i , -1);
        int cur = i;
        while(!mx.empty() and a[i] > a[mx.top()]){
            int bz = mx.top();
            mx.pop();
            if(mx.size()){
                seg.update(mx.top()+1 , cur , a[i] - a[bz]);
                cur = mx.top()+1;
            }
            else{
                seg.update(1, cur , a[i] - a[bz]);
            }
        }
        cur = i;
        while(!mn.empty() and a[i] < a[mn.top()]){
            int bz = mn.top();
            mn.pop();
            if(mn.size()){
                seg.update(mn.top()+1 , cur , a[bz] - a[i]);
                cur = mn.top()+1;
            }
            else{
                seg.update(1, cur , a[bz] - a[i]);
            }
        }
        ans+=seg.ans;
        mn.push(i);
        mx.push(i);
    }
    cout << ans;
    return(0);
}









struct segment{
    vector < int > seg , lazy;
    segment(int x):
        seg(maxn*4 , 0),
        lazy(maxn*4 , -1){}
    void shift(int v , int l , int r){
        if(lazy[v] == -1)return;
        if(lazy[v] == 1)
            seg[v] = r - l;
        if(lazy[v] == 0)
            seg[v] = 0;
        if(lazy[v] == 2)
            seg[v] = r - l - seg[v];
        if(r - l > 1){
            if(lazy[v] == 2){
                if(lazy[2*v] == 2){
                    lazy[2*v] = -1;
                }
                else if(lazy[2*v] == 0){
                    lazy[2*v] = 1;
                }
                else if(lazy[2*v] == 1){
                    lazy[2*v] = 0;
                }
                else{
                    lazy[2*v] = 2;
                }
                if(lazy[2*v + 1] == 2){
                    lazy[2*v + 1] = -1;
                }
                else if(lazy[2*v + 1] == 0){
                    lazy[2*v + 1] = 1;
                }
                else if(lazy[2*v + 1] == 1){
                    lazy[2*v + 1] = 0;
                }
                else{
                    lazy[2*v + 1] = 2;
                }
            }
            else
                lazy[2*v + 1] = lazy[2*v] = lazy[v];
        }
        lazy[v] = -1;
    }
    void update(int x, int L , int R , int v = 1, int l = 1 , int r = maxn){
        shift(v , l , r);
        if(r <= L or R <= l)
            return;
        if(L <= l and r <= R){
            lazy[v] = x;
            shift(v , l , r);
            return;
        }
        int mid = (l + r)/2;
        update(x , L , R , 2*v , l , mid);
        update(x , L , R , 2*v + 1 , mid , r);
        seg[v] = seg[2*v] + seg[2*v + 1];
    }
    void solve(int v = 1 , int l = 1 , int r = maxn){
        shift(v , l , r);
        if(r - l == 1){
            cout << vec[l - 1] << endl;
            return;
        }
        int mid = (r + l) / 2;
        shift(2*v , l , mid);
        if(seg[2*v] == mid - l){
            solve(2*v + 1 , mid , r);
        }
        else{
            solve(2*v , l , mid);
        }
    }
};
 
segment seg(2);


