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

const char *INPUT_FILE = "cases.txt";
const char *OUTPUT_FILE = "output.txt";

constexpr int MAXN = 1e5 + 10;

struct TwoSat {
    int N;
    vector<vector<int>> gr;
    vector<int> values;

    TwoSat(int n = 0) : N(n), gr(2 * n) {}

    void either(int f, int j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f].push_back(j ^ 1);
        gr[j].push_back(f ^ 1);
    }

    void setValue(int x) { either(x, x); }

    vector<int> val, comp, z;
    int time = 0;

    int dfs(int i) {
        int low = val[i] = ++time, x;
        z.push_back(i);
        for (int e : gr[i]) {
            if (!comp[e]) {
                low = min(low, val[e] ?: dfs(e));
            }
        }
        if (low == val[i]) {
            do {
                x = z.back();
                z.pop_back();
                comp[x] = low;
                if (values[x >> 1] == -1) {
                    values[x >> 1] = x & 1;
                }
            } while (x != i);
        }
        return val[i] = low;
    }

    bool solve() {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp = val;
        for (int i = 0; i < 2 * N; i++) {
            if (!comp[i]) dfs(i);
        }
        for (int i = 0; i < N; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return 0;
        }
        return 1;
    }
};

void prayGod() {
    int n;
    cin >> n;
    vector<tuple<string, int, int>> investigations(n);
    cin >> investigations;

    int ret = 0;

    auto parse = [&](const string &letters, int player, int cnt, TwoSat &ts) {
        bool is_second = player == 2;
        int first_index = (letters[0] - 'A') * 2 + is_second;
        int second_index = (letters[1] - 'A') * 2 + is_second;
        switch (cnt) {
            case 0: {
                ts.setValue(~first_index);
                ts.setValue(~second_index);
                break;
            }
            case 1: {
                ts.either(first_index, second_index);
                ts.either(~first_index, ~second_index);
                break;
            }
            case 2: {
                ts.setValue(first_index);
                ts.setValue(second_index);
                break;
            }
            default: {
                assert(false);
            }
        }
    };

    for (int c1 = 0; c1 < 26; c1++) {
        for (int c2 = c1 + 1; c2 < 26; c2++) {
            for (int c3 = c2 + 1; c3 < 26; c3++) {
                TwoSat ts(52);
                for (const auto &[letters, player, cnt] : investigations) {
                    parse(letters, player, cnt, ts);
                }
                for (int i = 0; i < 26; i++) {
                    if (i == c1 || i == c2 || i == c3) {
                        ts.setValue(~(i * 2));
                        ts.setValue(~(i * 2 + 1));
                    } else {
                        ts.either(i * 2 + 1, i * 2);
                        ts.either(~(i * 2), ~(i * 2 + 1));
                    }
                }
                ret += ts.solve();
            }
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