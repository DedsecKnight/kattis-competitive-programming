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

struct SuffixArray {
    vector<int> sa, lcp;
    SuffixArray(const string &s, int lim = 256) {
        int n = len(s) + 1, k = 0, a, b;
        vector<int> x(begin(s), end(s) + 1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(sa.begin(), sa.end(), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(y.begin(), y.end(), n - j);
            for (int i = 0; i < n; i++) {
                if (sa[i] >= j) y[p++] = sa[i] - j;
            }
            fill(ws.begin(), ws.end(), 0);
            for (int i = 0; i < n; i++) {
                ws[x[i]]++;
            }
            for (int i = 1; i < lim; i++) {
                ws[i] += ws[i - 1];
            }
            for (int i = n; i--;) {
                sa[--ws[x[y[i]]]] = y[i];
            }
            swap(x, y), p = 1, x[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
        }
        for (int i = 1; i < n; i++) {
            rank[sa[i]] = i;
        }
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k) {
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
                ;
        }
    }
};

template <typename T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T> &V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= len(V); pw *= 2, k++) {
            jmp.emplace_back(len(V) - pw * 2 + 1);
            for (int j = 0; j < len(jmp[k]); j++) {
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
        }
    }

    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct SegmentTree {
    vector<int> tree;
    int arr_size;
    SegmentTree(int n) : tree(4 * n, iinf), arr_size{n} {}
    void update(int idx, int curr_l, int curr_r, int i, int x) {
        if (curr_l == curr_r) {
            tree[idx] = min(tree[idx], x);
            return;
        }
        auto mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid) {
            update(idx * 2 + 1, curr_l, mid, i, x);
        } else {
            update(idx * 2 + 2, mid + 1, curr_r, i, x);
        }
        tree[idx] = min(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    int query(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r || curr_r < l || r < curr_l) return iinf;
        if (l <= curr_l && curr_r <= r) return tree[idx];
        auto mid = curr_l + (curr_r - curr_l) / 2;
        auto left = query(idx * 2 + 1, curr_l, mid, l, r);
        auto right = query(idx * 2 + 2, mid + 1, curr_r, l, r);
        return min(left, right);
    }
    int query(int l, int r) { return query(0, 0, arr_size - 1, l, r); }
};

void prayGod() {
    string s;
    getline(cin, s);
    s += "$";

    for (char &c : s) {
        if (c == ' ') c = ',';
    }

    int n = len(s);
    vector<int> pos(n);

    auto [sa, lcp] = SuffixArray(s);
    RMQ<int> rmq{lcp};

    for (int i = 1; i < len(sa); i++) {
        pos[sa[i]] = i;
    }

    deque<int> st;
    vec<int> left(n, -1), right(n, -1);
    vector<int> dp(n);
    iota(dp.begin(), dp.end(), 1);

    for (int i = 2; i < len(sa); i++) {
        while (!st.empty() && sa[st.back()] >= sa[i]) st.pop_back();
        if (!st.empty()) left[sa[i]] = st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = len(sa) - 1; i >= 2; i--) {
        while (!st.empty() && sa[st.back()] >= sa[i]) st.pop_back();
        if (!st.empty()) right[sa[i]] = st.back();
        st.push_back(i);
    }

    vec<int> bound(n);

    for (int i = 0; i < n; i++) {
        if (left[i] != -1) bound[i] = max(bound[i], rmq.query(left[i] + 1, pos[i] + 1));
        if (right[i] != -1) bound[i] = max(bound[i], rmq.query(pos[i] + 1, right[i] + 1));
    }

    SegmentTree tree(2 * n);

    for (int i = 1; i < n; i++) {
        dp[i] = min({dp[i], dp[i - 1] + 1, tree.query(i + 1, 2 * n - 1) + 3});
        if (i - 1 >= 0) {
            tree.update(0, 0, 2 * n - 1, i - 1 + bound[i - 1], (i - 2 >= 0 ? dp[i - 2] : 0));
        }
    }

    cout << dp[n - 2] << '\n';
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