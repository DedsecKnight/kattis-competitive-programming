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

constexpr int MAXN = 1e6 + 1;

void prayGod() {
    int n;
    cin >> n;
    vector<int> v(n);
    cin >> v;

    vector<vector<int>> graph(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[--a].push_back(--b);
        graph[b].push_back(a);
    }

    auto rb = max(*max_element(v.begin(), v.end()), n) * 2;

    vector<vector<int>> pf(rb + 1);
    for (int i = 2; i <= rb; i++) {
        int curr = i;
        for (int d = 2; d * d <= curr; d++) {
            if (curr % d == 0) {
                pf[i].push_back(d);
                while (curr % d == 0) curr /= d;
            }
        }
        if (curr > 1) pf[i].push_back(curr);
    }

    vector<vector<int>> dp(n, vector<int>(rb + 1, iinf));

    function<void(int, int)> dfs = [&](int curr, int par) {
        for (int i = 2; i <= rb; i++) {
            dp[curr][i] = v[curr] == i ? 0 : i;
        }
        for (const auto &neighbor : graph[curr]) {
            if (neighbor == par) continue;
            dfs(neighbor, curr);
            vector<int> by_prime(rb + 1, iinf);
            for (int x = 2; x <= rb; x++) {
                for (auto &&d : pf[x]) {
                    by_prime[d] = min(by_prime[d], dp[neighbor][x]);
                }
            }
            for (int x = 2; x <= rb; x++) {
                int best = iinf;
                for (auto &&d : pf[x]) {
                    best = min(best, by_prime[d]);
                }
                dp[curr][x] += best;
            }
        }
    };
    dfs(0, -1);
    cout << *min_element(dp[0].begin(), dp[0].end()) << '\n';
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