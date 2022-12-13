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

struct Hungarian {
    int n, m;
    vector<vector<int>> dist;
    vector<int> u, v, p, ans, way;
    Hungarian(int _n, int _m) : n{_n}, m{_m}, dist(n + 1, vector<int>(m + 1, iinf)), u(n + 1), v(m + 1), p(m + 1), ans(n + 1), way(m + 1) {}

    void add_edge(int from, int to, int w) {
        dist[from][to] = w;
    }

    void reset() {
        for (int i = 0; i <= n; i++) {
            u[i] = v[i] = p[i] = ans[i] = way[i] = 0;
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dist[i][j] = iinf;
            }
        }
    }

    void run() {
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int ptr = 0;
            vector<int> minv(m + 1, iinf);
            vector<bool> visited(m + 1, false);

            do {
                visited[ptr] = true;
                int ptr_match = p[ptr], delta = iinf, nxt_ptr = 0;
                for (int j = 1; j <= m; j++) {
                    if (visited[j]) continue;
                    int curr = dist[ptr_match][j] - u[ptr_match] - v[j];
                    if (curr < minv[j]) {
                        minv[j] = curr;
                        way[j] = ptr;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        nxt_ptr = j;
                    }
                }

                for (int j = 0; j <= m; j++) {
                    if (visited[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }

                ptr = nxt_ptr;
            } while (p[ptr] != 0);

            do {
                int nxt_ptr = way[ptr];
                p[ptr] = p[nxt_ptr];
                ptr = nxt_ptr;
            } while (ptr != 0);
        }
        for (int i = 1; i <= m; i++) {
            ans[p[i]] = i;
        }
    }
};

pair<vector<vector<int>>, vector<vector<int>>> construct_hexagon(int n) {
    int curr = 1;
    vector<vector<int>> row;

    for (int row_size = (n + 1) / 2; row_size < n; row_size++) {
        row.emplace_back();
        for (int j = 0; j < row_size; j++) {
            row.back().push_back(curr++);
        }
    }

    for (int row_size = n; row_size >= (n + 1) / 2; row_size--) {
        row.emplace_back();
        for (int j = 0; j < row_size; j++) {
            row.back().push_back(curr++);
        }
    }

    vector<vector<int>> graph(curr);
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < len(row[i]); j++) {
            if (j + 1 < len(row[i])) {
                graph[row[i][j]].push_back(row[i][j + 1]);
                graph[row[i][j + 1]].push_back(row[i][j]);
            }
            graph[row[i][j]].push_back(row[i + 1][j]);
            graph[row[i + 1][j]].push_back(row[i][j]);
            if (j + 1 < len(row[i + 1])) {
                graph[row[i][j]].push_back(row[i + 1][j + 1]);
                graph[row[i + 1][j + 1]].push_back(row[i][j]);
            }
        }
    }

    for (int i = n / 2; i < len(row) - 1; i++) {
        for (int j = 0; j < len(row[i]); j++) {
            if (j + 1 < len(row[i])) {
                graph[row[i][j]].push_back(row[i][j + 1]);
                graph[row[i][j + 1]].push_back(row[i][j]);
            }
            if (j < len(row[i + 1])) {
                graph[row[i][j]].push_back(row[i + 1][j]);
                graph[row[i + 1][j]].push_back(row[i][j]);
            }
            if (j - 1 >= 0) {
                graph[row[i][j]].push_back(row[i + 1][j - 1]);
                graph[row[i + 1][j - 1]].push_back(row[i][j]);
            }
        }
    }

    for (int j = 0; j < len(row.back()); j++) {
        if (j + 1 < len(row.back())) {
            graph[row.back()[j]].push_back(row.back()[j + 1]);
            graph[row.back()[j + 1]].push_back(row.back()[j]);
        }
    }

    vector<vector<int>> configs(3);
    configs.back().insert(configs.back().end(), row[n / 2].begin(), row[n / 2].end());

    int x = 0, y = 0;
    for (int i = 0; i < n / 2; i++) {
        configs[0].push_back(row[x++][y++]);
    }

    for (int i = 0; i < (n + 1) / 2; i++) {
        configs[0].push_back(row[x++][y]);
    }

    x = 0, y = len(row[0]) - 1;
    for (int i = 0; i < n / 2; i++) {
        configs[1].push_back(row[x++][y]);
    }

    for (int i = 0; i < (n + 1) / 2; i++) {
        configs[1].push_back(row[x++][y--]);
    }
    return make_pair(graph, configs);
}

void prayGod() {
    string line;
    getline(cin, line);
    int t = stoi(line);
    for (int tc = 1; tc <= t; tc++) {
        vector<int> pos, value;
        getline(cin, line);
        istringstream is(line);
        pos = vector<int>(istream_iterator<int>(is), istream_iterator<int>());

        getline(cin, line);
        istringstream is2(line);
        value = vector<int>(istream_iterator<int>(is2), istream_iterator<int>());

        int n = len(pos);
        auto [graph, configs] = construct_hexagon(n);
        int curr = len(graph);

        vector<vector<int>> dist(curr, vector<int>(curr, iinf));
        for (int i = 0; i < curr; i++) {
            deque<int> q{i};
            dist[i][i] = 0;
            while (!q.empty()) {
                int v = q.front();
                q.pop_front();
                for (auto neighbor : graph[v]) {
                    if (dist[i][neighbor] > dist[i][v] + 1) {
                        dist[i][neighbor] = dist[i][v] + 1;
                        q.push_back(neighbor);
                    }
                }
            }
        }

        int ret = iinf;

        for (const auto &config : configs) {
            Hungarian ds{n, n};
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    ds.add_edge(i + 1, j + 1, value[i] * dist[pos[i]][config[j]]);
                }
            }
            ds.run();
            int curr_ans = 0;
            for (int i = 1; i <= n; i++) {
                curr_ans += ds.dist[i][ds.ans[i]];
            }
            ret = min(ret, curr_ans);
        }

        cout << "Case #" << tc << ": " << ret << '\n';
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