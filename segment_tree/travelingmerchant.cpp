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

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

template <class T>
class SegmentTree {
   public:
    SegmentTree(int n, T b, function<T(T, T)> &&f) {
        arr_sz = n;
        base = b;
        eval = f;
        int sz = 1;
        while (sz < n) {
            sz *= 2;
        }
        tree.assign(sz * 2 + 1, T{});
    }
    void set(int i, T x) {
        set(0, 0, arr_sz - 1, i, x);
    }
    T query(int l, int r) {
        return query(0, 0, arr_sz - 1, l, r);
    }

   private:
    vec<T> tree;
    int arr_sz;
    function<T(T, T)> eval;
    T base;

    void set(int curr_idx, int curr_l, int curr_r, int i, T x) {
        assert(curr_l <= curr_r);
        if (curr_l == curr_r) {
            tree[curr_idx] = x;
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid)
            set(curr_idx * 2 + 1, curr_l, mid, i, x);
        else
            set(curr_idx * 2 + 2, mid + 1, curr_r, i, x);
        tree[curr_idx] = eval(tree[curr_idx * 2 + 1], tree[curr_idx * 2 + 2]);
    }

    T query(int curr_idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r || curr_l > r || curr_r < l) return base;
        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) return tree[curr_idx];
        int mid = curr_l + (curr_r - curr_l) / 2;
        T left = query(curr_idx * 2 + 1, curr_l, mid, l, r);
        T right = query(curr_idx * 2 + 2, mid + 1, curr_r, l, r);
        return eval(left, right);
    }
};

struct Payload {
    int max_val, min_val, sol;
    Payload() : max_val{-iinf}, min_val{iinf}, sol{0} {};
    Payload(int maxv, int minv, int s) : max_val{maxv}, min_val{minv}, sol{s} {}
    Payload operator+(const Payload &other) {
        if (this->max_val == -iinf) return {other.max_val, other.min_val, other.sol};
        if (other.max_val == -iinf) return {max_val, min_val, sol};
        int delta = max(other.max_val - min_val, 0);
        int global_solution = max({sol, other.sol, delta});
        int new_max = max(max_val, other.max_val);
        int new_min = min(min_val, other.min_val);
        return {new_max, new_min, global_solution};
    }
    friend ostream &operator<<(ostream &out, const Payload &p) {
        return out << p.max_val << " " << p.min_val << " " << p.sol;
    }
};

struct Day {
    int v, d;
    Day() = default;
    friend istream &operator>>(istream &in, Day &d) {
        return in >> d.v >> d.d;
    }
};

const int dx[] = {0, 1, 2, 3, 2, 1, 0};

void prayGod() {
    int n;
    cin >> n;

    auto merge_function = [](Payload a, Payload b) {
        return a + b;
    };

    vec<SegmentTree<Payload>> east_tree(7, SegmentTree<Payload>(n, {-iinf, iinf, 0}, merge_function));
    vec<SegmentTree<Payload>> west_tree(7, SegmentTree<Payload>(n, {-iinf, iinf, 0}, merge_function));

    vec<Day> days(n);
    cin >> days;

    for (int start_day = 0; start_day < 7; start_day++) {
        for (int i = 0; i < n; i++) {
            int curr_cost = days[i].v + days[i].d * (dx[(start_day + i % 7) % 7]);
            east_tree[start_day].set(i, {curr_cost, curr_cost, 0});
        }
    }

    for (int start_day = 0; start_day < 7; start_day++) {
        for (int i = n - 1, ptr = 0; i >= 0; i--, ptr++) {
            int curr_cost = days[i].v + days[i].d * (dx[(start_day + ptr % 7) % 7]);
            west_tree[start_day].set(ptr, {curr_cost, curr_cost, 0});
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int s, t;
        cin >> s >> t;
        if (s < t) {
            int pos = (0 - s + 1 + 7 * 1000000) % 7;
            Payload p = east_tree[pos].query(s - 1, t - 1);
            cout << max(p.sol, 0) << '\n';

        } else {
            int pos = (0 - n + s + 7 * 1000000) % 7;
            Payload p = west_tree[pos].query(n - s, n - t);
            cout << max(p.sol, 0) << '\n';
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
