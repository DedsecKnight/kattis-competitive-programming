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

#define var(args...)                           \
    {                                          \
        string _s = #args;                     \
        stringstream _ss;                      \
        string curr = "";                      \
        for (int zz = 0; zz < len(_s); zz++) { \
            if (_s[zz] == ' ') continue;       \
            if (_s[zz] == ',') {               \
                _ss << ' ' + curr;             \
                curr = "";                     \
            } else                             \
                curr += _s[zz];                \
        }                                      \
        _ss << ' ' + curr;                     \
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

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

const int nax = 1e5 + 10;

struct TramLine {
    int u, v;
    ll t0, p, d;
    friend istream &operator>>(istream &in, TramLine &line) {
        in >> line.u >> line.v >> line.t0 >> line.p >> line.d;
        return in;
    };
    TramLine() : u(-1), v(-1), t0(-1), p(-1), d(-1){};
    ll operator()(ll di) {
        if (di <= t0) return 0;
        return (di - t0 + p - 1) / p;
    }
};

void prayGod() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<TramLine> lines(m);
    cin >> lines;

    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        graph[lines[i].u].emplace_back(lines[i].v, i);
    }

    function<bool(int)> possible = [&](int mid) {
        vector<ll> dist(n, inf);
        dist[0] = mid;
        auto comp = [&](int a, int b) {
            if (dist[a] != dist[b]) return dist[a] < dist[b];
            return a < b;
        };
        set<int, decltype(comp)> q(comp);
        q.insert(0);

        while (!q.empty()) {
            int curr = *q.begin();
            q.erase(q.begin());
            for (pair<int, int> p : graph[curr]) {
                int neighbor = p.first, idx = p.second;
                ll depart_time = lines[idx].t0 + lines[idx](dist[curr]) * lines[idx].p;
                ll arrival_time = depart_time + lines[idx].d;

                if (arrival_time > s) continue;
                if (dist[neighbor] > depart_time + lines[idx].d) {
                    q.erase(neighbor);
                    dist[neighbor] = depart_time + lines[idx].d;
                    q.insert(neighbor);
                }
            }
        }

        return dist.back() <= s;
    };

    int low = 0, high = s, best = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (possible(mid)) {
            best = mid;
            low = mid + 1;
        } else
            high = mid - 1;
    }
    if (best == -1)
        cout << "impossible" << '\n';
    else
        cout << best << '\n';
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