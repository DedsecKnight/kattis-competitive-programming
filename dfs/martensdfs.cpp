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
constexpr ll inf = 1'000'000'000'000'000;
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
template <typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
    in >> a.first >> a.second;
    return in;
}

static constexpr const int MAXN = 1e6 + 10;

inline void prayGod() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::unordered_set<int>> graph(n);
    std::vector<std::vector<int>> og(n);
    for (int i = 0;i<m; i++) {
        int u,v;
        std::cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
        og[u].push_back(v);
        og[v].push_back(u);
    }
    std::vector<int> l;
    int buf = 0;
    while (std::cin >> buf) {
        l.push_back(buf);
    }
    l.push_back(-1);
    bool valid = true;
    int nxt_index = 0;
    std::vector<bool> visited(n);
    function<void(int, int)> dfs = [&](int curr, int par) {
        if (!valid) return;
        visited[curr] = true;
        graph[curr].erase(par);
        std::vector<int> marked;
        for (const auto& neighbor : graph[curr]) {
            if (visited[neighbor]) marked.push_back(neighbor);
        }
        for (const auto& neighbor : marked) {
            graph[curr].erase(neighbor);
        }
        for (const auto& neighbor : og[curr]) {
            graph[neighbor].erase(curr);
        }
        while (!graph[curr].empty()) {
            if (!present(graph[curr], l[nxt_index])) {
                valid = false;
                return;
            }
            graph[curr].erase(l[nxt_index]);
            auto val = l[nxt_index++];
            if (visited[val]) {
                valid = false;
                return;
            }
            dfs(val, curr);
            if (!valid) {
                return;
            }
        }
    };
    while (valid && l[nxt_index] != -1) {
        auto val = l[nxt_index++];
        dfs(val, -1);
    }
    printVerdict(valid);
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