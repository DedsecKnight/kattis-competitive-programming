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

struct godly_data_structure {
    int N;
    vector<int> depth;
    map<pair<int, int>, int> range_to_root_left, range_to_root_right;
    set<pair<int, int>> left_ranges, right_ranges;
    explicit godly_data_structure(int n) : N{n}, depth(n, -1) {}
    void insert_helper(map<pair<int, int>, int>& range_to_root,
                       set<pair<int, int>>& ranges_set,
                       pair<int, int> replaced_range, int val) {
        int root = range_to_root[replaced_range];
        ranges_set.erase(replaced_range);
        range_to_root.erase(replaced_range);
        if (replaced_range.first < val) {
            range_to_root_left.emplace(make_pair(replaced_range.first, val - 1),
                                       val);
            left_ranges.emplace(replaced_range.first, val - 1);
        }
        if (val < replaced_range.second) {
            range_to_root_right.emplace(
                make_pair(val + 1, replaced_range.second), val);
            right_ranges.emplace(val + 1, replaced_range.second);
        }
        depth[val] = depth[root] + 1;
    }
#define INSERT_AT_LEFT(replaced_range, val) \
    insert_helper(range_to_root_left, left_ranges, replaced_range, val)

#define INSERT_AT_RIGHT(replaced_range, val) \
    insert_helper(range_to_root_right, right_ranges, replaced_range, val)

    int insert(int x) {
        if (left_ranges.empty() && right_ranges.empty()) {
            if (x - 1 >= 0) {
                range_to_root_left[make_pair(0, x - 1)] = x;
                left_ranges.emplace(0, x - 1);
            }
            if (x + 1 < N) {
                range_to_root_right[make_pair(x + 1, N - 1)] = x;
                right_ranges.emplace(x + 1, N - 1);
            }
            return depth[x] = 0;
        }
        if (!left_ranges.empty()) {
            auto it = left_ranges.upper_bound(make_pair(x + 1, -1));
            if ((it--) != left_ranges.begin()) {
                if (inrange(x, it->first, it->second)) {
                    INSERT_AT_LEFT(*it, x);
                    return depth[x];
                }
            }
        }
        if (!right_ranges.empty()) {
            auto it = right_ranges.upper_bound(make_pair(x + 1, -1));
            if ((it--) != right_ranges.begin()) {
                if (inrange(x, it->first, it->second)) {
                    INSERT_AT_RIGHT(*it, x);
                    return depth[x];
                }
            }
        }
        assert(false);
        return -1;
    }
};

inline void prayGod() {
    int n;
    cin >> n;
    godly_data_structure gds{n};
    ll total = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cout << (total += gds.insert(--x)) << '\n';
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

    double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    debugDecimal(5) << time_taken << " s" << '\n';
#endif
}
