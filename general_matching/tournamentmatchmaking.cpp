#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

using ui = unsigned int;
using ll = int64_t;
using ull = uint64_t;
using ld = long double;

#define len(a) static_cast<int>((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

static constexpr const int iinf = 0x3f3f3f3f;
static constexpr const ll inf = 1'000'000'000'000'000;
static constexpr const ll mod = 1e9 + 7;

#define var(args...)                           \
    {                                          \
        string _s = #args;                     \
        stringstream _ss;                      \
        string _ccurr = "";                    \
        for (int zz = 0; zz < len(_s); zz++) { \
            if (_s[zz] == ' ')                 \
                continue;                      \
            if (_s[zz] == ',') {               \
                _ss << ' ' + _ccurr;           \
                _ccurr = "";                   \
            } else {                           \
                _ccurr += _s[zz];              \
            }                                  \
        }                                      \
        _ss << ' ' + _ccurr;                   \
        istream_iterator<string> _it(_ss);     \
        vars(_it, args);                       \
    }
#define debugDecimal(d) cerr << setprecision(d) << fixed

void vars(istream_iterator<string> it) {
    cerr << '\n';
}
template <typename T, typename... Args>
void vars(istream_iterator<string> it, T a, Args... args) {
    cerr << " [" << *it << ": " << a << "] ";
    vars(++it, args...);
}

#define printVerdict(verdict) cout << (verdict ? "YES" : "NO") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define printCase(_) cout << "Case #" << (_) << ": "

template <typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p) {
    return out << p.first << " " << p.second;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
    for (const T& a : arr)
        out << a << " ";
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& grid) {
    for (const vector<T>& row : grid)
        out << row << '\n';
    return out;
}
template <typename T>
istream& operator>>(istream& in, vector<T>& arr) {
    for (T& a : arr)
        in >> a;
    return in;
}
template <typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) {
    in >> a.first >> a.second;
    return in;
}

template <typename Fun>
class y_combinator_result {
    Fun fun_;

   public:
    template <typename T>
    explicit y_combinator_result(T&& fun) : fun_{std::forward<T>(fun)} {}

    template <typename... ArgTs>
    decltype(auto) operator()(ArgTs&&... args) {
        return fun_(std::ref(*this), std::forward<ArgTs>(args)...);
    }
};

template <typename Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

bool dfs(int a, int L, vector<vector<int>>& g, vector<int>& btoa,
         vector<int>& A, vector<int>& B) {
    if (A[a] != L)
        return 0;
    A[a] = -1;
    for (int b : g[a])
        if (B[b] == L + 1) {
            B[b] = 0;
            if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
                return btoa[b] = a, 1;
        }
    return 0;
}

int hopcroftKarp(vector<vector<int>>& g, vector<int>& btoa) {
    int res = 0;
    vector<int> A(g.size()), B(btoa.size()), cur, next;
    for (;;) {
        fill(begin(A), end(A), 0);
        fill(begin(B), end(B), 0);
        /// Find the starting nodes for BFS (i.e. layer 0).
        cur.clear();
        for (int a : btoa)
            if (a != -1)
                A[a] = -1;
        for (int a = 0; a < len(g); a++)
            if (A[a] == 0)
                cur.push_back(a);
        /// Find all layers using bfs.
        for (int lay = 1;; lay++) {
            bool islast = 0;
            next.clear();
            for (int a : cur)
                for (int b : g[a]) {
                    if (btoa[b] == -1) {
                        B[b] = lay;
                        islast = 1;
                    } else if (btoa[b] != a && !B[b]) {
                        B[b] = lay;
                        next.push_back(btoa[b]);
                    }
                }
            if (islast)
                break;
            if (next.empty())
                return res;
            for (int a : next)
                A[a] = lay;
            cur.swap(next);
        }
        /// Use DFS to scan for augmenting paths.
        for (int a = 0; a < len(g); a++)
            res += dfs(a, 0, g, btoa, A, B);
    }
}

