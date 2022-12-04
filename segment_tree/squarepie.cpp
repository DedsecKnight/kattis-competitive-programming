/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/squarepie
TAGS: merge sort tree, segment tree, binary search, sparse table
EXPLANATION:
- My thought process:
    + Given a rectangle, we need to find a line that will split it into 2 halves and then recursively do the same
    to the 2 halves.
    + Once we can no longer split the rectangle, we store its area and use it to report the answer
    + In worst case, time complexity of this operation will be the following recurrence relation:
        + T(N) = T(N-1) + f(n)
        + f(n) is the time complexity for finding the split line
        + This is true when the every other line is on one side of the split line
    + From that, it can be noticed that f(n) needs to be of sub-linear time complexity
    + To find an element that is bounded by 2 dimensions (x and y coordinates), we can utilize merge sort tree, which
    is basically a segment tree
    constructed from the array sorted by the first dimension and each node of the tree will contain everything within
    its respective range for 1st and sorted by 2nd dimension.
    + To make 2d-bounded queries on merge sort tree, do normal traversal by first dimension. Once we reach a node
    representing a range completely within that of first dimension, binary search by 2nd dimension to get answer.
    + Since this kind of query will yield time complexity of roughly O(log^2(n)), it definitely is a good fit for
    f(n), as worst case of our algorithm will now be roughly O(n log^2(n)), where n is # of lines segment in the
    input.
    + Another thing to notice is that this approach will not work if there exists a horizontal line and a vertical
    line intersecting each other. However, since the problem statement guarantees that this will not happen,
    we can use it to solve this problem.
- Solution sketch:
    + Categorize the lines based on whether it is vertical or horizontal.
    + Build one merge sort tree for horizontal lines and one for vertical lines.
    + Start from the rectangle that covers everything, do the following:
        + Determine if there exists a vertical line that splits the rectangle in half
        + If there is, split the rectangle using that line and recursively apply the same procedure with the 2 halves
        + If not, determine if there exists a horizontal line that splits the rectangle in half
        + If there is, split the rectangle using that line and recursively apply the same procedure with the 2 halves.
        + If not, then we can assume that our rectangle can no longer be splitted we can just store its area.
END ANNOTATION
*/
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

constexpr bool PRINT_EXEC_TIME = true;
constexpr bool EXTERNAL_INPUT = false;
constexpr bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "cases.txt";
const char *OUTPUT_FILE = "output.txt";

struct RMQ {
    vector<vector<pair<int, int>>> jmp;
    void init(const vector<tuple<int, int, int>> &V) {
        jmp.emplace_back();
        for (const auto &[didx, _, cnt] : V) jmp.back().emplace_back(didx, cnt);
        for (int pw = 1, k = 1; pw * 2 <= len(V); pw *= 2, ++k) {
            jmp.emplace_back(len(V) - pw * 2 + 1);
            for (int j = 0; j < len(jmp[k]); j++) {
                if (jmp[k - 1][j].second > jmp[k - 1][j + pw].second) {
                    jmp[k][j] = jmp[k - 1][j];
                } else {
                    jmp[k][j] = jmp[k - 1][j + pw];
                }
            }
        }
    }
    pair<int, int> query(int a, int b) {
        assert(a < b);  // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        auto l = jmp[dep][a], r = jmp[dep][b - (1 << dep)];
        if (l.second > r.second) return l;
        return r;
    }
};

struct MergeSortTree {
    vector<vector<tuple<int, int, int>>> tree;
    vector<RMQ> tree_rmq;

    MergeSortTree(int n) : tree(4 * n), tree_rmq(4 * n) {}
    void insert(int idx, int curr_l, int curr_r, int i, tuple<int, int, int> payload) {
        if (curr_l == curr_r) {
            tree[idx].push_back(payload);
            tree_rmq[idx].init(tree[idx]);
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid)
            insert(idx * 2 + 1, curr_l, mid, i, payload);
        else
            insert(idx * 2 + 2, mid + 1, curr_r, i, payload);
    }

    void build(int idx, int curr_l, int curr_r) {
        if (curr_l >= curr_r) return;
        int mid = curr_l + (curr_r - curr_l) / 2;
        build(idx * 2 + 1, curr_l, mid);
        build(idx * 2 + 2, mid + 1, curr_r);
        for (const auto &p : tree[idx * 2 + 1]) {
            tree[idx].push_back(p);
        }
        for (const auto &p : tree[idx * 2 + 2]) {
            tree[idx].push_back(p);
        }
        sort(tree[idx].begin(), tree[idx].end(), [](const auto &x, const auto &y) { return get<1>(x) < get<1>(y); });
        tree_rmq[idx].init(tree[idx]);
    }

