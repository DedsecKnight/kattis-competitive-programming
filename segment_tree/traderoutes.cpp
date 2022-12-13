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

struct SegmentTree {
    vector<pair<int, int>> tree;
    vector<int> cnt;
    SegmentTree(int n) : tree(4 * n), cnt(4 * n, 0) {}

    void insert(int idx, int curr_l, int curr_r, int i, int x) {
        if (curr_l == curr_r) {
            tree[idx] = make_pair(x, i);
            cnt[idx]++;
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid) {
            insert(idx * 2 + 1, curr_l, mid, i, x);
        } else {
            insert(idx * 2 + 2, mid + 1, curr_r, i, x);
        }
        tree[idx] = min(tree[idx * 2 + 1], tree[idx * 2 + 2]);
        cnt[idx] = cnt[idx * 2 + 1] + cnt[idx * 2 + 2];
    }

    int count(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r || r < curr_l || curr_r < l) {
            return 0;
        }
        if (l <= curr_l && curr_r <= r) {
            return cnt[idx];
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        auto left = count(idx * 2 + 1, curr_l, mid, l, r);
        auto right = count(idx * 2 + 2, mid + 1, curr_r, l, r);
        return left + right;
    }

    pair<int, int> find_min(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r || r < curr_l || curr_r < l) {
            return make_pair(iinf, -1);
        }
        if (l <= curr_l && curr_r <= r) {
            return tree[idx];
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        auto left = find_min(idx * 2 + 1, curr_l, mid, l, r);
        auto right = find_min(idx * 2 + 2, mid + 1, curr_r, l, r);
        return min(left, right);
    }

    void remove_at(int idx, int curr_l, int curr_r, pair<int, int> payload) {
        if (curr_l == curr_r) {
            tree[idx] = make_pair(iinf, -1);
            cnt[idx]--;
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (payload.second <= mid) {
            remove_at(idx * 2 + 1, curr_l, mid, payload);
        } else {
            remove_at(idx * 2 + 2, mid + 1, curr_r, payload);
        }
        tree[idx] = min(tree[idx * 2 + 1], tree[idx * 2 + 2]);
        cnt[idx] = cnt[idx * 2 + 1] + cnt[idx * 2 + 2];
    }
};

void prayGod() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    vector<int> indegree(n), p(n, -1);

    for (int i = 1; i < n; i++) {
        cin >> p[i];
        graph[i].push_back(--p[i]);
        graph[p[i]].push_back(i);
        indegree[p[i]]++;
    }

    vector<int> b(n), v(n), tin(n), tout(n);
    cin >> b >> v;

    int timer = 0;
    function<void(int)> dfs = [&](int curr) {
        tin[curr] = timer++;
        for (const auto &neighbor : graph[curr]) {
            if (neighbor == p[curr]) continue;
            dfs(neighbor);
        }
        tout[curr] = timer;
    };

    dfs(0);

    SegmentTree tree(n);
    for (int i = 0; i < n; i++) {
        tree.insert(0, 0, n - 1, tin[i], v[i]);
    }

    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        auto iter = max(tree.count(0, 0, n - 1, tin[curr], tout[curr] - 1) - b[curr], 0);
        while (iter--) {
            auto payload = tree.find_min(0, 0, n - 1, tin[curr], tout[curr] - 1);
            if (payload.second == -1) break;
            tree.remove_at(0, 0, n - 1, payload);
        }
        if (p[curr] == -1) continue;
        if (--indegree[p[curr]] == 0) q.push(p[curr]);
    }

    ll total = 0;
    vector<int> ret;

    for (int i = 0; i < n; i++) {
        auto [vv, pos] = tree.find_min(0, 0, n - 1, tin[i], tin[i]);
        if (pos == -1) continue;
        total += vv;
        ret.push_back(i + 1);
    }

    cout << total << '\n';
    cout << len(ret) << " " << ret << '\n';
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