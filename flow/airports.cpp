/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/airports
TAGS: flows, binary search, shortest path
EXPLANATION: 
- This problem is a variation of the Airport Scheduling problem. 
- Following is how one can use flow with demand to determine whether all flights can be satisfied with k planes: 
    + For every flight i, create 2 new vertices in the flow graph: u_i, v_i. Then, construct an edge with capacity 1 and demand 1 going
    from u_i to v_i in the flow graph. 
    + For every u_i and v_i, create an edge with capacity 1 and demand 0 between source and u_i and an edge with capacity 1 and demand 0 from v_i
    to sink. 
    + For every pair of flights i, j, if a plane can satisfy flight i AND THEN flight j, then construct and edge with capacity 1 and demand 0 from 
    v_i to u_j. 
    + Set the demand of the source to -k and demand of the sink to k. 
    + Whether the constructed flow graph has a feasible circulation will provide the answer to whether all flights can be satisfied with k planes. 
- To determine the minimum number of planes required, it can be noted that binary search can be used to find the minimal k. 
- Refer to the code below on how to convert a flow with demand graph into a normal flow graph with no demand. 
- Potential pitfall: 
    + Although it is not explicitly stated in the problem statement, a direct flight is not always the fastest way to go from one airport to the other. 
    + Although the m provided flights has to be direct flights, the unscheduled flights are not required to be direct flights
    => One need to apply some shortest path algorithm such as Floyd-Warshall to determine the real shortest path from one airport to the other.
- Flow with demand resource: https://courses.cs.vt.edu/cs5114/spring2013/lectures/lecture19-network-flow-applications.pdf
END ANNOTATION
*/
#include <bits/stdc++.h>

using namespace std;

using ui = unsigned int;
using ll = long long;
using ld = long double;

template <typename K, typename V>
using umap = unordered_map<K, V>;

#define null NULL
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)

constexpr ll inf = 1000000000000000000;

struct Dinic {
    struct Edge {
        int to, rev;
        int c, oc;
        int flow() {return max(oc - c, 0);}
    };
    vector<int> lvl, ptr, q;
    vector<vector<Edge>> adj;
    explicit Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, int c, int rcap = 0) {
        adj[a].push_back({b, len(adj[b]), c, c});
        adj[b].push_back({a, len(adj[a]) - 1, rcap, rcap});
    }
    int dfs(int v, int t, int f) {
        if (v == t || !f) return f;
        for (int& i = ptr[v]; i < len(adj[v]); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1) {
                if (int p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
            }
        }
        return 0;
    }
    int calc(int s, int t) {
        int flow = 0; q[0] = s;
        for (int L = 0; L<31; L++) do {
            lvl = ptr = vector<int>(len(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                for (Edge e : adj[v]) {
                    if (!lvl[e.to] && e.c >> (30 - L)) {
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
                    }
                }
            }
            while (int p = dfs(s, t, 1e9 + 10)) flow += p;
        } while (lvl[t]);
        return flow;
    }
};

struct DemandEdge {
    int from, to;
    int lb, rb;
    DemandEdge(int f, int t, int l, int r) : from{f}, to{t}, lb{l}, rb{r} {}
};


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n,m; 
    cin >> n >> m;
    vector<int> inspection(n);
    for (int i = 0;i<n; i++) {
        cin >> inspection[i];
    }
    vector<vector<int>> dist(n, vector<int>(n)), shortest_path(n, vector<int>(n));
    for (int i = 0;i<n; i++) {
        for (int j = 0; j<n; j++) {
            cin >> dist[i][j];
            shortest_path[i][j] = dist[i][j];
        }
    }
    for (int k = 0; k<n; k++) {
        for (int i = 0;i<n; i++) {
            for (int j = 0;j<n; j++) {
                shortest_path[i][j] = min(shortest_path[i][j], shortest_path[i][k] + inspection[k] + shortest_path[k][j]);
            }
        }
    }
    vector<tuple<int, int, int>> requirements;
    vector<DemandEdge> demands;

    auto add_demand = [&](int f, int t, int lb, int rb) {
        demands.emplace_back(f, t, lb, rb);
    };

    for (int i = 0;i<m; i++) {
        int s, f, t;
        cin >> s >> f >> t;
        s--, f--;
        requirements.emplace_back(s, f, t);
        // Add edge from origin to dest with demand of 1
        add_demand(2*i, 2*i+1, 1, 1);
        // Add edge from source to origin
        add_demand(2*m, 2*i, 0, 1);
        // Add edge from dest to sink
        add_demand(2*i+1, 2*m+1, 0, 1);
    } 

    for (int i = 0;i<m; i++) {
        for (int j = 0; j<m; j++) {
            if (i == j) continue;
            auto [s1, f1, t1] = requirements[i];
            auto [s2, f2, t2] = requirements[j];
            auto arrive_j = t1 + dist[s1][f1] + inspection[f1];
            if (f1 != s2) {
                arrive_j += shortest_path[f1][s2] + inspection[s2];
            }
            if (arrive_j <= t2) {
                // add edge from dest of i to origin of j
                add_demand(2*i+1, 2*j, 0, 1);
            }
        }
    }


    auto find_flow = [&](int mid) -> bool {
        Dinic ds(2*m+4);
        int saturated_flow = 0;
        vector<int> d(2*m+2);
        d[2*m] = -mid;
        d[2*m+1] = mid;
        for (const auto& [f, t, lb, rb] : demands) {
            ds.addEdge(f, t, rb - lb);
            d[f] += lb, d[t] -= lb;
        }
        for (int v = 0; v < 2*m+2; v++) {
            if (d[v] < 0) {
                ds.addEdge(2*m+2, v, -d[v]);
            }
            if (d[v] > 0) {
                ds.addEdge(v, 2*m+3, d[v]);
                saturated_flow += d[v];
            }
        }
        return ds.calc(2*m+2, 2*m+3) == saturated_flow; 
    };

    int low = 1, high = m;
    int best = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (find_flow(mid)) {
            best = mid;
            high = mid-1;
        } 
        else {
            low = mid+1;
        }
    }
    assert(best != -1);
    cout << best << '\n';
}

