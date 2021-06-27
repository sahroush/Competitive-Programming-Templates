//Code for CF Good Bye 2013, problem: (E) New Year Tree Decorations
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ld , ld> pld;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int maxn = 310;
const ll mod = 1e9+7;

#define pb push_back
#define endl '\n'
#define dokme(x) cout << x , exit(0)
#define ms(x , y) memset(x , y , sizeof x)
ll pw(ll a, ll b, ll md = mod){ll res = 1;while(b){if(b&1){res=(a*res)%md;}a=(a*a)%md;b>>=1;}return(res);}

int n, k;
int a[maxn];

struct ch{
	set < pld > coord;
	ld add_line(ld l, ld r){
		if(coord.empty()){
			coord.insert({0 , l});
			coord.insert({1 , r});
			return (l + r) / 2.0;
		}
		vector < pld  > add, del;
		ld ans = 0;
		auto cur = coord.begin();
		while(next(cur) != coord.end()){
			ld L = cur->first;
			ld R = next(cur)->first;
			ld nowl = l + (r - l) * L;
			ld nowr = l + (r - l) * R;
			if(nowl <= cur->second and nowr <= next(cur)->second){
				ans += 0;
			}
			else if(nowl > cur->second and nowr > next(cur)->second){
				ld a1 = (nowl + nowr)/2.0 * (R - L);
				ld a2 = (cur->second + next(cur)->second)/2.0 * (R - L);
				ans += a1 - a2;
				del.pb(*cur);
				del.pb(*next(cur));
			}
			else if(nowl <= cur->second and nowr > next(cur)->second){
				//geometry is temporary (and shit) binary search is eternal!
				ld bsl = L, bsr = R;
				for(int i = 0 ; i < 100 ; i ++){
					ld mid = (bsl + bsr) / 2.0;
					ld h1 = nowl + (nowr - nowl) * ((mid - L) / (R - L));
					ld h2 = cur->second + (next(cur)->second - cur->second) * ((mid - L) / (R - L));
					if(h1 <= h2)
						bsl = mid;
					else 
						bsr = mid;
				}
				ld a1 = (nowr + nowl + (nowr - nowl) * ((bsl - L) / (R - L))) / 2.0;
				ld a2 = (next(cur)->second + cur->second + (next(cur)->second - cur->second) * ((bsl - L) / (R - L))) / 2.0;
				ans += (a1 - a2) * (R - bsl);
				del.pb(*next(cur));
				add.pb({bsl, nowl + (nowr - nowl) * ((bsl - L) / (R - L))});
			}
			else if(nowl > cur->second and nowr <= next(cur)->second){
				ld bsl = L, bsr = R;
				for(int i = 0 ; i < 100 ; i ++){
					ld mid = (bsl + bsr) / 2.0;
					ld h1 = nowl + (nowr - nowl) * ((mid - L) / (R - L));
					ld h2 = cur->second + (next(cur)->second - cur->second) * ((mid - L) / (R - L));
					if(h1 >= h2)
						bsl = mid;
					else 
						bsr = mid;
				}
				ld a1 = (nowl + nowl + (nowr - nowl) * ((bsl - L) / (R - L))) / 2.0;
				ld a2 = (cur->second + cur->second + (next(cur)->second - cur->second) * ((bsl - L) / (R - L))) / 2.0;
				ans += (a1 - a2) * (bsl - L);
				del.pb(*cur);
				add.pb({bsl, nowl + (nowr - nowl) * ((bsl - L) / (R - L))});
			}
			else{
				dokme("This is why I hate geometry");
			}
			cur = next(cur);
		}
		for(auto x : del)
			if(coord.count(x))coord.erase(x);
		for(auto x : add)
			coord.insert(x);
		if(coord.empty())
			coord.insert({0 , l}),
			coord.insert({1 , r});
		if(coord.begin()->first > 0)
			coord.insert({0, l});
		if(coord.rbegin()->first < 1)
			coord.insert({1, r});
		return ans;
	}
}block[maxn];

ld solve(){
	ld ans = 0;
	for(int i = 0 ; i < k ; i ++)
		ans += block[i].add_line(a[i], a[i + 1]);
	return ans;
}

int32_t main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n >> k;
	while(n --){
		for(int i = 0 ; i <= k ; i ++)
			cin >> a[i];
		cout << fixed << setprecision(12) << solve() << endl;
	}
	return(0);
}
