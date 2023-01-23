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

template <class T>
struct SegmentTreeSSum {
    vector<T> tree, pref, suff, sum;
    SegmentTreeSSum(int n) : tree(4 * n), pref(4 * n), suff(4 * n), sum(4 * n) {}
    void set(int idx, int curr_l, int curr_r, int i, T x) {
        assert(curr_l <= curr_r);
        if (curr_l == curr_r) {
            sum[idx] = pref[idx] = suff[idx] = x;
            tree[idx] = max(x, T{});
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid) {
            set(idx * 2 + 1, curr_l, mid, i, x);
        } else {
            set(idx * 2 + 2, mid + 1, curr_r, i, x);
        }
        pref[idx] = max(pref[idx * 2 + 1], sum[idx * 2 + 1] + pref[idx * 2 + 2]);
        suff[idx] = max(suff[idx * 2 + 2], suff[idx * 2 + 1] + sum[idx * 2 + 2]);
        sum[idx] = sum[idx * 2 + 1] + sum[idx * 2 + 2];
        tree[idx] = max({tree[idx * 2 + 1], tree[idx * 2 + 2], pref[idx * 2 + 2] + suff[idx * 2 + 1]});
    }

    tuple<T, T, T, T> query(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r || r < curr_l || curr_r < l) return make_tuple(0, 0, 0, 0);
        if (l <= curr_l && curr_r <= r) {
            return make_tuple(tree[idx], pref[idx], suff[idx], sum[idx]);
        }
        auto mid = curr_l + (curr_r - curr_l) / 2;
        auto [a1, p1, s1, t1] = query(idx * 2 + 1, curr_l, mid, l, r);
        auto [a2, p2, s2, t2] = query(idx * 2 + 2, mid + 1, curr_r, l, r);
        return make_tuple(
            max({a1, a2, s1 + p2}),
            max(p1, t1 + p2),
            max(s2, t2 + s1),
            t1 + t2);
    }
};

template <class T>
struct BIT {
    vector<T> tree;
    BIT(int n) {
        tree.assign(n + 1, 0);
    }
    void update(int idx, T val) {
        idx++;
        while (idx < len(tree)) {
            tree[idx] += val;
            idx += idx & (-idx);
        }
    }

    T query(int idx) {
        idx++;
        T ret = 0;
        while (idx > 0) {
            ret += tree[idx];
            idx -= idx & (-idx);
        }
        return ret;
    }
};

void prayGod() {
    int n, q;
    cin >> n >> q;

    vector<ll> h(n + 1);
    cin >> h;

    SegmentTreeSSum<ll> fun_factor(n);
    BIT<ll> pref(n + 1);

    for (int i = 0; i <= n; i++) {
        pref.update(i, h[i]);
    }

    for (int i = 0; i < n; i++) {
        auto curr_cost = h[i] - h[i + 1];
        curr_cost *= curr_cost;
        if (h[i] < h[i + 1]) curr_cost = -curr_cost;
        fun_factor.set(0, 0, n - 1, i, curr_cost);
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int i;
            ll v;
            cin >> i >> v;
            if (i - 1 >= 0) {
                auto new_fun = h[i - 1] - v;
                new_fun *= new_fun;
                if (h[i - 1] < v) new_fun = -new_fun;
                fun_factor.set(0, 0, n - 1, i - 1, new_fun);
            }
            if (i + 1 <= n) {
                auto new_fun = v - h[i + 1];
                new_fun *= new_fun;
                if (v < h[i + 1]) new_fun = -new_fun;
                fun_factor.set(0, 0, n - 1, i, new_fun);
            }
            pref.update(i, v - h[i]);
            h[i] = v;
        } else {
            int x;
            ll k;
            cin >> x >> k;

            int low = x + 1, high = n, best = x;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                auto cost = h[x] - 2 * pref.query(x) + 2 * pref.query(mid) - h[mid];
                if (cost <= k) {
                    best = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            cout << get<0>(fun_factor.query(0, 0, n - 1, 0, best - 1)) << '\n';
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