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
const ll inf = 1e18;
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

struct Hungarian {
    vec<vec<ll>> c;
    vec<ll> fx, fy, d;
    vec<int> l, r, arg, trace;
    queue<int> q;
    int start, finish, n;
    Hungarian() = delete;
    Hungarian(int n1, int n2) : n(max(n1, n2)) {
        c.assign(n + 1, vec<ll>(n + 1));
        fx.assign(n + 1, 0);
        fy.assign(n + 1, 0);
        d.assign(n + 1, 0);
        l.assign(n + 1, 0);
        r.assign(n + 1, 0);
        arg.assign(n + 1, 0);
        trace.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            fy[i] = l[i] = r[i] = 0;
            for (int j = 1; j <= n; ++j) c[i][j] = inf;
        }
    }
    void add_edge(int u, int v, ll cost) {
        c[u][v] = min(c[u][v], cost);
    }
    inline long long getC(int u, int v) {
        return c[u][v] - fx[u] - fy[v];
    }
    void initBFS() {
        while (!q.empty()) q.pop();
        q.push(start);
        for (int i = 0; i <= n; ++i) trace[i] = 0;
        for (int v = 1; v <= n; ++v) {
            d[v] = getC(start, v);
            arg[v] = start;
        }
        finish = 0;
    }
    void findAugPath() {
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 1; v <= n; ++v)
                if (!trace[v]) {
                    ll w = getC(u, v);
                    if (!w) {
                        trace[v] = u;
                        if (!r[v]) {
                            finish = v;
                            return;
                        }
                        q.push(r[v]);
                    }
                    if (d[v] > w) {
                        d[v] = w;
                        arg[v] = u;
                    }
                }
        }
    }
    void subX_addY() {
        ll delta = inf;
        for (int v = 1; v <= n; ++v)
            if (trace[v] == 0 && d[v] < delta) {
                delta = d[v];
            }
        // Rotate
        fx[start] += delta;
        for (int v = 1; v <= n; ++v)
            if (trace[v]) {
                int u = r[v];
                fy[v] -= delta;
                fx[u] += delta;
            } else
                d[v] -= delta;
        for (int v = 1; v <= n; ++v)
            if (!trace[v] && !d[v]) {
                trace[v] = arg[v];
                if (!r[v]) {
                    finish = v;
                    return;
                }
                q.push(r[v]);
            }
    }
    void Enlarge() {
        do {
            int u = trace[finish];
            int nxt = l[u];
            l[u] = finish;
            r[finish] = u;
            finish = nxt;
        } while (finish);
    }
    ll minimum_matching() {
        for (int u = 1; u <= n; ++u) {
            fx[u] = c[u][1];
            for (int v = 1; v <= n; ++v) {
                fx[u] = min(fx[u], c[u][v]);
            }
        }
        for (int v = 1; v <= n; ++v) {
            fy[v] = c[1][v] - fx[1];
            for (int u = 1; u <= n; ++u) {
                fy[v] = min(fy[v], c[u][v] - fx[u]);
            }
        }
        for (int u = 1; u <= n; ++u) {
            start = u;
            initBFS();
            while (!finish) {
                findAugPath();
                if (!finish) subX_addY();
            }
            Enlarge();
        }
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (c[i][l[i]] != inf)
                ans += c[i][l[i]];
            else
                l[i] = 0;
        }
        return ans;
    }
};

void prayGod() {
    int n;
    cin >> n;
    vec<vec<pair<int, int>>> worker_gate(n);
    vec<vec<pair<int, int>>> gate_station(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pair<int, int> curr;
            cin >> curr;
            worker_gate[i].push_back(curr);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pair<int, int> curr;
            cin >> curr;
            gate_station[i].push_back(curr);
        }
    }

    ll ret = inf;
    int best_bound = -1;
    vec<int> best_left, best_right;

    for (int bound = n - 1; bound >= -1; bound--) {
        Hungarian wg(n, n), gs(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= bound; j++) {
                wg.add_edge(i + 1, j + 1, worker_gate[i][j].first);
                gs.add_edge(j + 1, i + 1, gate_station[i][j].first);
            }
            for (int j = bound + 1; j < n; j++) {
                wg.add_edge(i + 1, j + 1, worker_gate[i][j].second);
                gs.add_edge(j + 1, i + 1, gate_station[i][j].second);
            }
        }
        ll curr_ans = wg.minimum_matching() + gs.minimum_matching();
        if (curr_ans < ret) {
            ret = curr_ans;
            best_bound = bound;
            best_left = move(wg.l);
            best_right = move(gs.l);
        }
    }

    cout << ret << '\n';
    for (int i = 1; i <= n; i++) {
        cout << i << " " << best_left[i];
        cout << (best_left[i] - 1 <= best_bound ? "A" : "B") << " ";
        cout << best_right[best_left[i]] << '\n';
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