#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int  ,int > pii;

const ll maxn =10e5+10;
const ld SADAT = 7.84e-17;
const ll INF = 1e9;
const ll mod = 1e9+7;
const ld PI = 4 * atan((ld) 1);

#define pb(x) push_back(x);
#define endl '\n'
#define dokme(x) cout << x ;  return(0);
#define migmig ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define file_init freopen("input.txt", "r+", stdin); freopen("output.txt", "w+", stdout);
#define random_init mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T>bool checkmin(T &a,T b){return a > b ? a = b, 1 : 0;}
ll pw(ll a, ll b) {
    return (!b ? 1 : (b & 1 ? a * pw(a * a % mod, b / 2) % mod : pw(a * a % mod, b / 2) % mod));
}

vector <int> vec[maxn];
bool mark[101][101];
int n;
int p[maxn];
set <pii> st;
vector <int> ans;
stack <int> dom[7][7];
int yal[7][7];
ll sum = 0;

void dfs(int v){
    for (int u = 0 ; u <= 6 ; u++){
        if(yal[u][v]){
            yal[u][v]--;
            yal[v][u]--;
            sum-=2;
            dfs(u);
        }
    }
    ans.pb(v);
}

int main(){
    migmig
    cin >> n;
    memset(yal , 0 , sizeof yal);
    for (int  i = 0 ; i < n ; i ++){
        int x , y;
        cin >> x >> y;
        vec[x].pb(y);
        vec[y].pb(x);
        st.insert(make_pair(x , y));
        dom[x][y].push(i + 1);
        yal[x][y]++;
        yal[y][x]++;
        sum+=2;
    }
    bool f = 1;
    int cnt = 0;
    int pis;
    for (int i = 0 ; i <= 6 ; i ++ ){
        if(f and vec[i].size()%2){
            cnt++;
            pis = i;
        }
    }
    if(cnt > 0){
        if(cnt>2){
            dokme("No solution");
        }
        dfs(pis);
        f = 0;
    }
    if(f ==1 ){
        for (int i = 0 ; i <= 6 ; i ++ ){
            if(f and vec[i].size()){
                dfs(i);
                f = 0;
                break;
            }
        }
    }
    if(sum > 0){
        dokme("No solution");
    }
    for (int i =0 ; i < ans.size()-1 ; i ++){
        if(!dom[ans[i]][ans[i+1]].empty()){
            cout << dom[ans[i]][ans[i+1]].top();
            dom[ans[i]][ans[i + 1]].pop();
            cout << " +" << endl;
        }
        else if(!dom[ans[i+1]][ans[i]].empty()){
            cout << dom[ans[i+1]][ans[i]].top();
            dom[ans[i+1]][ans[i]].pop();
            cout << " -" << endl;
        }
    }



    return(0);
}


//When we hit our lowest point, we are open to the greatest change.
//If I try, I fail. If I don't try, I'm NEVER GOING TO GET IT.
//Sometimes, life is like this dark tunnel. You can't always see the light at the end of the tunnel. But if you just keep moving... you will come to a better place.
//It is important to draw wisdom from diffrent places. If you take it from only one place it becomes rigid and stale.