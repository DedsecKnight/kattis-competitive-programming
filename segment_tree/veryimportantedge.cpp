#include <bits/stdc++.h>

using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")

#define len(a) static_cast<int>((a).size())
using ll = long long;
using ld = long double;
constexpr const int iinf = 1e9 + 7;
constexpr const ll inf = 1e18;
constexpr const ll mod = 998244353;
#define printDecimal(d) std::cout << std::setprecision(d) << std::fixed

template <typename Fun>
class y_combinator_result {
    Fun fun_;

   public:
    template <typename T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <typename... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
template <typename Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

struct edge {
    int u, v, w;
};

struct query {
    int i, l, r;
};

struct DSU {
    vector<int> dsu;
    explicit DSU(int n) : dsu(n, -1) {}
    int find(int u) { return (dsu[u] < 0 ? u : (dsu[u] = find(dsu[u]))); }
    inline bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            return false;
        }
        if (dsu[u] > dsu[v]) {
            swap(u, v);
        }
        dsu[u] += dsu[v];
        dsu[v] = u;
        return true;
    }
};

struct SegmentTree {
    vector<int> tree;
    int arr_size;
    explicit SegmentTree(int n) : tree(2 * n, iinf), arr_size{n} {}
    inline void set(int i, int x) {
        i += arr_size;
        tree[i] = min(tree[i], x);
        for (; i /= 2;) {
            tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
        }
    };
    inline int query(int l, int r) {
        int ra = iinf, rb = iinf;
        for (l += arr_size, r += arr_size; l < r; l /= 2, r /= 2) {
            if (l % 2) {
                ra = min(ra, tree[l++]);
            }
            if (r % 2) {
                rb = min(tree[--r], rb);
            }
        }
        return min(ra, rb);
    }
    inline void clear() { fill(tree.begin(), tree.end(), iinf); }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    ll mst_cost = 0;
    DSU dsu{n};
    vector<edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.emplace_back(u, v, w);
    }
    std::sort(edges.begin(), edges.end(),
              [](const auto& x, const auto& y) { return x.w < y.w; });
    vector<int> used, extra;
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        if (dsu.merge(edges[i].u, edges[i].v)) {
            used.push_back(i);
            graph[edges[i].u].emplace_back(edges[i].v, edges[i].w);
            graph[edges[i].v].emplace_back(edges[i].u, edges[i].w);
            mst_cost += edges[i].w;
        } else {
            extra.push_back(i);
        }
    }
    int timer = 0;
    vector<int> tin(n, -1), tout(n, -1);
    y_combinator([&](auto self, int curr, int par) -> void {
        tin[curr] = timer++;
        for (const auto& [neighbor, _] : graph[curr]) {
            if (neighbor != par) {
                self(neighbor, curr);
            }
        }
        tout[curr] = timer;
    })(0, -1);
    for (int i = 0; i < m; i++) {
        if (tin[edges[i].u] > tin[edges[i].v]) {
            swap(edges[i].u, edges[i].v);
        }
    }
    ll ret = 0;
    vector<vector<pair<int, int>>> by_dim1(n), by_dim2(n);
    for (auto i : extra) {
        auto [u, v, w] = edges[i];
        by_dim1[tin[u]].emplace_back(tin[v], w);
        by_dim2[tin[v]].emplace_back(tin[u], w);
    }
    vector<int> min_replacement_edges(n - 1, iinf);
    vector<vector<query>> query_dim1(n), query_dim2(n);
    for (int i = 0; i < n - 1; i++) {
        auto [u, v, w] = edges[used[i]];
        if (tin[v] - 1 >= 0) {
            query_dim1[tin[v] - 1].emplace_back(i, tin[v], tout[v] - 1);
        }
        if (tout[v] < n) {
            query_dim2[tout[v]].emplace_back(i, tin[v], tout[v] - 1);
        }
    }
    SegmentTree tree{n};
    for (int i = 0; i < n; i++) {
        for (const auto& [pos, val] : by_dim1[i]) {
            tree.set(pos, val);
        }
        for (const auto& [index, lb, rb] : query_dim1[i]) {
            min_replacement_edges[index] =
                min(min_replacement_edges[index], tree.query(lb, rb + 1));
        }
    }
    tree.clear();
    for (int i = n - 1; i >= 0; i--) {
        for (const auto& [pos, val] : by_dim2[i]) {
            tree.set(pos, val);
        }
        for (const auto& [index, lb, rb] : query_dim2[i]) {
            min_replacement_edges[index] =
                min(min_replacement_edges[index], tree.query(lb, rb + 1));
        }
    }
    for (int i = 0; i < n - 1; i++) {
        assert(min_replacement_edges[i] < iinf);
        ret = max(ret, mst_cost - edges[used[i]].w + min_replacement_edges[i]);
    }
    cout << ret << '\n';
}
