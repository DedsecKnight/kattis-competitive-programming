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

struct Query {
    int l, r, idx, block_size;
    Query(int _l, int _r, int _idx, int _bsz) : l{_l}, r{_r}, idx{_idx}, block_size{_bsz} {}
    bool operator<(const Query &other) {
        assert(block_size == other.block_size);
        if (l / block_size != other.l / other.block_size) return l / block_size < other.l / other.block_size;
        return r < other.r;
    }
};

void prayGod() {
    int n, m, k;
    cin >> n >> m >> k;

    vec<int> male(n), female(n);
    cin >> male >> female;

    vec<int> fcount(k), mcount(k), pcount(k);
    int sqrt_n = int(sqrt(n));

    vec<Query> queries;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        queries.emplace_back(l, r, i, sqrt_n);
    }

    vec<int> ret(m);
    sort(queries.begin(), queries.end());

    int total = 0;

    int curr_l = 0, curr_r = -1;
    for (const auto &query : queries) {
        while (curr_r < query.r) {
            curr_r++;
            int old = pcount[male[curr_r]];
            if (male[curr_r] != female[curr_r]) old += pcount[female[curr_r]];

            pcount[male[curr_r]] = min(fcount[male[curr_r]], ++mcount[male[curr_r]]);
            pcount[female[curr_r]] = min(++fcount[female[curr_r]], mcount[female[curr_r]]);

            total = total - old + pcount[male[curr_r]];
            if (male[curr_r] != female[curr_r]) total += pcount[female[curr_r]];
        }
        while (curr_r > query.r) {
            int old = pcount[male[curr_r]];
            if (male[curr_r] != female[curr_r]) old += pcount[female[curr_r]];

            pcount[male[curr_r]] = min(fcount[male[curr_r]], --mcount[male[curr_r]]);
            pcount[female[curr_r]] = min(--fcount[female[curr_r]], mcount[female[curr_r]]);

            total = total - old + pcount[male[curr_r]];
            if (male[curr_r] != female[curr_r]) total += pcount[female[curr_r]];

            curr_r--;
        }
        while (curr_l < query.l) {
            int old = pcount[male[curr_l]];
            if (male[curr_l] != female[curr_l]) old += pcount[female[curr_l]];

            pcount[male[curr_l]] = min(fcount[male[curr_l]], --mcount[male[curr_l]]);
            pcount[female[curr_l]] = min(--fcount[female[curr_l]], mcount[female[curr_l]]);

            total = total - old + pcount[female[curr_l]];
            if (male[curr_l] != female[curr_l]) total += pcount[male[curr_l]];
            curr_l++;
        }
        while (curr_l > query.l) {
            curr_l--;

            int old = pcount[male[curr_l]];
            if (male[curr_l] != female[curr_l]) old += pcount[female[curr_l]];

            pcount[male[curr_l]] = min(fcount[male[curr_l]], ++mcount[male[curr_l]]);
            pcount[female[curr_l]] = min(++fcount[female[curr_l]], mcount[female[curr_l]]);

            total = total - old + pcount[female[curr_l]];
            if (male[curr_l] != female[curr_l]) total += pcount[male[curr_l]];
        }
        ret[query.idx] = total;
    }
    for (int i = 0; i < m; i++) {
        cout << ret[i] << '\n';
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