    pair<int, int> query(int idx, int curr_l, int curr_r, int l, int r, int lb, int rb) {
        if (curr_l > curr_r || curr_r < l || r < curr_l) return {-1, -iinf};
        if (l <= curr_l && curr_r <= r) {
            int low = 0, high = len(tree[idx]) - 1, left = len(tree[idx]), right = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (get<1>(tree[idx][mid]) >= lb) {
                    left = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            low = 0, high = len(tree[idx]) - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (get<1>(tree[idx][mid]) < rb) {
                    right = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            if (left > right) return make_pair(-1, -iinf);
            return tree_rmq[idx].query(left, right + 1);
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        auto left = query(idx * 2 + 1, curr_l, mid, l, r, lb, rb);
        auto right = query(idx * 2 + 2, mid + 1, curr_r, l, r, lb, rb);
        if (left.second > right.second) return left;
        return right;
    }
};

struct Line {
    int x, y, sz;
    Line(int _x, int _y, int _sz) : x{_x}, y{_y}, sz{_sz} {}
    bool operator<(const Line &other) {
        return x < other.x;
    }
};

void prayGod() {
    int n;
    cin >> n;
    vec<tuple<int, int, int>> horizontal_lines, vertical_lines;

    int minx = iinf, maxx = -iinf, miny = iinf, maxy = -iinf;

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        minx = min({minx, x1, x2});
        maxx = max({maxx, x1, x2});
        miny = min({miny, y1, y2});
        maxy = max({maxy, y1, y2});

        if (x1 == x2) {
            vertical_lines.emplace_back(x1, min(y1, y2), abs(y2 - y1));
        } else {
            assert(y2 == y1);
            horizontal_lines.emplace_back(y1, min(x1, x2), abs(x2 - x1));
        }
    }

    sort(vertical_lines.begin(), vertical_lines.end());
    sort(horizontal_lines.begin(), horizontal_lines.end());

    MergeSortTree horizontal(len(horizontal_lines)), vertical(len(vertical_lines));
    for (int i = 0; i < len(vertical_lines); i++) {
        vertical.insert(0, 0, len(vertical_lines) - 1, i, vertical_lines[i]);
    }
    for (int i = 0; i < len(horizontal_lines); i++) {
        horizontal.insert(0, 0, len(horizontal_lines) - 1, i, horizontal_lines[i]);
    }

    horizontal.build(0, 0, len(horizontal_lines) - 1);
    vertical.build(0, 0, len(vertical_lines) - 1);

    vector<ll> all_areas;

    auto find_split_line = [&](int x1, int x2, int y1, int y2, MergeSortTree &tree, const vector<tuple<int, int, int>> &lines) {
        int low = 0, high = len(lines) - 1, l = len(lines), r = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (get<0>(lines[mid]) > x1) {
                l = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        low = 0, high = len(lines) - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (get<0>(lines[mid]) < x2) {
                r = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return tree.query(0, 0, len(lines) - 1, l, r, y1, y2);
    };

    function<void(int, int, int, int)> solve = [&](int x1, int x2, int y1, int y2) {
        auto [split_x, max_sz_x] = find_split_line(x1, x2, y1, y2, vertical, vertical_lines);
        if (max_sz_x == y2 - y1) {
            solve(x1, split_x, y1, y2);
            solve(split_x, x2, y1, y2);
            return;
        }

        auto [split_y, max_sz_y] = find_split_line(y1, y2, x1, x2, horizontal, horizontal_lines);
        if (max_sz_y == x2 - x1) {
            solve(x1, x2, y1, split_y);
            solve(x1, x2, split_y, y2);
            return;
        }

        if (max_sz_x == -iinf && max_sz_y == -iinf) {
            all_areas.push_back((y2 - y1) * 1ll * (x2 - x1));
            return;
        }
    };

    vector<ld> fractions;

    solve(minx, maxx, miny, maxy);
    ld total = accumulate(all_areas.begin(), all_areas.end(), 0.0, [](auto acc, auto curr) { return acc + ld(curr); });

    for (const auto &area : all_areas) {
        fractions.push_back(ld(area) / total);
    }

    sort(fractions.rbegin(), fractions.rend());

    for (const auto &f : fractions) {
        printDecimal(10) << f << '\n';
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