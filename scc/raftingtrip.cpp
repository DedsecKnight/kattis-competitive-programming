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

constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};

void prayGod() {
    int n, m;
    cin >> n >> m;
    vec<string> grid(n);
    cin >> grid;

    vec<vec<int>> graph(n * m), rev_graph(n * m), adj_scc(n * m), root_member(n * m);
    vector<bool> used(n * m, false);
    vec<int> order, component;
    vec<int> roots(n * m, 0), root_nodes, indegree(n * m, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            switch (grid[i][j]) {
                case 'v': {
                    if (i + 1 < n && grid[i + 1][j] != '.' && grid[i + 1][j] != '#') {
                        int from = (i + 1) * m + j;
                        int to = i * m + j;
                        graph[from].push_back(to);
                        rev_graph[to].push_back(from);
                    }
                    break;
                }
                case '<': {
                    if (j - 1 >= 0 && grid[i][j - 1] != '.' && grid[i][j - 1] != '#') {
                        int from = i * m + j - 1;
                        int to = i * m + j;
                        graph[from].push_back(to);
                        rev_graph[to].push_back(from);
                    }
                    break;
                }
                case '^': {
                    if (i - 1 >= 0 && grid[i - 1][j] != '.' && grid[i - 1][j] != '#') {
                        int from = (i - 1) * m + j;
                        int to = i * m + j;
                        graph[from].push_back(to);
                        rev_graph[to].push_back(from);
                    }
                    break;
                }
                case '>': {
                    if (j + 1 < m && grid[i][j + 1] != '.' && grid[i][j + 1] != '#') {
                        int from = i * m + j + 1;
                        int to = i * m + j;
                        graph[from].push_back(to);
                        rev_graph[to].push_back(from);
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }

    function<void(int)> dfs1 = [&](int v) {
        used[v] = true;
        for (auto u : graph[v]) {
            if (!used[u]) dfs1(u);
        }
        order.push_back(v);
    };

    function<void(int)> dfs2 = [&](int v) {
        used[v] = true;
        component.push_back(v);
        for (auto u : rev_graph[v]) {
            if (!used[u]) dfs2(u);
        }
    };

    for (int i = 0; i < n * m; i++) {
        if (!used[i] && grid[i / m][i % m] != '.' && grid[i / m][i % m] != '#') dfs1(i);
    }

    used.assign(n * m, false);
    reverse(order.begin(), order.end());

    for (auto v : order) {
        if (!used[v]) {
            dfs2(v);
            int root = component.front();

            for (auto u : component) {
                roots[u] = root;
            }
            root_member[root].insert(root_member[root].end(), component.begin(), component.end());

            root_nodes.push_back(root);
            component.clear();
        }
    }

    for (int v = 0; v < n * m; v++) {
        if (grid[v / m][v % m] == '.' || grid[v / m][v % m] == '#') continue;
        for (auto u : graph[v]) {
            int root_v = roots[v], root_u = roots[u];
            if (root_u != root_v) {
                adj_scc[root_v].push_back(root_u);
            }
        }
    }

    for (auto i : root_nodes) {
        sort(adj_scc[i].begin(), adj_scc[i].end());
        adj_scc[i].erase(unique(adj_scc[i].begin(), adj_scc[i].end()), adj_scc[i].end());
        for (const auto &v : adj_scc[i]) {
            indegree[v]++;
        }
    }

    vec<int> top_order;
    deque<int> q;

    for (auto i : root_nodes) {
        if (indegree[i] == 0) q.push_back(i);
    }

    while (!q.empty()) {
        auto curr = q.front();
        q.pop_front();
        top_order.push_back(curr);
        for (auto neighbor : adj_scc[curr]) {
            if (--indegree[neighbor] == 0) {
                q.push_back(neighbor);
            }
        }
    }

    map<pair<int, int>, int> cnt;
    int ret = 0;

    function<void(int)> dfs = [&](int curr) {
        used[curr] = true;
        for (auto member : root_member[curr]) {
            int i = member / m, j = member % m;
            for (int k = 0; k < 4; k++) {
                int new_x = i + dx[k], new_y = j + dy[k];
                if (!inrange(new_x, 0, n - 1) || !inrange(new_y, 0, m - 1)) continue;
                if (grid[new_x][new_y] == '#') cnt[make_pair(new_x, new_y)]++;
            }
        }
        ret = max(ret, len(cnt));
        for (const auto &neighbor : adj_scc[curr]) {
            assert(!used[neighbor]);
            dfs(neighbor);
        }
        for (auto member : root_member[curr]) {
            int i = member / m, j = member % m;
            for (int k = 0; k < 4; k++) {
                int new_x = i + dx[k], new_y = j + dy[k];
                if (!inrange(new_x, 0, n - 1) || !inrange(new_y, 0, m - 1)) continue;
                if (grid[new_x][new_y] == '#') {
                    auto pos = make_pair(new_x, new_y);
                    if (--cnt[pos] == 0) cnt.erase(pos);
                }
            }
        }
    };

    used.assign(n * m, false);

    for (const auto &p : top_order) {
        if (!used[p]) {
            dfs(p);
        }
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