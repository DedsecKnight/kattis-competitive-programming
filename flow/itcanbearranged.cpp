#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

#define len(a) int((a).size())
using ll = long long;
constexpr const int iinf = 1e9 + 7;

#define printDecimal(d) \
    cout << setprecision(d) << fixed

struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc-c, 0ll); }
    };
    vector<int> lvl, ptr, q;
    vector<vector<Edge>> adj;
    explicit Dinic(int n) : lvl(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0) {
        adj[a].push_back({b, len(adj[b]), c, c});
        adj[b].push_back({a, len(adj[a])-1, rcap, rcap});
    } 
    ll dfs(int v, int t, ll f) {
        if (v == t || !f) return f;
        for (int& i = ptr[v]; i < len(adj[v]); i++) {
            auto& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1) {
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
            }
        }
        return 0;
    }
    ll calc(int s, int t) {
        ll flow = 0;
        q[0] = s;
        for (int L = 0; L<31; L++) {
            do {
                lvl = ptr = vector<int>(len(q));
                int qi = 0, qe = lvl[s] = 1;
                while (qi < qe && !lvl[t]) {
                    int v = q[qi++];
                    for (auto e : adj[v]) {
                        if (!lvl[e.to] && e.c >> (30 - L))
                            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
                    }
                }
                while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
            } while (lvl[t]);
        }
        return flow;
    }
};

struct demand_edge {
    int dest, demand, capacity;
    demand_edge() = default;
    demand_edge(int a, int b, int c) : dest{a}, demand{b}, capacity{c} {}
};

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    int t; cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, m; 
        cin >> n >> m;
        vector<int> a(n), b(n), required(n);
        for (int i = 0;i<n; i++) {
            cin >> a[i] >> b[i] >> required[i];
            required[i] = (required[i] + m - 1) / m;
        }
        vector<vector<int>> clean(n, vector<int>(n));
        vector<vector<demand_edge>> edges(2*n+2);
        
        for (int i = 0;i<n; i++) {
            edges[2*n].emplace_back(2*i, 0, required[i]);
            edges[2*i+1].emplace_back(2*n+1, 0, iinf);
            edges[2*i].emplace_back(2*i+1, required[i], required[i]);
            for (int j = 0;j<n; j++) {
                cin >> clean[i][j];
                if (i != j && b[i] + clean[i][j] < a[j]) {
                    edges[2*i+1].emplace_back(2*j, 0, iinf);
                }
            }
        }

        auto compute_flow = [&](int cap) -> ll {
            Dinic ds{2*n+4};
            ds.addEdge(2*n+1, 2*n, cap);
            vector<int> in_demand(2*n+2), out_demand(2*n+2);
            for (int i= 0;i<2*n+2; i++) {
                for (const auto& [to, demand, capacity] : edges[i]) {
                    in_demand[to] += demand;
                    out_demand[i] += demand;
                    ds.addEdge(i, to, capacity - demand);
                }
            }
            for (int i= 0;i<2*n+2; i++) {
                ds.addEdge(2*n+2, i, in_demand[i]);
                ds.addEdge(i, 2*n+3, out_demand[i]);
            }
            return ds.calc(2*n+2, 2*n+3);
        };
        auto total = accumulate(begin(required), end(required), 0);
        int low = 0, high = total + 1;
        auto best = high;
        while (low <= high) {
            auto mid = low + (high - low) / 2;
            if (compute_flow(mid) == total) {
                best = mid;
                high = mid-1;
            } else {
                low = mid+1;
            }
        }
        cout << "Case " << tc << ": " << best << '\n';
    }
}
