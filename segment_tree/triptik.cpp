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
constexpr bool EXTERNAL_INPUT = true;
constexpr bool EXTERNAL_OUTPUT = true;

const char *INPUT_FILE = "cases.txt";
const char *OUTPUT_FILE = "output.txt";

struct SegmentTree {
    vec<vec<int>> tree;
    int max_payload_size;
    SegmentTree(int n, int k) : tree(4 * n), max_payload_size{k} {}
    void insert(int idx, int curr_l, int curr_r, int pos, int i) {
        if (curr_l == curr_r) {
            tree[idx].push_back(i);
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (pos <= mid)
            insert(idx * 2 + 1, curr_l, mid, pos, i);
        else
            insert(idx * 2 + 2, mid + 1, curr_r, pos, i);
        merge(tree[idx], tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    void merge(vec<int> &par, const vec<int> &child1, const vec<int> &child2) {
        par.clear();
        par.insert(par.end(), child1.begin(), child1.end());
        par.insert(par.end(), child2.begin(), child2.end());
        sort(par.begin(), par.end(), greater<int>());
        while (len(par) > max_payload_size) par.pop_back();
    }
    vec<int> query(int idx, int curr_l, int curr_r, int l, int r) {
        if (l > r || curr_l > curr_r || curr_r < l || r < curr_l) {
            return {};
        }
        if (l <= curr_l && curr_r <= r) {
            return tree[idx];
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        auto left = query(idx * 2 + 1, curr_l, mid, l, r);
        auto right = query(idx * 2 + 2, mid + 1, curr_r, l, r);
        vec<int> ans;
        merge(ans, left, right);
        return ans;
    }
};

void prayGod() {
    int n, K;
    cin >> n >> K;
    vec<ld> pos(n), sorted_pos{0};
    umap<ld, int> ptoid;
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
        sorted_pos.push_back(pos[i]);
    }
    sort(sorted_pos.begin(), sorted_pos.end());
    int sz = len(sorted_pos);
    for (int i = 0; i < sz; i++) {
        ptoid[sorted_pos[i]] = i;
    }

    SegmentTree tree(sz, K);
    for (int i = 0; i < n; i++) {
        tree.insert(0, 0, sz - 1, ptoid[pos[i]], i);
    }

    vec<vec<int>> dist(sz, vec<int>(31, iinf));
    vec<ld> p2(31);
    p2[1] = 1, p2[0] = 0.5;
    for (int i = 2; i < 31; i++) {
        p2[i] = p2[i - 1] * 2;
    }

    vec<vec<vec<int>>> neighbors(sz, vec<vec<int>>(31));
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < 31; j++) {
            ld lb = -100000000.0, rb = 100000000.0;
            if (sorted_pos[i] - lb > p2[j]) {
                lb = sorted_pos[i] - p2[j];
            }

            if (sorted_pos[i] < rb - p2[j]) {
                rb = sorted_pos[i] + p2[j];
            }

            int llb = lower_bound(sorted_pos.begin(), sorted_pos.end(), lb) - sorted_pos.begin();
            int rrb = upper_bound(sorted_pos.begin(), sorted_pos.end(), rb) - sorted_pos.begin() - 1;

            neighbors[i][j] = tree.query(0, 0, sz - 1, llb, rrb);
        }
    }

    deque<pair<int, int>> q;
    q.emplace_back(ptoid[0], 1);
    dist[ptoid[0]][1] = 0;

    auto center_viewable = [&](int curr, int view_length) -> bool {
        for (auto neighbor : neighbors[curr][view_length]) {
            if (pos[neighbor] == sorted_pos[curr]) return true;
        }
        return false;
    };

    while (!q.empty()) {
        auto [curr, view_length] = q.front();
        q.pop_front();

        if (view_length - 1 >= 0 && dist[curr][view_length - 1] > dist[curr][view_length] + 1) {
            dist[curr][view_length - 1] = dist[curr][view_length] + 1;
            q.emplace_back(curr, view_length - 1);
        }
        if (view_length < 30 && dist[curr][view_length + 1] > dist[curr][view_length] + 1) {
            dist[curr][view_length + 1] = dist[curr][view_length] + 1;
            q.emplace_back(curr, view_length + 1);
        }

        for (auto neighbor : neighbors[curr][view_length]) {
            if (dist[ptoid[pos[neighbor]]][view_length] > dist[curr][view_length] + 1) {
                dist[ptoid[pos[neighbor]]][view_length] = dist[curr][view_length] + 1;
                q.emplace_back(ptoid[pos[neighbor]], view_length);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int ans = iinf;
        for (int j = 0; j < 30; j++) {
            if (center_viewable(ptoid[pos[i]], j))
                ans = min(ans, dist[ptoid[pos[i]]][j]);
        }
        if (ans == iinf)
            cout << -1 << '\n';
        else
            cout << ans << '\n';
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