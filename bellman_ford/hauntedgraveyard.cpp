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

namespace KACTL {
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const ll inf = LLONG_MAX;
struct Ed {
    int a, b, w;
    int s() { return a < b ? a : -a; }
};
struct Node {
    ll dist = inf;
    int prev = -1;
    bool reachable = false;
};

void bellmanFord(vector<Node> &nodes, vector<Ed> &eds, int s) {
    nodes[s].dist = 0;
    nodes[s].reachable = true;
    sort(all(eds), [](Ed a, Ed b) { return a.s() < b.s(); });

    int lim = sz(nodes) / 2 + 2;  // /3+100 with shuffled vertices
    rep(i, 0, lim) for (Ed ed : eds) {
        Node cur = nodes[ed.a], &dest = nodes[ed.b];
        if (abs(cur.dist) == inf) continue;
        ll d = cur.dist + ed.w;
        if (d < dest.dist) {
            dest.prev = ed.a;
            dest.dist = (i < lim - 1 ? d : -inf);
            dest.reachable = dest.reachable || cur.reachable;
        }
    }
    rep(i, 0, lim) for (Ed e : eds) {
        if (nodes[e.a].dist == -inf)
            nodes[e.b].dist = -inf;
    }
}
};  // namespace KACTL

constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};

void prayGod() {
    while (true) {
        int n, m;
        cin >> m >> n;
        if (!n && !m) break;

        vector<vector<bool>> is_gravestone(n, vector<bool>(m, false));
        vector<vector<bool>> is_hole(n, vector<bool>(m, false));

        int g;
        cin >> g;
        for (int i = 0; i < g; i++) {
            int x, y;
            cin >> x >> y;
            is_gravestone[n - 1 - y][x] = true;
        }

        set<pair<int, int>> seen_edges;
        vector<KACTL::Node> nodes(n * m);
        vector<KACTL::Ed> edges;
        int e;
        cin >> e;
        for (int i = 0; i < e; i++) {
            int x1, y1, x2, y2, t;
            cin >> y1 >> x1 >> y2 >> x2 >> t;
            x1 = n - 1 - x1, x2 = n - 1 - x2;
            edges.push_back({x1 * m + y1, x2 * m + y2, t});
            seen_edges.emplace(x1 * m + y1, x2 * m + y2);
            is_hole[x1][y1] = true;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < 4; k++) {
                    int new_x = i + dx[k], new_y = j + dy[k];
                    if (!inrange(new_x, 0, n - 1) || !inrange(new_y, 0, m - 1)) continue;
                    if (is_gravestone[i][j] || is_gravestone[new_x][new_y]) continue;
                    auto p = make_pair(i * m + j, new_x * m + new_y);
                    if (!present(seen_edges, p) && !is_hole[i][j] && (i != 0 || j != m - 1)) {
                        edges.push_back({p.first, p.second, 1});
                        seen_edges.insert(p);
                    }
                    swap(p.first, p.second);
                    if (!present(seen_edges, p) && !is_hole[new_x][new_y] && (new_x != 0 || new_y != m - 1)) {
                        edges.push_back({p.first, p.second, 1});
                        seen_edges.insert(p);
                    }
                }
            }
        }

        KACTL::bellmanFord(nodes, edges, (n - 1) * m);
        bool con = false;

        for (int i = 0; i < n * m; i++) {
            if (nodes[i].dist == -KACTL::inf && nodes[i].reachable) {
                cout << "Never" << '\n';
                con = true;
                break;
            }
        }
        if (con) continue;
        if (nodes[m - 1].dist == KACTL::inf) {
            cout << "Impossible" << '\n';
        } else {
            cout << nodes[m - 1].dist << '\n';
        }
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