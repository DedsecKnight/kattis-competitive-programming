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

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

void prayGod() {
    int n;
    cin >> n;
    pair<int, int> start_pos, end_pos;
    cin >> start_pos >> end_pos;

    vector<pair<int, int>> pos(n);
    cin >> pos;

    vector<pair<pair<int, int>, int>> sorted_x(n), sorted_y(n);
    for (int i = 0; i < n; i++) {
        sorted_x[i] = make_pair(pos[i], i);
        sorted_y[i] = make_pair(pos[i], i);
    }

    auto x_comp = [&](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
        if (a.first.first != b.first.first) return a.first.first < b.first.first;
        return a.first.second < b.first.second;
    };

    auto y_comp = [&](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
        if (a.first.second != b.first.second) return a.first.second < b.first.second;
        return a.first.first < b.first.first;
    };

    sort(sorted_x.begin(), sorted_x.end(), x_comp);
    sort(sorted_y.begin(), sorted_y.end(), y_comp);

    vector<int> x_pos(n), y_pos(n);

    for (int i = 0; i < n; i++) {
        x_pos[sorted_x[i].second] = i;
    }

    for (int i = 0; i < n; i++) {
        y_pos[sorted_y[i].second] = i;
    }

    int start_idx = find(pos.begin(), pos.end(), start_pos) - pos.begin(), end_idx = find(pos.begin(), pos.end(), end_pos) - pos.begin();
    vector<int> dist(n, iinf);
    dist[start_idx] = 0;

    deque<int> q{start_idx};

    while (!q.empty()) {
        int curr = q.front();
        q.pop_front();

        for (int dx : {-2, 2}) {
            for (int dy : {-1, 1}) {
                int x_fly = x_pos[curr] + dx;
                if (!inrange(x_fly, 0, n - 1) || sorted_x[x_fly].first.first != pos[curr].first) continue;

                int y_fly = y_pos[sorted_x[x_fly].second] + dy;
                if (!inrange(y_fly, 0, n - 1) || sorted_y[y_fly].first.second != sorted_x[x_fly].first.second) continue;

                int dest_idx = sorted_y[y_fly].second;
                if (dist[dest_idx] > dist[curr] + 1) {
                    dist[dest_idx] = dist[curr] + 1;
                    q.push_back(dest_idx);
                }
            }
        }

        for (int dy : {-2, 2}) {
            for (int dx : {-1, 1}) {
                int y_fly = y_pos[curr] + dy;
                if (!inrange(y_fly, 0, n - 1) || sorted_y[y_fly].first.second != pos[curr].second) continue;

                int x_fly = x_pos[sorted_y[y_fly].second] + dx;
                if (!inrange(x_fly, 0, n - 1) || sorted_x[x_fly].first.first != sorted_y[y_fly].first.first) continue;

                int dest_idx = sorted_x[x_fly].second;
                if (dist[dest_idx] > dist[curr] + 1) {
                    dist[dest_idx] = dist[curr] + 1;
                    q.push_back(dest_idx);
                }
            }
        }
    }

    if (dist[end_idx] == iinf)
        cout << -1 << '\n';
    else
        cout << dist[end_idx] << '\n';
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