#include <bits/stdc++.h>

#include <type_traits>

using namespace std;

using ui = unsigned int;
using ll = long long;
using ld = long double;

#define null NULL
#define umap unordered_map
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

const char *INPUT_FILE = "second_flight_input.txt";
const char *OUTPUT_FILE = "output.txt";

struct Payload {
    vec<pair<int, ll>> sorted;
    vec<ll> pref;
    Payload() = default;
};

struct SegmentTree {
    vec<Payload> tree;
    int arr_size;
    SegmentTree(const vec<pair<int, ll>> &a) : tree(len(a) * 4), arr_size{len(a)} {
        for (int i = 0; i < len(a); i++) {
            add(i, a[i]);
        }
        merge(0, 0, arr_size - 1);
    }
    void merge(int idx, int curr_l, int curr_r) {
        if (curr_l == curr_r) return;
        int mid = curr_l + (curr_r - curr_l) / 2;

        merge(idx * 2 + 2, mid + 1, curr_r);
        merge(idx * 2 + 1, curr_l, mid);

        auto &[sorted, pref] = tree[idx];
        for (int i = 1; i <= 2; i++) {
            int child_idx = idx * 2 + i;
            auto &[ss, pp] = tree[idx * 2 + i];
            sorted.insert(sorted.end(), ss.begin(), ss.end());
        }
        sort(sorted.begin(), sorted.end());
        pref.resize(sorted.size());
        transform(sorted.begin(), sorted.end(), pref.begin(), [](const auto &p) { return p.second; });
        partial_sum(pref.begin(), pref.end(), pref.begin());
    }

    void add(int idx, int curr_l, int curr_r, int i, pair<int, ll> x) {
        if (curr_l == curr_r) {
            tree[idx].sorted.push_back(x);
            tree[idx].pref.push_back(x.second * 1ll);
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid) {
            add(idx * 2 + 1, curr_l, mid, i, x);
        } else {
            add(idx * 2 + 2, mid + 1, curr_r, i, x);
        }
    }

    void add(int i, pair<int, ll> x) {
        add(0, 0, arr_size - 1, i, x);
    }

    ll query(int l, int r, int bound) {
        return query(0, 0, arr_size - 1, l, r, bound);
    }

    ll eval(int idx, int bound) {
        int pos = lower_bound(
                      tree[idx].sorted.begin(),
                      tree[idx].sorted.end(),
                      make_pair(bound, ll(-1))) -
                  tree[idx].sorted.begin() - 1;
        if (pos < 0) return 0ll;
        return tree[idx].pref[pos];
    }

    ll query(int idx, int curr_l, int curr_r, int l, int r, int bound) {
        if (curr_l > curr_r || curr_r < l || r < curr_l) return 0ll;
        if (l <= curr_l && curr_r <= r) {
            return eval(idx, bound);
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        return query(idx * 2 + 1, curr_l, mid, l, r, bound) + query(idx * 2 + 2, mid + 1, curr_r, l, r, bound);
    }
};

void prayGod() {
    int n;
    cin >> n;
    vec<vec<int>> graph(n);

    int root = -1;

    vec<pair<int, ll>> employees(n);
    for (int i = 0; i < n; i++) {
        int manager;
        cin >> manager >> employees[i].first >> employees[i].second;
        if (manager == -1) {
            root = i;
        } else {
            graph[--manager].push_back(i);
        }
    }

    vec<int> tin(n), tout(n);
    int timer = 0;

    function<void(int)> establish_order = [&](int curr) {
        tin[curr] = timer++;
        for (auto &&neighbor : graph[curr]) {
            establish_order(neighbor);
        }
        tout[curr] = timer;
    };

    establish_order(root);

    vec<pair<int, ll>> employees_order(n);
    for (int i = 0; i < n; i++) {
        employees_order[tin[i]] = employees[i];
    }

    SegmentTree tree{employees_order};

    for (int i = 0; i < n; i++) {
        cout << tree.query(tin[i], tout[i] - 1, employees[i].first) << '\n';
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