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

bool ccw(const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
    auto v = a.first * (b.second - c.second) + b.first * (c.second - a.second) +
             c.first * (a.second - b.second);
    return v > 0;
}

inline void prayGod() {
    int n, m;
    cin >> n;
    vector<vector<pair<ll, ll>>> garry(n, vector<pair<ll, ll>>(3));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> garry[i][j].first >> garry[i][j].second;
        }
        if (!ccw(garry[i][0], garry[i][1], garry[i][2])) {
            reverse(garry[i].begin(), garry[i].end());
        }
    }
    cin >> m;
    vector<vector<pair<ll, ll>>> jerry(m, vector<pair<ll, ll>>(3));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> jerry[i][j].first >> jerry[i][j].second;
        }
        if (!ccw(jerry[i][0], jerry[i][1], jerry[i][2])) {
            reverse(jerry[i].begin(), jerry[i].end());
        }
    }
    map<pair<pair<ll, ll>, pair<ll, ll>>,
        vector<tuple<pair<ll, ll>, pair<ll, ll>, int>>>
        bucket;
    auto process = [&](const vector<vector<pair<ll, ll>>>& pts,
                       int on_increment) {
        for (const auto& tri : pts) {
            for (int i = 0; i < 3; i++) {
                auto pp = tri[i], qq = tri[(i + 1) % 3];
                int delta = on_increment;
                if (qq < pp) {
                    swap(pp, qq);
                    delta = -delta;
                }
                if (pp.first == qq.first) {
                    auto slope = make_pair(0, 1e9);
                    auto y_intercept = make_pair(qq.first, 1);
                    bucket[make_pair(slope, y_intercept)].emplace_back(pp, qq,
                                                                       delta);
                } else if (pp.second == qq.second) {
                    auto slope = make_pair(0, 0);
                    auto y_intercept = make_pair(qq.second, 1);
                    bucket[make_pair(slope, y_intercept)].emplace_back(pp, qq,
                                                                       delta);
                } else {
                    auto slope =
                        make_pair(qq.second - pp.second, qq.first - pp.first);
                    auto g = __gcd(slope.first, slope.second);
                    slope.first /= g, slope.second /= g;
                    auto y_intercept = make_pair(
                        slope.second * pp.second - slope.first * pp.first,
                        slope.second);
                    g = __gcd(y_intercept.first, y_intercept.second);
                    y_intercept.first /= g, y_intercept.second /= g;
                    bucket[make_pair(slope, y_intercept)].emplace_back(pp, qq,
                                                                       delta);
                }
            }
        }
    };
    process(garry, 1);
    process(jerry, -1);
    bool matches = true;
    for (const auto& [k, v] : bucket) {
        vector<pair<ll, ll>> pts;
        for (const auto& [p1, p2, _] : v) {
            pts.push_back(p1);
            pts.push_back(p2);
        }
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        vector<int> diff(len(pts) + 1);
        for (const auto& [p1, p2, delta] : v) {
            int lb = lower_bound(pts.begin(), pts.end(), p1) - pts.begin();
            int rb = lower_bound(pts.begin(), pts.end(), p2) - pts.begin();
            diff[lb] += delta, diff[rb] -= delta;
        }
        for (int i = 0; i < len(diff); i++) {
            if (i - 1 >= 0)
                diff[i] += diff[i - 1];
            if (diff[i] != 0) {
                matches = false;
            }
        }
    }
    cout << (matches ? "yes" : "no") << '\n';
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
