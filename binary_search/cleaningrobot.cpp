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
constexpr ll inf = 1000000000000000000;
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

constexpr int MAXN = 1e5 + 10;
constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};

void prayGod() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> is_obstructed(n, vector<int>(m, 0));
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        is_obstructed[--x][--y] = 1;
    }

    for (int i = n - 1; i >= 0; i--) {
        dp[i][m - 1] = is_obstructed[i][m - 1];
        if (i + 1 < n) dp[i][m - 1] += dp[i + 1][m - 1];
    }

    for (int j = m - 1; j >= 0; j--) {
        dp[n - 1][j] = is_obstructed[n - 1][j];
        if (j + 1 < m) dp[n - 1][j] += dp[n - 1][j + 1];
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = m - 2; j >= 0; j--) {
            dp[i][j] = dp[i + 1][j] + dp[i][j + 1] - dp[i + 1][j + 1] + is_obstructed[i][j];
        }
    }

    vector<vector<int>> mrow(n, vector<int>(m + 1, 0));
    vector<vector<int>> mcol(m, vector<int>(n + 1, 0));
    vector<vector<bool>> can_robot(n, vector<bool>(m, false)), visited(n, vector<bool>(m, false));

    int low = 1, high = min(n, m), best = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                can_robot[i][j] = false;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                mrow[i][j] = 0;
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j <= n; j++) {
                mcol[i][j] = 0;
            }
        }

        for (int i = 0; i + mid <= n; i++) {
            for (int j = 0; j + mid <= m; j++) {
                int total = dp[i][j];
                if (i + mid < n) total -= dp[i + mid][j];
                if (j + mid < m) total -= dp[i][j + mid];
                if (i + mid < n && j + mid < m) total += dp[i + mid][j + mid];
                can_robot[i][j] = !total;
            }
        }

        auto update = [&](int x, int y, int z) {
            if (z == 0) {
                mrow[x][y]++;
                mrow[x][y + mid]--;
            } else if (z == 1) {
                mrow[x + mid - 1][y]++;
                mrow[x + mid - 1][y + mid]--;
            } else if (z == 2) {
                mcol[y][x]++;
                mcol[y][x + mid]--;
            } else {
                mcol[y + mid - 1][x]++;
                mcol[y + mid - 1][x + mid]--;
            }
        };

        bool done = false;

        for (int i = 0; i < n - mid + 1 && !done; i++) {
            for (int j = 0; j < m - mid + 1; j++) {
                if (!can_robot[i][j]) continue;
                queue<pair<int, int>> q;
                q.emplace(i, j);
                visited[i][j] = true;
                for (int d = i; d < i + mid; d++) {
                    mrow[d][j]++;
                    mrow[d][j + mid]--;
                }
                for (int d = j; d < j + mid; d++) {
                    mcol[d][i]++;
                    mcol[d][i + mid]--;
                }
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    for (int z = 0; z < 4; z++) {
                        auto nx = x + dx[z], ny = y + dy[z];
                        if (!inrange(nx, 0, n - mid) || !inrange(ny, 0, m - mid)) continue;
                        if (!visited[nx][ny] && can_robot[nx][ny]) {
                            visited[nx][ny] = true;
                            q.emplace(nx, ny);
                            update(nx, ny, z);
                        }
                    }
                }
                done = true;
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= m; j++) mrow[i][j] += mrow[i][j - 1];
        }
        for (int i = 0; i < m; i++) {
            for (int j = 1; j <= n; j++) mcol[i][j] += mcol[i][j - 1];
        }

        bool possible = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                auto h = mrow[i][j] + mcol[j][i];
                if (!is_obstructed[i][j] && !h) {
                    possible = false;
                }
            }
        }

        if (possible) {
            best = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

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