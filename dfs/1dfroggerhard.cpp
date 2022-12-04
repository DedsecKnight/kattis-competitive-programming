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
constexpr ll inf = 1000000000000000010;
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

const char *INPUT_FILE = "cases.txt";
const char *OUTPUT_FILE = "output.txt";

void prayGod() {
    int n;
    cin >> n;
    vec<int> a(n);
    vec<vec<int>> nxt(n), rev_nxt(n);
    cin >> a;

    for (int i = 0; i < n; i++) {
        auto nxt_node = i + a[i];
        if (inrange(nxt_node, 0, n - 1)) {
            nxt[i].push_back(nxt_node);
            rev_nxt[nxt_node].push_back(i);
        }
    }

    vector<bool> visited(n, false);
    vec<int> order, component;
    vec<int> roots(n, 0), root_nodes, indegree(n), root_sizes(n, 0);
    vec<vec<int>> scc_adj(n);
    vec<vec<int>> scc_seen(n);

    function<void(int)> dfs1 = [&](int curr) {
        visited[curr] = true;
        for (auto v : nxt[curr]) {
            if (!visited[v]) dfs1(v);
        }
        order.push_back(curr);
    };

    function<void(int)> dfs2 = [&](int curr) {
        visited[curr] = true;
        component.push_back(curr);
        for (auto v : rev_nxt[curr]) {
            if (!visited[v]) dfs2(v);
        }
    };

    // Step 1: Determine strongly connected components in the graph

    fill(visited.begin(), visited.end(), false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs1(i);
    }

    fill(visited.begin(), visited.end(), false);
    reverse(order.begin(), order.end());

    for (auto v : order) {
        if (!visited[v]) {
            dfs2(v);

            int root = component.front();
            for (auto u : component) {
                roots[u] = root;
                scc_seen[root].push_back(a[u]);
            }
            root_nodes.push_back(root);
            root_sizes[root] = len(component);
            component.clear();
        }
    }

    // Step 2: Build condensation graph from strongly connected components.

    for (int v = 0; v < n; v++) {
        int root_v = roots[v];
        for (auto neighbor : nxt[v]) {
            int root_nxt = roots[neighbor];
            if (root_v != root_nxt) {
                scc_adj[root_nxt].push_back(root_v);
                indegree[root_v]++;
            }
        }
    }

    // Determine traversal order in condensed graph for computing final answer

    deque<int> q;
    vec<int> top_order;

    for (auto r : root_nodes) {
        if (indegree[r] == 0) {
            q.push_back(r);
        }
    }

    while (!q.empty()) {
        auto curr = q.front();
        q.pop_front();
        top_order.push_back(curr);
        for (auto nei : scc_adj[curr]) {
            if (--indegree[nei] == 0) {
                q.push_back(nei);
            }
        }
    }

    ll ret = 0;
    fill(visited.begin(), visited.end(), false);
    umap<int, int> curr_seen;

    function<void(int)> dfs3 = [&](int curr) {
        visited[curr] = true;
        for (auto v : scc_seen[curr]) {
            curr_seen[v]++;
        }
        ret += len(curr_seen) * 1ll * root_sizes[curr];
        for (auto v : scc_adj[curr]) {
            if (!visited[v]) dfs3(v);
        }
        for (auto v : scc_seen[curr]) {
            if (--curr_seen[v] == 0) {
                curr_seen.erase(v);
            }
        }
    };

    for (auto v : top_order) {
        if (!visited[v]) dfs3(v);
    }

    cout << ret << '\n';
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