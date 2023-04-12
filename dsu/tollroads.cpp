#include <math.h>

#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;
using ll = long long;

struct DSU {
    vector<int> dsu;
    DSU(int n) : dsu(n, -1) {}
    int find(int u) {
        if (dsu[u] < 0) return u;
        return dsu[u] = find(dsu[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (dsu[u] > dsu[v]) swap(u, v);
        dsu[u] += dsu[v];
        dsu[v] = u;
        return true;
    }
    void reset() {
        fill(dsu.begin(), dsu.end(), -1);
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<tuple<int, int, int>> edges(m);
    vector<vector<pair<int, int>>> graph(n);
    vector<pair<int, int>> queries(q);

    for (int i = 0; i < m; i++) {
        cin >> get<0>(edges[i]) >> get<1>(edges[i]) >> get<2>(edges[i]);
        get<0>(edges[i])--, get<1>(edges[i])--;
    }

    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
        queries[i].first--, queries[i].second--;
    }

    sort(edges.begin(), edges.end(), [](auto x, auto y) {
        return get<2>(x) < get<2>(y);
    });

    DSU dsu(n);
    for (const auto &[u, v, w] : edges) {
        if (dsu.merge(u, v)) {
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }
    }

    int l = ceil(log2(n));

    vector<vector<int>> up(n, vector<int>(l + 1));
    vector<vector<int>> path(n, vector<int>(l + 1));

    vector<int> tin(n), tout(n), depth(n);
    int timer = 0;
    function<void(int, int, int, int)> dfs = [&](int v, int p, int w, int dd) {
        tin[v] = ++timer;
        up[v][0] = p;
        path[v][0] = w;
        depth[v] = dd;
        for (int i = 1; i <= l; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
            path[v][i] = max(path[v][i - 1], path[up[v][i - 1]][i - 1]);
        }
        for (auto [u, ww] : graph[v]) {
            if (u != p) dfs(u, v, ww, dd + 1);
        }
        tout[v] = ++timer;
    };

    auto is_ancestor = [&](int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    };

    auto lca = [&](int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    };

    auto query = [&](int u, int v) {
        assert(is_ancestor(v, u));
        auto d = depth[u] - depth[v];
        int ret = 0;
        for (int i = l; i >= 0; i--) {
            if (d & (1 << i)) {
                ret = max(ret, path[u][i]);
                u = up[u][i];
            }
        }
        return ret;
    };

    dfs(0, 0, 0, 0);

    map<int, vector<pair<int, int>>> bucket;
    vector<pair<int, int>> ans(q);

    for (int i = 0; i < q; i++) {
        auto [a, b] = queries[i];
        auto p = lca(a, b);
        auto cost = max(query(a, p), query(b, p));
        bucket[cost].emplace_back(a, i);
        ans[i].first = cost;
    }

    dsu.reset();
    int prv = -1;

    for (const auto &[u, v, w] : edges) {
        if (prv == -1) {
            prv = w;
        } else if (w > prv) {
            for (const auto &[a, i] : bucket[prv]) {
                ans[i].second = -dsu.dsu[dsu.find(a)];
            }
            prv = w;
        }
        dsu.merge(u, v);
    }
    for (const auto &[a, i] : bucket[prv]) {
        ans[i].second = -dsu.dsu[dsu.find(a)];
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i].first << " " << ans[i].second << '\n';
    }
}