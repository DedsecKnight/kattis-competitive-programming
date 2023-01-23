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

constexpr int OPEN_BRACKET = -1;
constexpr int CLOSE_BRACKET = -2;

struct SegmentTree {
    vector<ll> tree, p2;
    static constexpr ll MOD = 100000000183;

    SegmentTree(int n) : tree(4 * n, 0), p2(n + 1, 1) {
        for (int i = 1; i <= n; i++) {
            p2[i] = p2[i - 1] * 2 % MOD;
        }
    }

    void insert(int idx, int curr_l, int curr_r, int i, int v) {
        if (curr_l == curr_r) {
            tree[idx] = p2[v];
            return;
        }
        auto mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid) {
            insert(idx * 2 + 1, curr_l, mid, i, v);
        } else {
            insert(idx * 2 + 2, mid + 1, curr_r, i, v);
        }
        tree[idx] = (tree[idx * 2 + 1] + tree[idx * 2 + 2]) % MOD;
    };

    ll query(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r || curr_r < l || r < curr_l) return 0ll;
        if (l <= curr_l && curr_r <= r) return tree[idx];
        auto mid = curr_l + (curr_r - curr_l) / 2;
        auto left = query(idx * 2 + 1, curr_l, mid, l, r);
        auto right = query(idx * 2 + 2, mid + 1, curr_r, l, r);
        return (left + right) % MOD;
    }
};

void prayGod() {
    int n;
    cin >> n;
    umap<ll, int> hash_cnt;

    auto parse = [&](const string &s) {
        vector<int> ret;

        string buff = "";
        for (char c : s) {
            if (c == '(')
                ret.push_back(OPEN_BRACKET);
            else if (c == ')') {
                if (!buff.empty()) {
                    ret.push_back(stoi(buff));
                    buff = "";
                }
                ret.push_back(CLOSE_BRACKET);
            } else if (c == ',') {
                if (!buff.empty()) {
                    ret.push_back(stoi(buff));
                    buff = "";
                }
            } else {
                buff += c;
            }
        }

        return ret;
    };

    string s;
    cin >> s;
    vector<int> alice = parse(s);

    cin >> s;
    vector<int> bob = parse(s);

    SegmentTree tree{max(len(alice), len(bob))};

    auto find_group = [&](const vector<int> &a) {
        stack<int> st;

        for (int i = 0; i < len(a); i++) {
            if (a[i] == OPEN_BRACKET) {
                st.push(i);
            } else if (a[i] == CLOSE_BRACKET) {
                hash_cnt[tree.query(0, 0, len(a) - 1, st.top(), i)]++;
                st.pop();
            }
        }
    };

    for (int i = 0; i < len(alice); i++) {
        if (alice[i] != OPEN_BRACKET && alice[i] != CLOSE_BRACKET) {
            tree.insert(0, 0, len(alice) - 1, i, alice[i]);
        }
    }
    find_group(alice);

    fill(tree.tree.begin(), tree.tree.end(), 0);
    for (int i = 0; i < len(bob); i++) {
        if (bob[i] != OPEN_BRACKET && bob[i] != CLOSE_BRACKET) {
            tree.insert(0, 0, len(bob) - 1, i, bob[i]);
        }
    }
    find_group(bob);

    int ret = n;
    for (const auto &[k, v] : hash_cnt) {
        if (v > 1) ret++;
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