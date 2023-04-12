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

struct BiconnectedComponent {
    vector<int> num, st;
    vector<vector<pair<int, int>>> ed;
    int Time = 0, eid = 0;
    BiconnectedComponent(int n) : ed(n) {}
    void add_edge(int i, int j) {
        ed[i].emplace_back(j, eid);
        ed[j].emplace_back(i, eid++);
    }
    template <class F>
    int dfs(int at, int par, F &f) {
        int me = num[at] = ++Time, e, y, top = me;
        for (auto pa : ed[at])
            if (pa.second != par) {
                tie(y, e) = pa;
                if (num[y]) {
                    top = min(top, num[y]);
                    if (num[y] < me)
                        st.push_back(e);
                } else {
                    int si = len(st);
                    int up = dfs(y, e, f);
                    top = min(top, up);
                    if (up == me) {
                        st.push_back(e);
                        f(vector<int>(st.begin() + si, st.end()));
                        st.resize(si);
                    } else if (up < me)
                        st.push_back(e);
                    else { /* e is a bridge */
                    }
                }
            }
        return top;
    }

    template <class F>
    void bicomps(F f) {
        num.assign(len(ed), 0);
        for (int i = 0; i < len(ed); i++)
            if (!num[i]) dfs(i, -1, f);
    }
};

void prayGod() {
    int n;
    cin >> n;
    vec<pair<ld, ld>> p(n);
    cin >> p;
    p.insert(p.begin(), make_pair(0.0, 0.0));
    n++;

    vec<vec<ld>> d2(n, vec<ld>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            d2[i][j] = (p[i].first - p[j].first) * (p[i].first - p[j].first) + (p[i].second - p[j].second) * (p[i].second - p[j].second);
        }
    }

    ld low = 0.0, high = 3e9 + 10;

    for (auto _ = 0; _ < 60; _++) {
        auto mid = low + (high - low) / 2;
        BiconnectedComponent ds(n);
        vec<int> parent(n, -1);
        vector<bool> marked(n, false);
        vec<pair<int, int>> edges;
        marked[0] = true;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (d2[i][j] <= mid * mid) {
                    ds.add_edge(i, j);
                    if (!i) marked[j] = true;
                    edges.emplace_back(i, j);
                }
            }
        }

        ds.bicomps([&](const vector<int> &edgeList) {
            bool has_origin = any_of(edgeList.begin(), edgeList.end(), [&](auto x) {
                return !edges[x].first;
            });
            if (has_origin) {
                for (const auto &idx : edgeList) {
                    marked[edges[idx].first] = marked[edges[idx].second] = true;
                }
            }
        });

        if (all_of(marked.begin(), marked.end(), [&](auto x) { return x; })) {
            high = mid;
        } else {
            low = mid;
        }
    }

    printDecimal(8) << high << '\n';
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
