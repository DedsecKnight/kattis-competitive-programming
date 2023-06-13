#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

using ui = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

template <typename K, typename V>
using umap = unordered_map<K, V>;

#define null NULL
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

constexpr int iinf = 0x3f3f3f3f;
constexpr ll inf = 1'000'000'000'000'000'000;
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
    cout << (verdict ? "Yes" : "No") << '\n'
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

constexpr int MAXN = 1000;

struct DSU {
    vector<int> dsu;
    explicit DSU(int n) : dsu(n, -1) {}
    int find (int u) {
        return (dsu[u] < 0 ? u : (dsu[u] = find(dsu[u])));
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

template <typename T>
struct RMQ {
    vector<vector<T>> jmp;
    explicit RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= len(V); pw *= 2, k++) {
            jmp.emplace_back(len(V) - pw*2 + 1);
            for (int j = 0; j<len(jmp[k]); j++) {
                jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
            }
        }
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b-a);
        return min(jmp[dep][a], jmp[dep][b-(1<<dep)]);
    }
};

struct LCA {
    int T = 0;
    vector<int> time, path, ret;
    RMQ<int> rmq;
    explicit LCA(const vector<vector<int>>&C) : time(len(C)), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(const vector<vector<int>> &C, int v, int par) {
        time[v] = T++;
        for (int y : C[v]) if (y != par) {
            path.push_back(v); ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }
    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
};

inline void prayGod() {
    int n, q;
    cin >> n >> q;
    vector<int> special_nodes;
    vector<pair<int, int>> special_edges;
    vector<vector<int>> graph(n);
    DSU dsu(n);

    for (int i = 0;i<n+1; i++) {
        int u,v; cin >> u >> v;
        u--, v--;
        if (dsu.merge(u, v)) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        } else {
            special_nodes.push_back(u);
            special_nodes.push_back(v);
            special_edges.emplace_back(u, v);
        }
    }

    LCA lct{graph};
    sort(begin(special_nodes), end(special_nodes));
    special_nodes.erase(unique(begin(special_nodes), end(special_nodes)), end(special_nodes));

    while (q--) {
        int u,v; cin >> u >> v;
        vector<int> nodes{--u, --v};
        nodes.insert(end(nodes), begin(special_nodes), end(special_nodes));
        sort(begin(nodes), end(nodes));
        nodes.erase(unique(begin(nodes), end(nodes)), end(nodes));
        sort(begin(nodes), end(nodes), [&](auto x, auto y) { return lct.time[x] < lct.time[y]; });
        int sz = len(nodes);
        set<int> seen;
        for (int i = 0;i<sz-1; i++) {
            auto l = lct.lca(nodes[i], nodes[i+1]);
            if (!present(seen, l)) {
                seen.insert(l);
                nodes.push_back(l);
            } 
        }
        sort(begin(nodes), end(nodes), [&](auto x, auto y) { return lct.time[x] < lct.time[y]; });
        unordered_map<int, int> F;
        for (int i = 0;i<len(nodes); i++) {
            F[nodes[i]] = i;
        }
        vector<vector<int>> G(len(nodes));
        vector<int> st{nodes[0]};
        for (int i = 1; i<len(nodes); i++) {
            while (!st.empty() && lct.lca(st.back(), nodes[i]) != st.back()) st.pop_back();
            assert(!st.empty());
            G[F[st.back()]].push_back(F[nodes[i]]);
            G[F[nodes[i]]].push_back(F[st.back()]);       
            st.push_back(nodes[i]);
        }
        for (const auto& [a, b] : special_edges) {
            G[F[a]].push_back(F[b]);
            G[F[b]].push_back(F[a]);
        }
        int ret = 0;
        vector<bool> visited(len(nodes), false);
        function<void(int)> dfs = [&](int curr) {
            visited[curr] = true;
            if (F[v] == curr) {
                ret++;
            } else {
                for (const auto& neighbor : G[curr]) {
                    if (!visited[neighbor]) {
                        dfs(neighbor);
                    }
                }
            }
            visited[curr] = false;
        };
        dfs(F[u]);
        cout << ret << '\n';
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

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    debugDecimal(5) << time_taken << " s" << '\n';
#endif
}
