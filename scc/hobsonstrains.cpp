#include <bits/stdc++.h>

using namespace std;

using ui = unsigned int;
using ll = long long;
using ld = long double;

template <typename K, typename V>
using umap = unordered_map<K, V>;

constexpr int iinf = 1e9 + 10;

#define null NULL
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)

template <typename F>
struct SCC {
    vector<int> val, comp, z, cont;
    int n, Time, ncomps;
    int dfs(int j, vector<vector<int>> &g, const F& f) {
        int low = val[j] = ++Time, x; z.push_back(j);
        for (auto e : g[j]) if (comp[e] < 0) 
            low = min(low, val[e] ?: dfs(e, g, f));
        
        if (low == val[j]) {
            do {
                x = z.back(); z.pop_back();
                comp[x] = ncomps;
                cont.push_back(x);
            } while (x != j);
            f(cont); cont.clear();
            ncomps++;
        }
        return val[j] = low;
    }
    SCC(vector<vector<int>>& g, const F& f) : val(len(g), 0), comp(len(g), -1), n{len(g)}, Time{}, ncomps{} {
        for (int i = 0;i<n; i++) {
            if (comp[i] < 0) dfs(i, g, f); 
        }
    }
};

struct FT {
    vector<ll> s;
    explicit FT(int n) : s(n) {}
    void update(int pos, ll dif) {
        for (; pos < len(s); pos |= pos+1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for (; pos > 0; pos &= pos-1) res += s[pos-1];
        return res;
    }
};

int main() {
    int n,k;
    cin >> n >> k;
    vector<vector<int>> graph(n), successor(n);
    vector<int> indegree(n);
    for (int i = 0;i<n; i++) {
        int d; cin >> d;
        graph[i].push_back(--d);
        successor[d].push_back(i);
        indegree[d]++;
    }
    vector<int> ret(n, -1);
    vector<int> root_nodes, root(n), depth(n, -1);
    vector<vector<int>> root_member(n);
    SCC scc(graph, [&](vector<int>& comp) {
        sort(begin(comp), end(comp), [&](auto x, auto y) { return indegree[x] > indegree[y]; });
        int curr = comp[0], leader = comp[0];
        do {
            root_member[leader].push_back(curr);
            root[curr] = leader;
            assert(len(graph[curr]) == 1);
            if (len(comp) > 1) curr = graph[curr][0];
        } while (curr != leader);
        root_nodes.push_back(leader);
    });
    function<void(int, int, int, int, vector<int>&)> dfs = [&](int curr, int par, int r, int dd, vector<int>& diff) {
        depth[curr] = dd;
        if (dd <= k) {
            // do something special
            int sz = min(k-dd+1, len(diff)-1);
            int first = min(sz, len(diff)-1-r);
            diff[r]++, diff[r+first]--;
            sz -= first;
            diff[0]++, diff[sz]--;
        }
        for (const auto& neighbor : successor[curr]) {
            if (neighbor != par && depth[neighbor] != 0) dfs(neighbor, curr, r, dd+1, diff);
        }
    };
    for (const auto& group : root_member) {
        if (len(group) == 1) continue;
        for (int i = 0 ;i<len(group); i++) {
            depth[group[i]] = 0;
        }
        vector<int> diff(len(group) + 1);
        for (int i = 0;i<len(group); i++) {
            dfs(group[i], -1, i, 0, diff);
        }
        for (int i = 0;i<len(group); i++) {
            if (i-1 >= 0) diff[i] += diff[i-1];
            ret[group[i]] = diff[i];
        }
    }
    vector<vector<int>> scc_adj(n);
    vector<int> top_order;
    indegree.assign(n, 0);
    for (int i = 0;i<n; i++) {
        assert(len(graph[i]) == 1);
        int u = root[graph[i][0]], v = root[i];
        if (u != v) {
            scc_adj[u].push_back(v);
            indegree[v]++;
        }
    }
    queue<int> q;
    for (auto i : root_nodes) {
        if (!indegree[i]) q.push(i);
    }
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        top_order.push_back(curr);
        for (const auto& neighbor : scc_adj[curr]) {
            if (--indegree[neighbor] == 0) q.push(neighbor);
        }
    }
    int timer = 0;
    vector<int> tin(n), tout(n), preorder, subtree_sum(n), max_depth(n);
    vector<set<int>> by_depth(n);
    FT tree(n);
    depth.assign(n, -1);
    function<void(int, int, int)> dfs2 = [&](int curr, int par, int dd) {
        depth[curr] = dd;
        tin[curr] = timer++;
        preorder.push_back(curr);
        by_depth[dd].insert(tin[curr]);
        max_depth[curr] = 1;
        for (const auto& neighbor : scc_adj[curr]) {
            if (neighbor != par) {
                dfs2(neighbor, curr, dd+1);
                subtree_sum[curr] += subtree_sum[neighbor];
                max_depth[curr] = max(max_depth[curr], max_depth[neighbor] + 1);
            }
        }
        subtree_sum[curr]++;
        tout[curr] = timer;
    };
    for (auto i : top_order) {
        if (depth[i] == -1) {
            dfs2(i, -1, 0);
        }
    }
    reverse(begin(top_order), end(top_order));
    for (const auto& node : top_order) {
        if (len(root_member[node]) == 1) {
            int ptr = depth[node] + k + 1;
            if (inrange(ptr, 0, n-1)) {
                while (!by_depth[ptr].empty()) {
                    auto it = by_depth[ptr].lower_bound(tin[node]);
                    if (it == by_depth[ptr].end() || *it >= tout[node]) break;
                    tree.update(*it, 1);
                    by_depth[ptr].erase(it);
                }
            }
            ret[node] = subtree_sum[node] - (tree.query(tout[node]) - tree.query(tin[node]));
        }
    }
    
    for (int i = 0;i<n; i++) {
        assert(ret[i] != -1);
        cout << ret[i] << '\n';
    }
    
}


