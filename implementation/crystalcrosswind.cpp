#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

using ui = unsigned int;
using ll = int64_t;
using ull = uint64_t;
using ld = long double;

template <typename K, typename V>
using umap = unordered_map<K, V>;

#define null NULL
#define len(a) static_cast<int>((a).size())
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
            if (_s[zz] == ' ')                 \
                continue;                      \
            if (_s[zz] == ',') {               \
                _ss << ' ' + ccurr;            \
                ccurr = "";                    \
            } else {                           \
                ccurr += _s[zz];               \
            }                                  \
        }                                      \
        _ss << ' ' + ccurr;                    \
        istream_iterator<string> _it(_ss);     \
        vars(_it, args);                       \
    }
#define debugDecimal(d) cerr << setprecision(d) << fixed

void vars(istream_iterator<string> it) {
    cerr << '\n';
}
template <typename T, typename... Args>
void vars(istream_iterator<string> it, T a, Args... args) {
    cerr << " [" << *it << ": " << a << "] ";
    vars(++it, args...);
}

#define printVerdict(verdict) cout << (verdict ? "YES" : "NO") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define printCase(_) cout << "Case #" << (_) << ": "

template <int I, typename TupleT>
ostream& printTupleImpl(ostream& out, const TupleT& t) {
    if constexpr (I < tuple_size_v<TupleT>) {
        out << get<I>(t) << " ";
        printTupleImpl<I + 1, TupleT>(out, t);
    }
    return out;
}
template <typename... Ts>
ostream& operator<<(ostream& out, const tuple<Ts...>& t) {
    return printTupleImpl<0>(out, t);
}

template <int I, typename TupleT>
istream& readTupleImpl(istream& in, TupleT& t) {
    if constexpr (I < tuple_size_v<TupleT>) {
        in >> get<I>(t);
        readTupleImpl<I + 1, TupleT>(in, t);
    }
    return in;
}

template <typename... Ts>
istream& operator>>(istream& in, tuple<Ts...>& t) {
    return readTupleImpl<0>(in, t);
}

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

inline void prayGod() {
    int n, m, k;
    cin >> m >> n >> k;
    vector<pair<int, int>> wind_dir(k);
    vector<bitset<10>> requirement(n * m);
    vector<vector<int>> graph(n * m + 1), rev_graph(n * m + 1);
    auto add_edge = [&](int from, int to) {
        graph[from].push_back(to);
        rev_graph[to].push_back(from);
    };
    for (int i = 0; i < k; i++) {
        cin >> wind_dir[i];
        swap(wind_dir[i].first, wind_dir[i].second);
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++) {
            int x, y;
            cin >> y >> x;
            x--, y--;
            requirement[x * m + y].set(i);
            int bx = x - wind_dir[i].first, by = y - wind_dir[i].second;
            if (inrange(bx, 0, n - 1) && inrange(by, 0, m - 1)) {
                add_edge(bx * m + by, n * m);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int z = 0; z < k; z++) {
                if (!requirement[i * m + j][z]) {
                    int nx = i - wind_dir[z].first, ny = j - wind_dir[z].second;
                    if (!inrange(nx, 0, n - 1) || !inrange(ny, 0, m - 1)) {
                        add_edge(i * m + j, n * m);
                    } else {
                        add_edge(i * m + j, nx * m + ny);
                    }
                }
            }
        }
    }
    queue<int> q;
    vector<bool> invalid_position(n * m + 1, false), required(n * m + 1, false);
    invalid_position[n * m] = true;
    q.push(n * m);
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        for (const auto& neighbor : rev_graph[curr]) {
            if (!invalid_position[neighbor]) {
                invalid_position[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    for (int i = 0; i < n * m; i++) {
        if (requirement[i].any()) {
            required[i] = true;
            q.push(i);
        }
    }
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        for (const auto& neighbor : graph[curr]) {
            if (!required[neighbor]) {
                q.push(neighbor);
                required[neighbor] = true;
            }
        }
    }
    vector<vector<char>> grid(n, vector<char>(m, '.'));
    vector<pair<int, int>> extra;
    for (int i = 0; i < n * m; i++) {
        if (required[i]) {
            grid[i / m][i % m] = '#';
        } else if (!invalid_position[i]) {
            extra.emplace_back(i / m, i % m);
        }
    }
    for (const auto& row : grid) {
        for (const auto& elem : row) {
            cout << elem;
        }
        cout << '\n';
    }
    cout << '\n';
    for (const auto& [x, y] : extra) {
        grid[x][y] = '#';
    }
    for (const auto& row : grid) {
        for (const auto& elem : row) {
            cout << elem;
        }
        cout << '\n';
    }
    cout << '\n';
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
