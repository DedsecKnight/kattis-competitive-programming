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
#define PI 3.14159265

const int iinf = 0x3f3f3f3f;
const ll inf = 1e18;
const ll mod = 1e9 + 7;

#ifndef ONLINE_JUDGE
#define var(args...)                             \
    {                                            \
        string _s = #args;                       \
        replace(_s.begin(), _s.end(), ',', ' '); \
        stringstream _ss(_s);                    \
        istream_iterator<string> _it(_ss);       \
        vars(_it, args);                         \
    }
#else
#define var(args...) false
#endif

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
void printPair(const pair<T1, T2> &p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(const vector<T> &arr) {
    for (int i = 0; i < len(arr); i++) {
        cout << arr[i] << " ";
    }
    cout << '\n';
}
template <class T>
void printGrid(const vector<vector<T>> &grid) {
    for (int i = 0; i < len(grid); i++) {
        for (int j = 0; j < len(grid[i]); j++) {
            cout << grid[i][j] << " ";
        }
        cout << '\n';
    }
}

template <class T>
void read(vector<T> &a, int n) {
    for (int i = 0; i < n; i++)
        cin >> a[i];
}
template <class T>
void readIdx(vector<pair<T, int>> &a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
}
template <class T1, class T2>
void readPair(pair<T1, T2> &a) { cin >> a.first >> a.second; }

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

struct MinQueryObj {
    static constexpr pair<int, int> init = {iinf, -1};
    pair<int, int> first_min, second_min;
    int cnt_fmin;
    MinQueryObj() {
        first_min = second_min = {iinf, -1};
        cnt_fmin = 0;
    }
    MinQueryObj(pair<int, int> fmin, pair<int, int> smin, int cnt) {
        first_min = fmin;
        second_min = smin;
        cnt_fmin = cnt;
    }
    MinQueryObj operator+(const MinQueryObj &other) {
        MinQueryObj ret;
        if (first_min.first < other.first_min.first) {
            ret.first_min = first_min;
            ret.second_min = min(other.first_min, second_min);
            ret.cnt_fmin = cnt_fmin;
        } else if (first_min.first > other.first_min.first) {
            ret.first_min = other.first_min;
            ret.second_min = min(first_min, other.second_min);
            ret.cnt_fmin = other.cnt_fmin;
        } else {
            ret.first_min = first_min;
            ret.second_min = min(other.second_min, second_min);
            ret.cnt_fmin = cnt_fmin + other.cnt_fmin;
        }
        return ret;
    }
};

struct MaxQueryObj {
    static constexpr pair<int, int> init = {-iinf, -1};
    pair<int, int> first_max, second_max;
    int cnt_fmax;
    MaxQueryObj() {
        first_max = second_max = {-iinf, -1};
        cnt_fmax = 0;
    }
    MaxQueryObj(pair<int, int> fmax, pair<int, int> smax, int cnt) {
        first_max = fmax;
        second_max = smax;
        cnt_fmax = cnt;
    }
    MaxQueryObj operator+(const MaxQueryObj &other) {
        MaxQueryObj ret;
        if (first_max.first > other.first_max.first) {
            ret.first_max = first_max;
            ret.second_max = max(other.first_max, second_max);
            ret.cnt_fmax = cnt_fmax;
        } else if (first_max.first < other.first_max.first) {
            ret.first_max = other.first_max;
            ret.second_max = max(first_max, other.second_max);
            ret.cnt_fmax = other.cnt_fmax;
        } else {
            ret.first_max = first_max;
            ret.second_max = max(other.second_max, second_max);
            ret.cnt_fmax = cnt_fmax + other.cnt_fmax;
        }
        return ret;
    }
};

template <class T>
struct SegmentTree {
    int arr_size;
    vector<T> tree;
    pair<int, int> base;
    SegmentTree(int n) {
        arr_size = n;
        base = T::init;
        int sz = 1;
        while (sz < n) sz *= 2;
        sz = 2 * sz + 1;
        tree.resize(sz);
    }
    void set(int idx, int curr_l, int curr_r, int i, int x) {
        if (curr_l == curr_r) {
            tree[idx] = T(make_pair(x, i), base, 1);
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;

        if (i <= mid)
            set(idx * 2 + 1, curr_l, mid, i, x);
        else
            set(idx * 2 + 2, mid + 1, curr_r, i, x);

        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
    }

    T query(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r || curr_r < l || curr_l > r) return T(base, base, 0);
        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) return tree[idx];

        int mid = curr_l + (curr_r - curr_l) / 2;

        T left = query(idx * 2 + 1, curr_l, mid, l, r);
        T right = query(idx * 2 + 2, mid + 1, curr_r, l, r);

        return left + right;
    }

    void set(int i, int x) {
        set(0, 0, arr_size - 1, i, x);
    }
    T query(int l, int r) {
        return query(0, 0, arr_size - 1, l, r);
    }
};

void prayGod() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> houses(n);
    for (int i = 0; i < n; i++) readPair(houses[i]);

    SegmentTree<MaxQueryObj> max_xtree(n), max_ytree(n);
    SegmentTree<MinQueryObj> min_xtree(n), min_ytree(n);

    for (int i = 0; i < n; i++) {
        max_xtree.set(i, houses[i].first);
        min_xtree.set(i, houses[i].first);

        max_ytree.set(i, houses[i].second);
        min_ytree.set(i, houses[i].second);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        MaxQueryObj max_x = max_xtree.query(--l, --r);
        MinQueryObj min_x = min_xtree.query(l, r);

        MaxQueryObj max_y = max_ytree.query(l, r);
        MinQueryObj min_y = min_ytree.query(l, r);

        int left = min_x.first_min.first, right = max_x.first_max.first;
        int up = max_y.first_max.first, down = min_y.first_min.first;

        int curr_best = max(right - left, up - down);

        function<void(int)> check_horizontal = [&](int idx) {
            if (houses[idx].second == up && max_y.cnt_fmax <= 1)
                up = max_y.second_max.first;
            else if (houses[idx].second == down && min_y.cnt_fmin <= 1)
                down = min_y.second_min.first;
            curr_best = min(curr_best, max(right - left, up - down));
            up = max_y.first_max.first, down = min_y.first_min.first;
        };

        function<void(int)> check_vertical = [&](int idx) {
            if (houses[idx].first == left && min_x.cnt_fmin <= 1)
                left = min_x.second_min.first;
            else if (houses[idx].first == right && max_x.cnt_fmax <= 1)
                right = max_x.second_max.first;
            curr_best = min(curr_best, max(right - left, up - down));
            left = min_x.first_min.first, right = max_x.first_max.first;
        };

        if (min_x.cnt_fmin <= 1) {
            left = min_x.second_min.first;
            check_horizontal(min_x.first_min.second);
            left = min_x.first_min.first;
        }
        if (max_x.cnt_fmax <= 1) {
            right = max_x.second_max.first;
            check_horizontal(max_x.first_max.second);
            right = max_x.first_max.first;
        }
        if (min_y.cnt_fmin <= 1) {
            down = min_y.second_min.first;
            check_vertical(min_y.first_min.second);
            down = min_y.first_min.first;
        }
        if (max_y.cnt_fmax <= 1) {
            up = max_y.second_max.first;
            check_vertical(max_y.first_max.second);
            up = max_y.first_max.first;
        }

        cout << curr_best << '\n';
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