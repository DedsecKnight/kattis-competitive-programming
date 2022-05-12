#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
typedef long long ll;
typedef long double ld;

template <class K, class V>
using umap = unordered_map<K, V>;

#define null NULL
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
void readIdx(vector<pair<T, int>> &a, int n) {
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

struct SegmentTree {
    vec<ll> tree;
    int arr_size;
    SegmentTree(int n) {
        tree.assign(4 * n, 0);
        arr_size = n;
    };

    void update(int idx, int curr_l, int curr_r, int i, ll x) {
        if (curr_l == curr_r) {
            tree[idx] += x;
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid)
            update(idx * 2 + 1, curr_l, mid, i, x);
        else
            update(idx * 2 + 2, mid + 1, curr_r, i, x);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
    }

    void update(int i, ll x) {
        update(0, 0, arr_size - 1, i, x);
    }

    ll query(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r || curr_l > r || curr_r < l) return 0;
        if (curr_l >= l && curr_r <= r) {
            return tree[idx];
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        ll left = query(idx * 2 + 1, curr_l, mid, l, r);
        ll right = query(idx * 2 + 2, mid + 1, curr_r, l, r);
        return left + right;
    }

    ll query(int l, int r) {
        if (l > r) return 0;
        return query(0, 0, arr_size - 1, l, r);
    }

    void reset() {
        fill(tree.begin(), tree.end(), 0ll);
    }
};

void prayGod() {
    int n;
    cin >> n;

    vec<vec<int>> pos(3, vec<int>(n));
    cin >> pos;

    ll ret = 0;
    SegmentTree tree(2 * n);

    for (int f = 0; f < 3; f++) {
        for (int s = f + 1; s < 3; s++) {
            tree.reset();
            vec<int> prev(n + 1, -1);

            for (int i = 0; i < n; i++) {
                prev[pos[f][i]] = i;
            }

            for (int i = 0; i < n; i++) {
                ret += tree.query(prev[pos[s][i]] + 1, i + n - 1);
                tree.update(prev[pos[s][i]], 1);
            }
        }
    }

    cout << (n * 1ll * (n - 1) - ret) / 2 << '\n';
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