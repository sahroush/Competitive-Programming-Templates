#include <bits/stdc++.h>

using namespace std;

struct Dinic {
    #define MAXN 400010
    int n = 0, m = 0;
    vector < int > a, b, h, pos, adj[MAXN];
    vector < int64_t > c, d;
    queue < int > q;
    void add_edge(int u, int v, int64_t w = 1) {
        u--, v--;
        adj[u].push_back(m);
        adj[v].push_back(m);
        a.push_back(u);
        b.push_back(v);
        c.push_back(w);
        m++;
        n = max(n, max(u, v) + 1);
    }
    bool bfs(int source, int sink, int64_t C) {
		fill(h.begin(), h.end(), -1);
		h[source] = 0;
        int l = 0, r = 0;
        pos[r++] = source;
        while (l < r) {
            int v = pos[l++];
            for (int w: adj[v]) {
                if (a[w] == v and h[b[w]] == -1 and c[w] - d[w] >= C) {
                    h[b[w]] = h[v] + 1;
                    pos[r++] = b[w];
                }
                if (b[w] == v and h[a[w]] == -1 and d[w] >= C) {
                    h[a[w]] = h[v] + 1;
                    pos[r++] = a[w];
                }
            }
        }
        return h[sink] != -1;
    }
	bool pump(int v, int source, int sink, int64_t cap) {
        if (v == sink)
            return 1;
        for (; pos[v] < int(adj[v].size()); pos[v]++) {
            int w = adj[v][pos[v]];
            if (a[w] == v) {
                if (c[w] - d[w] < cap) continue;
                if (h[b[w]] ^ (h[v] + 1)) continue;
                if(pump(b[w], source, sink, min(cap, c[w] - d[w]))){
					d[w] += cap;
					return 1;
				}
            }
            if (b[w] == v) {
                if (d[w] < cap) continue;
                if (h[a[w]] ^ (h[v] + 1)) continue;
                if(pump(a[w], source, sink, min(cap, d[w]))){
					d[w] -= cap;
					return 1;
				}
            }
        }
        return 0;
    }
    int64_t solve(int source, int sink) {
        source--, sink--;
        int64_t ans = 0;
        d.resize(m), fill(d.begin(), d.end(), 0);
        h.resize(n);
        pos.resize(n);
        for(int64_t C = (1LL << 30) ; C ; C >>= 1)
			while(bfs(source, sink, C)){
				fill(pos.begin(), pos.end(), 0);
				while(pump(source, source, sink, C))
					ans += C;
			}
        return ans;
    }
};

int n, m;

Dinic crap;

int32_t main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1, a, b, c; i <= m; i++)
        cin >> a >> b >> c, crap.add_edge(a, b, c);
    cout << crap.solve(1, n);
    return (0);
}

