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
constexpr ll inf = 1'000'000'000'000'000'000;
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
    cout << (verdict ? "Yes" : "No") << '\n'
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

constexpr int MAXN = 1000;

struct Tree {
    int n; 
    ll all;
    vector<pair<ll, ll >> d2, d;
    vector<ll> l;
    vector<vector<int>> graph;
    explicit Tree(int sz) : n{sz}, all{}, d2(sz), d(sz), l(sz), graph(sz) {
        for (int i = 0;i<sz-1; i++) {
            int u,v; cin >> u >> v;
            graph[--u].push_back(--v);
            graph[v].push_back(u);
        }
        dfs1(0, -1);
        dfs2(0, -1);
        for (int i = 0;i <n; i++) {
            all += fd2(i);
        }
    }
    void dfs1(int curr, int par) {
        l[curr] = 1;
        for (const auto& neighbor : graph[curr]) {
            if (neighbor == par) continue;
            dfs1(neighbor, curr);
            d2[curr].first += d2[neighbor].first + 2*d[neighbor].first + l[neighbor];
            d[curr].first += d[neighbor].first + l[neighbor];
            l[curr] += l[neighbor];
        }
    }
    void dfs2(int curr, int par) {
        ll t2 = 0, t1 = 0;
        for (const auto& neighbor : graph[curr]) {
            if (neighbor == par) continue;
            t2 += d2[neighbor].first + 4*d[neighbor].first+4*l[neighbor];
            t1 += d[neighbor].first+2*l[neighbor];
            d2[neighbor].second += d2[curr].second + 2*d[curr].second+n-l[curr]+1;
            d[neighbor].second += d[curr].second + n-l[curr]+1;
        }
        for (const auto& neighbor : graph[curr]) {
            if (neighbor == par) continue;
            d2[neighbor].second += t2 - (d2[neighbor].first+4*d[neighbor].first+4*l[neighbor]);
            d[neighbor].second += t1 - (d[neighbor].first+2*l[neighbor]);
            dfs2(neighbor, curr);
        }
    }
    ll fd2(int i) { return d2[i].first + d2[i].second; }
    ll fd(int i) { return d[i].first + d[i].second; }
};

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; } 
};

struct LineContainer : multiset<Line, less<>> {
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { return a/b-((a^b)<0 && a%b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p; 
    }
    void add(ll k, ll m) { 
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

inline void prayGod() {
    int n, m; 
    cin >> n;
    Tree A(n);
    cin >> m;
    Tree B(m);
    LineContainer container;
    for (int i = 0;i<n; i++) {
        container.add(-(n+A.fd(i))*2ll, -(m*1ll*n+A.fd(i)*m*2+A.fd2(i)*m));
    }
    ll ret = LLONG_MAX;
    for (int i = 0;i< m; i++) {
        ret = min(ret, -container.query(B.fd(i))+B.fd2(i)*n);
    }
    assert(ret < LLONG_MAX);
    cout << (ret*2 + B.all + A.all) / 2 << '\n';
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