struct blossom {
    int n, m;
    vector<int> mate;
    vector<vector<int>> b;
    vector<int> p, d, bl;
    vector<vector<int>> g;
    blossom(int n) : n(n) {
        m = n + n / 2;
        mate.assign(n, -1);
        b.resize(m);
        p.resize(m);
        d.resize(m);
        bl.resize(m);
        g.assign(m, vector<int>(m, -1));
    }
    void add_edge(int u, int v) {
        g[u][v] = u;
        g[v][u] = v;
    }
    void match(int u, int v) {
        g[u][v] = g[v][u] = -1;
        mate[u] = v;
        mate[v] = u;
    }
    vector<int> trace(int x) {
        vector<int> vx;
        while (true) {
            while (bl[x] != x)
                x = bl[x];
            if (!vx.empty() && vx.back() == x)
                break;
            vx.push_back(x);
            x = p[x];
        }
        return vx;
    }
    void contract(int c, int x, int y, vector<int>& vx, vector<int>& vy) {
        b[c].clear();
        int r = vx.back();
        while (!vx.empty() && !vy.empty() && vx.back() == vy.back()) {
            r = vx.back();
            vx.pop_back();
            vy.pop_back();
        }
        b[c].push_back(r);
        b[c].insert(b[c].end(), vx.rbegin(), vx.rend());
        b[c].insert(b[c].end(), vy.begin(), vy.end());
        for (int i = 0; i <= c; i++) {
            g[c][i] = g[i][c] = -1;
        }
        for (int z : b[c]) {
            bl[z] = c;
            for (int i = 0; i < c; i++) {
                if (g[z][i] != -1) {
                    g[c][i] = z;
                    g[i][c] = g[i][z];
                }
            }
        }
    }
    vector<int> lift(vector<int>& vx) {
        vector<int> A;
        while (vx.size() >= 2) {
            int z = vx.back();
            vx.pop_back();
            if (z < n) {
                A.push_back(z);
                continue;
            }
            int w = vx.back();
            int i =
                (A.size() % 2 == 0
                     ? find(b[z].begin(), b[z].end(), g[z][w]) - b[z].begin()
                     : 0);
            int j = (A.size() % 2 == 1
                         ? find(b[z].begin(), b[z].end(), g[z][A.back()]) -
                               b[z].begin()
                         : 0);
            int k = b[z].size();
            int dif = (A.size() % 2 == 0 ? i % 2 == 1 : j % 2 == 0) ? 1 : k - 1;
            while (i != j) {
                vx.push_back(b[z][i]);
                i = (i + dif) % k;
            }
            vx.push_back(b[z][i]);
        }
        return A;
    }
    int solve() {
        for (int ans = 0;; ans++) {
            fill(d.begin(), d.end(), 0);
            queue<int> Q;
            for (int i = 0; i < m; i++)
                bl[i] = i;
            for (int i = 0; i < n; i++) {
                if (mate[i] == -1) {
                    Q.push(i);
                    p[i] = i;
                    d[i] = 1;
                }
            }
            int c = n;
            bool aug = false;
            while (!Q.empty() && !aug) {
                int x = Q.front();
                Q.pop();
                if (bl[x] != x)
                    continue;
                for (int y = 0; y < c; y++) {
                    if (bl[y] == y && g[x][y] != -1) {
                        if (d[y] == 0) {
                            p[y] = x;
                            d[y] = 2;
                            p[mate[y]] = y;
                            d[mate[y]] = 1;
                            Q.push(mate[y]);
                        } else if (d[y] == 1) {
                            vector<int> vx = trace(x);
                            vector<int> vy = trace(y);
                            if (vx.back() == vy.back()) {
                                contract(c, x, y, vx, vy);
                                Q.push(c);
                                p[c] = p[b[c][0]];
                                d[c] = 1;
                                c++;
                            } else {
                                aug = true;
                                vx.insert(vx.begin(), y);
                                vy.insert(vy.begin(), x);
                                vector<int> A = lift(vx);
                                vector<int> B = lift(vy);
                                A.insert(A.end(), B.rbegin(), B.rend());
                                for (int i = 0; i < (int)A.size(); i += 2) {
                                    match(A[i], A[i + 1]);
                                    if (i + 2 < (int)A.size())
                                        add_edge(A[i + 1], A[i + 2]);
                                }
                            }
                            break;
                        }
                    }
                }
            }
            if (!aug)
                return ans;
        }
    }
};

inline void prayGod() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> groups(n);
    for (int i = 0; i < n; i++) {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++) {
            groups[i].emplace_back();
            cin >> groups[i].back().first >> groups[i].back().second;
            groups[i].back().first--, groups[i].back().second--;
        }
    }
    blossom b{n};
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (len(groups[i]) + len(groups[j]) == 15) {
                vector<vector<int>> g;
                g.reserve(15);
                vector<int> btoa(15, -1);
                for (auto elem : groups[i]) {
                    g.push_back(vector<int>{elem.first, elem.second});
                }
                for (auto elem : groups[j]) {
                    g.push_back({elem.first, elem.second});
                }
                if (hopcroftKarp(g, btoa) == 15) {
                    b.add_edge(i, j);
                }
            }
        }
    }
    std::cout << b.solve() << '\n';
}

int main() {
#ifdef LLOCAL
    clock_t start = clock();
#endif
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    prayGod();
#ifdef LLOCAL
    clock_t end = clock();

    double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    debugDecimal(5) << time_taken << " s" << '\n';
#endif
}
