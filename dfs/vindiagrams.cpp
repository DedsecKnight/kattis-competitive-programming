#include <bits/stdc++.h>
#include <queue>

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
void read_pair(vector<pair<T, int>> &a, int n) {
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

constexpr bool PRINT_EXEC_TIME = true;
constexpr bool EXTERNAL_INPUT = false;
constexpr bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "cases.txt";
const char *OUTPUT_FILE = "output.txt";

constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};

void prayGod() {
    int n,m;
    cin >> n >> m;
    vec<string> grid(n);
    cin >> grid;

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vec<pair<int, int>> corner_a, corner_b;

    function<bool(int, int)> is_intersection = [&](int i, int j) {
        if (!inrange(i, 1, n-2) || !inrange(j, 1, m-2)) {
            return false;
        }
        for (int k = 0; k<4; k++) {
            int new_x = i + dx[k], new_y = j + dy[k];
            if (grid[new_x][new_y] == '.') return false;
        }
        return true;
    };

    function<bool(int, int)> is_corner = [&](int i, int j) {
        if (is_intersection(i, j)) return false;
        for (int k1 : {0, 1}) {
            for (int k2 : {2, 3}) {
                int x1 = i+dx[k1], y1 = j+dy[k1];
                int x2 = i+dx[k2], y2 = j+dy[k2];
                if (!inrange(x1, 0, n-1) || !inrange(x2, 0, n-1)) {
                    continue;
                }
                if (!inrange(y1, 0, m-1) || !inrange(y2, 0, m-1)) {
                    continue;
                }
                if (grid[x1][y1] != '.' && grid[x2][y2] != '.') {
                    return true;
                }
            }
        }
        return false;
    };

    function<bool(int, int, const vec<pair<int, int>>&)> in_set = [&](int x, int y, const vec<pair<int, int>>& p) {
        int cut_seg = 0;
        for (int i = 0; i<len(p); i++) {
            int nxt = (i + 1) % len(p);
            if (inrange(x, min(p[i].first, p[nxt].first) + 1, max(p[i].first, p[nxt].first))) {
                cut_seg += (y <= p[i].second);
            }
        }
        return cut_seg % 2 == 1;
    };

    function<void(int, int, int, int)> dfs = [&](int i, int j, int dir, int is_a) {
        visited[i][j] = true;
        if (is_a && is_corner(i, j)) {
            corner_a.emplace_back(i, j);
        } else if (!is_a && is_corner(i, j)) {
            corner_b.emplace_back(i, j);
        }
        int new_x = i+dx[dir], new_y = j+dy[dir];
        if (inrange(new_x, 0, n-1) && inrange(new_y, 0, m-1) && grid[new_x][new_y] == 'X' && !visited[new_x][new_y]) {
            dfs(new_x, new_y, dir, is_a);
            return;
        }
        for (int k = 0; k<4; k++) {
            new_x = i+dx[k], new_y = j+dy[k];
            if (inrange(new_x, 0, n-1) && inrange(new_y, 0, m-1) && grid[new_x][new_y] == 'X' && !visited[new_x][new_y]) {
                dfs(new_x, new_y, k, is_a);
                return;
            }
        }
    };

    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            if (grid[i][j] == 'A') {
                visited[i][j] = true;
                if (is_corner(i, j) && !is_intersection(i, j)) {
                    corner_a.emplace_back(i, j);
                }
                for (int k = 0; k<4; k++) {
                    int new_x = i+dx[k], new_y = j+dy[k];
                    if (inrange(new_x, 0, n-1) && inrange(new_y, 0, m-1) && grid[new_x][new_y] == 'X' && !visited[new_x][new_y]) {
                        dfs(new_x, new_y, k, 1);
                        break;
                    }
                }
                break;
            }
        }
    }

    for (int i = 1; i<n-1; i++) {
        for (int j = 1; j<m-1; j++) {
            if (grid[i][j] != 'X' || !visited[i][j]) continue;
            if (is_intersection(i, j)) {
                visited[i][j] = false;
            }
        }
    }

    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            if (grid[i][j] == 'B') {
                visited[i][j] = true;
                if (is_corner(i, j) && !is_intersection(i, j)) {
                    corner_b.emplace_back(i, j);
                }
                for (int k = 0; k<4; k++) {
                    int new_x = i+dx[k], new_y = j+dy[k];
                    if (inrange(new_x, 0, n-1) && inrange(new_y, 0, m-1) && grid[new_x][new_y] == 'X' && !visited[new_x][new_y]) {
                        dfs(new_x, new_y, k, 0);
                        break;
                    }
                }
                break;
            }
        }
    }

    int only_a = 0, only_b = 0, both = 0;

    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            if (grid[i][j] != '.') continue;
            bool belongs_to_a = in_set(i, j, corner_a);
            bool belongs_to_b = in_set(i, j, corner_b);
            if (belongs_to_a && belongs_to_b) {
                both++;
            } else if (belongs_to_a) {
                only_a++;
            } else if (belongs_to_b) {
                only_b++;
            }
        }
    }

    cout << only_a << " " << only_b << " " << both << '\n';
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
