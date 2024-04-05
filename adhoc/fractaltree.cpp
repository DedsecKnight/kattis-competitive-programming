#include <bits/stdc++.h>
#ifdef LLOCAL
#include "debug.h"
#else
#define var(...)
#define debugArr(...)
#endif

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

using ui = unsigned int;
using ll = long long;
using ull = uint64_t;
using ld = long double;

#define len(a) static_cast<int>((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

static constexpr const int iinf = 0x3f3f3f3f;
static constexpr const ll inf = 1'000'000'000'000'000;
static constexpr const ll mod = 1e9 + 7;

#define debugDecimal(d) cerr << setprecision(d) << fixed
#define printVerdict(verdict) cout << (verdict ? "YES" : "NO") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define printCase(_) cout << "Case #" << (_) << ": "

template <typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p) {
    return out << p.first << " " << p.second;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
    for (const T& a : arr)
        out << a << " ";
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& grid) {
    for (const vector<T>& row : grid)
        out << row << '\n';
    return out;
}
template <typename T>
istream& operator>>(istream& in, vector<T>& arr) {
    for (T& a : arr)
        in >> a;
    return in;
}
template <typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) {
    in >> a.first >> a.second;
    return in;
}

template <typename Fun>
class y_combinator_result {
    Fun fun_;

   public:
    template <typename T>
    explicit y_combinator_result(T&& fun) : fun_{std::forward<T>(fun)} {}

    template <typename... ArgTs>
    decltype(auto) operator()(ArgTs&&... args) {
        return fun_(std::ref(*this), std::forward<ArgTs>(args)...);
    }
};

template <typename Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

int count_leaves(const vector<vector<int>>& graph, int node, int par) {
    bool is_leaf = true;
    int ret = 0;
    for (const auto& neighbor : graph[node]) {
        if (neighbor == par)
            continue;
        is_leaf = false;
        ret += count_leaves(graph, neighbor, node);
    }
    return ret + is_leaf;
}

template <class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= len(V); pw *= 2, ++k) {
            jmp.emplace_back(len(V) - pw * 2 + 1);
            for (int j = 0; j < len(jmp[k]); j++)
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b);  // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vector<int> time, path, ret, depth;
    RMQ<int> rmq;

    LCA(vector<vector<int>>& C)
        : time(len(C)), depth(len(C)), rmq((dfs(C, 0, -1, 0), ret)) {}
    void dfs(vector<vector<int>>& C, int v, int par, int dd) {
        time[v] = T++;
        depth[v] = dd;
        for (int y : C[v])
            if (y != par) {
                path.push_back(v), ret.push_back(time[v]);
                dfs(C, y, v, dd + 1);
            }
    }

    int lca(int a, int b) {
        if (a == b)
            return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    int dist(int a, int b) {
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    }
};

inline void prayGod() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        graph[p].push_back(i);
        graph[i].push_back(p);
    }
    int k, q;
    cin >> k >> q;
    int min_leaf = -1;
    int num_leaves = count_leaves(graph, 0, -1);
    if (num_leaves == 1) {
        while (q--) {
            int a, b;
            cin >> a >> b;
            cout << abs(a - b) << '\n';
        }
        return;
    }
    LCA lct{graph};
    ll curr_leaves = num_leaves;
    vector<ll> f(1);
    f[0] = n;
    while (f.back() <= 1e10 && len(f) <= k) {
        f.push_back(f.back() + curr_leaves * 1ll * (n - 1));
        curr_leaves *= num_leaves;
    }
    vector<vector<pair<ll, int>>> level_bounds(len(f));
    vector<int> order;
    auto dfs_level = y_combinator(
        [&](auto self, int curr, int par, int lvl, ll& timer) -> void {
            bool is_leaf = true;
            for (const auto& neighbor : graph[curr]) {
                if (neighbor != par) {
                    is_leaf = false;
                }
            }
            level_bounds[lvl].emplace_back(timer, curr);
            if (lvl == 0) {
                order.push_back(curr);
            }
            if (is_leaf) {
                if (lvl == 0 && min_leaf == -1) {
                    min_leaf = timer;
                }
                timer += (lvl - 1 >= 0 ? f[lvl - 1] : 1);
            } else {
                timer++;
            }
            for (const auto& neighbor : graph[curr]) {
                if (neighbor != par)
                    self(neighbor, curr, lvl, timer);
            }
        });
    for (int i = 0; i < len(f); i++) {
        ll timer = 0;
        dfs_level(0, -1, i, timer);
    }
    auto special_case = y_combinator([&](auto self, int a, int b,
                                         int lvl) -> ll {
        int x = upper_bound(level_bounds[lvl].begin(), level_bounds[x].end(),
                            make_pair(a * 1ll, n + 1)) -
                level_bounds[lvl].begin() - 1;
        int y = upper_bound(level_bounds[lvl].begin(), level_bounds[lvl].end(),
                            make_pair(b * 1ll, n + 1)) -
                level_bounds[lvl].begin() - 1;
        int ret = 0;
        if (x != y) {
            ret += lct.dist(level_bounds[lvl][x].second,
                            level_bounds[lvl][y].second);
            if (a != level_bounds[lvl][x].first) {
                ret += self(0, a - level_bounds[lvl][x].first, lvl - 1);
            }
            if (b != level_bounds[lvl][y].first) {
                ret += self(0, b - level_bounds[lvl][y].first, lvl - 1);
            }
        } else {
            ret += self(a - level_bounds[lvl][x].first,
                        b - level_bounds[lvl][x].first, lvl - 1);
        }
        return ret;
    });
    auto solve_0 = y_combinator([&](auto self, int x, int lvl) -> ll {
        if (lvl < len(f)) {
            return special_case(0, x, lvl);
        }
        if (x <= min_leaf) {
            return lct.dist(order[0], order[x]);
        }
        int alpha = min((x - 1) / min_leaf, lvl - len(f) + 1);
        return self(x - alpha * min_leaf, lvl - alpha) +
               lct.dist(0, order[min_leaf]) * 1ll * alpha;
    });
    auto solve = y_combinator([&](auto self, int a, int b, int lvl) -> ll {
        if (lvl < len(f)) {
            return special_case(a, b, lvl);
        }
        if (b <= min_leaf) {
            return lct.dist(order[a], order[b]);
        }
        if (a <= min_leaf) {
            return lct.dist(order[a], order[min_leaf]) +
                   solve_0(b - min_leaf, lvl - 1);
        }
        int alpha =
            min({(a - 1) / min_leaf, (b - 1) / min_leaf, lvl - len(f) + 1});
        return self(a - min_leaf * alpha, b - min_leaf * alpha, lvl - alpha);
    });
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a > b) {
            swap(a, b);
        }
        cout << solve(a, b, k) << '\n';
    }
}

int main() {
#ifdef LLOCAL
    clock_t start = clock();
#endif
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    prayGod();
#ifdef LLOCAL
    clock_t end = clock();

    double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    debugDecimal(5) << time_taken << " s" << '\n';
#endif
}
