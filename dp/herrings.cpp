#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

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
constexpr ll inf = 10000000000;
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
int dp[10001][8][3];
string n,l;
int sz;

int new_mask(int idx, int a, int b, int other, int old_mask) {
    int ret = 0;
    if ((old_mask & (1 << 0)) && a == l[idx]-'0') ret |= (1 << 0);
    if ((old_mask & (1 << 1)) && b == l[idx]-'0') ret |= (1 << 1);
    if ((old_mask & (1 << 2)) && other == l[idx]-'0') ret |= (1<<2);
    return ret;
}

int solve(int idx, int mask, int tens) {
    if (idx >= sz) return int(tens == 0);
    if (dp[idx][mask][tens] != -1) return dp[idx][mask][tens];
    int ret = 0;
    int target = tens*10+(n[idx]-'0');
    vector<int> start(3);
    for (int i = 0; i<3; i++) {
        if (mask&(1<<i)) start[i] = l[idx]-'0';
    }  
    for (int a = start[0]; a < 10; a++) {
        for (int b = start[1]; a != 3 && b < 10; b++) {
            for (int iter = 0, other = target-a-b; b != 3 && iter < 3; iter++, other--) {
                if (inrange(other, start[2], 9) && other != 3) {
                    ret += solve(idx+1, new_mask(idx, a, b, other, mask), iter);
                    ret %= 12345647;
                }
            }
        }
    }
    return dp[idx][mask][tens] = ret;
};

inline void prayGod() {
    int t; cin >> t;
    while (t--) {
        cin >> n >> l;
        sz = len(n);
        while (len(l) < sz) l = "0" + l;
        for (int i = 0;i<sz; i++) {
            for (int j = 0; j<8; j++) {
                for (int k = 0; k<3; k++) dp[i][j][k] = -1;
            }
        }
        cout << solve(0, 7, 0) << '\n';
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

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    debugDecimal(5) << time_taken << " s" << '\n';
#endif
}
