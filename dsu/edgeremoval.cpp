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
const double PI = 2 * acos(0.0);

constexpr int iinf = 0x3f3f3f3f;
constexpr ll inf = 1000000000000000000;
constexpr ll mod = 1e9 + 7;

#define var(args...)                           \
    {                                          \
        string _s = #args;                     \
        stringstream _ss;                      \
        string ccurr = "";                     \
        for (int zz = 0; zz < len(_s); zz++) { \
            if (_s[zz] == ' ') continue;       \
            if (_s[zz] == ',') {               \
                _ss << ' ' + ccurr;            \
                ccurr = "";                    \
            } else                             \
                ccurr += _s[zz];               \
        }                                      \
        _ss << ' ' + ccurr;                    \
        istream_iterator<string> _it(_ss);     \
        vars(_it, args);                       \
    }
#define debugDecimal(d) cerr << setprecision(d) << fixed

void vars(istream_iterator<string> it) { cerr << '\n'; }
template <typename T, typename... Args>
void vars(istream_iterator<string> it, T a, Args... args) {
    cerr << " [" << *it << ": " << a << "] ";
    vars(++it, args...);
}

#define printVerdict(verdict) \
    cout << (verdict ? "YES" : "NO") << '\n'
#define printDecimal(d) \
    cout << setprecision(d) << fixed
#define printCase(_) \
    cout << "Case #" << (_) << ": "

template <int I, typename TupleT>
ostream &printTupleImpl(ostream &out, const TupleT &t) {
    if constexpr (I < tuple_size_v<TupleT>) {
        out << get<I>(t) << " ";
        printTupleImpl<I + 1, TupleT>(out, t);
    }
    return out;
}
template <typename... Ts>
ostream &operator<<(ostream &out, const tuple<Ts...> &t) {
    return printTupleImpl<0>(out, t);
}

template <int I, typename TupleT>
istream &readTupleImpl(istream &in, TupleT &t) {
    if constexpr (I < tuple_size_v<TupleT>) {
        in >> get<I>(t);
        readTupleImpl<I + 1, TupleT>(in, t);
    }
    return in;
}

template <typename... Ts>
istream &operator>>(istream &in, tuple<Ts...> &t) {
    return readTupleImpl<0>(in, t);
}

template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) { return out << p.first << " " << p.second; }
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &arr) {
    for (const T &a : arr) out << a << " ";
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, const vector<vector<T>> &grid) {
    for (const vector<T> &row : grid) out << row << '\n';
    return out;
}
template <typename T>
istream &operator>>(istream &in, vector<T> &arr) {
    for (T &a : arr) in >> a;
    return in;
}
template <typename T>
void read_pair(vector<pair<T, int>> &a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
}
template <typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
    in >> a.first >> a.second;
    return in;
}

// Error handling for out of bounds
template <typename T>
class vec : public std::vector<T> {
    static_assert(!is_same_v<bool, T>, "vec cannot accept bool type. Please use vector<bool> instead");

   public:
    using std::vector<T>::vector;
    T &operator[](int i) {
        return std::vector<T>::at(i);
    }
    const T &operator[](int i) const {
        return std::vector<T>::at(i);
    }
};

constexpr bool PRINT_EXEC_TIME = true;
constexpr bool EXTERNAL_INPUT = false;
constexpr bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

constexpr int MAXN = 1e5 + 10;

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
};

struct LCA {
    int timer, l;
    vector<int> tin, tout, depth;
    vector<vector<int>> up, path;
    LCA(vector<vector<pair<int, int>>> &C) : timer{}, l{int(ceil(log2(len(C))))}, tin(len(C)), tout(len(C)), depth(len(C)) {
        up.assign(len(C), vector<int>(l + 1));
        path.assign(len(C), vector<int>(l + 1, -1));
        dfs(C, 0, 0, 0, 0);
    }
    void dfs(vector<vector<pair<int, int>>> &C, int v, int p, int dist, int dd) {
        tin[v] = ++timer;
        up[v][0] = p;
        path[v][0] = dist;
        depth[v] = dd;

        for (int i = 1; i <= l; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
            path[v][i] = max(path[v][i - 1], path[up[v][i - 1]][i - 1]);
        }

        for (auto [u, w] : C[v]) {
            if (u != p) dfs(C, u, v, w, dd + 1);
        }

        tout[v] = ++timer;
    }

    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v) {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    }

    int query(int u, int v) {
        assert(is_ancestor(v, u));
        auto step = depth[u] - depth[v];
        int ret = 0;
        for (int i = l; i >= 0; i--) {
            if (step & (1 << i)) {
                ret = max(ret, path[u][i]);
                u = up[u][i];
            }
        }
        return ret;
    }
};

void prayGod() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<bool> used(m, false);
        DSU dsu(n);
        vector<tuple<int, int, int, int>> edges(m);
        vector<vector<pair<int, int>>> graph(n);
        for (int i = 0; i < m; i++) {
            cin >> get<0>(edges[i]) >> get<1>(edges[i]) >> get<2>(edges[i]);
            get<3>(edges[i]) = i;
            get<0>(edges[i])--, get<1>(edges[i])--;
        }
        sort(edges.begin(), edges.end(), [](auto w1, auto w2) {
            return get<2>(w1) < get<2>(w2);
        });
        for (const auto &[u, v, w, id] : edges) {
            if (used[id] = dsu.merge(u, v)) {
                graph[u].emplace_back(v, w);
                graph[v].emplace_back(u, w);
            }
        }

        if (!any_of(dsu.dsu.begin(), dsu.dsu.end(), [&](auto v) { return v == -n; })) {
            cout << -1 << '\n';
            continue;
        }

        LCA lt(graph);
        vector<int> ret;

        for (const auto &[u, v, w, id] : edges) {
            if (!used[id]) {
                auto l = lt.lca(u, v);
                auto max_edge = max(lt.query(u, l), lt.query(v, l));
                if (max_edge == w) ret.push_back(id + 1);
            }
        }

        cout << len(ret) << " ";
        cout << ret << '\n';
    }
}

int main() {
    clock_t start = clock();

    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    if (EXTERNAL_INPUT)
        freopen(INPUT_FILE, "r", stdin);
    if (EXTERNAL_OUTPUT)
        freopen(OUTPUT_FILE, "w", stdout);

    prayGod();

    clock_t end = clock();

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME)
        debugDecimal(5) << time_taken << " s" << '\n';
}