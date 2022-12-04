#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

const int iinf = 0x3f3f3f3f;
const ll inf = 1000000000000000010;
const ll mod = 1e9 + 7;

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

template <class T1, class T2, class T3>
void printTuple(const tuple<T1, T2, T3> &t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) { return out << p.first << " " << p.second; }
template <class T>
ostream &operator<<(ostream &out, const vector<T> &arr) {
    for (const T &a : arr) out << a << " ";
    return out;
}
template <class T>
ostream &operator<<(ostream &out, const vector<vector<T>> &grid) {
    for (const vector<T> &row : grid) out << row << '\n';
    return out;
}
template <class T>
istream &operator>>(istream &in, vector<T> &arr) {
    for (T &a : arr) in >> a;
    return in;
}
template <class T>
void r(vector<pair<T, int>> &a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
}
template <class T1, class T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
    in >> a.first >> a.second;
    return in;
}

// Error handling for out of bounds
template <class T>
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

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "cases.txt";
const char *OUTPUT_FILE = "output.txt";

constexpr int MAXN = 1e6 + 1;

template <class T>
struct SegmentTree {
    T base_val;
    int arr_size;
    vector<T> tree, lazy;

    SegmentTree(int n, T base) {
        base_val = base, arr_size = n;
        int size = 1;
        while (size < n) size *= 2;
        size = 2 * size + 1;
        tree.assign(size, 0);
        lazy.assign(size, 0);
    };

    T eval(T a, T b) { return max(a, b); }

    void propagate(int idx, int curr_l, int curr_r) {
        if (lazy[idx]) {
            tree[idx] += lazy[idx];

            if (curr_l != curr_r) {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }

            lazy[idx] = 0;
        }
    }

    void update(int idx, int curr_l, int curr_r, int l, int r, T val) {
        if (curr_l > curr_r) return;

        propagate(idx, curr_l, curr_r);

        if (curr_r < l || curr_l > r) return;

        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) {
            tree[idx] += val;
            if (2 * idx + 1 < len(lazy)) lazy[2 * idx + 1] += val;
            if (2 * idx + 2 < len(lazy)) lazy[2 * idx + 2] += val;
            return;
        }

        int mid = curr_l + (curr_r - curr_l) / 2;
        update(idx * 2 + 1, curr_l, mid, l, r, val);
        update(idx * 2 + 2, mid + 1, curr_r, l, r, val);
        tree[idx] = eval(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    T query(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r) return base_val;

        propagate(idx, curr_l, curr_r);

        if (curr_r < l || curr_l > r) return base_val;

        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) return tree[idx];

        int mid = curr_l + (curr_r - curr_l) / 2;
        T left = query(idx * 2 + 1, curr_l, mid, l, r), right = query(idx * 2 + 2, mid + 1, curr_r, l, r);
        return eval(left, right);
    }

    void update(int l, int r, T val) { update(0, 0, arr_size - 1, l, r, val); }
    T query(int l, int r) { return query(0, 0, arr_size - 1, l, r); }
};

void prayGod() {
    int n, c;
    cin >> n >> c;
    vec<int> a(n);
    cin >> a;
    vec<int> sorted_idx(n), map_sorted(n);
    iota(sorted_idx.begin(), sorted_idx.end(), 0);
    sort(sorted_idx.begin(), sorted_idx.end(), [&](const int x, const int y) {
        return a[x] < a[y];
    });
    for (int i = 0; i < n; i++) {
        map_sorted[sorted_idx[i]] = i;
    }

    SegmentTree<ll> tree1(n, -iinf), tree2(n, -iinf);
    vec<int> ret(n, 0);

    tree1.update(0, n - 1, -iinf);
    tree2.update(0, n - 1, -iinf);

    for (int i = 0; i < n; i++) {
        int best = max(tree1.query(0, map_sorted[i] - 1) + a[i], tree2.query(map_sorted[i] + 1, n - 1) - a[i]);
        ret[i] = max(ret[i], best);

        tree1.update(map_sorted[i], map_sorted[i], iinf + i * c - a[i]);
        tree2.update(map_sorted[i], map_sorted[i], iinf + i * c + a[i]);

        tree1.update(0, n - 1, -c);
        tree2.update(0, n - 1, -c);
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
