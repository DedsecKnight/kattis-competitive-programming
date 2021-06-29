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

const int nax = 100000;

void prayGod() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) grid[i][j] = s[j];
    }

    function<ll(char)> top_left = [&](char target) {
        vector<vector<ll>> dp(n, vector<ll>(m, 0));
        vector<vector<int>> grid_cnt(n, vector<int>(m, 0));

        vector<vector<int>> row_cnt(n, vector<int>(m, 0)), col_cnt(m, vector<int>(n, 0));
        vector<vector<ll>> dp_row(n, vector<ll>(m, 0)), dp_col(m, vector<ll>(n, 0));

        ll ret = 0;

        grid_cnt[0][0] = row_cnt[0][0] = col_cnt[0][0] = (grid[0][0] == target);

        for (int i = 1; i < n; i++) {
            grid_cnt[i][0] = grid_cnt[i - 1][0] + (grid[i][0] == target);
            row_cnt[i][0] = (grid[i][0] == target);
            col_cnt[0][i] = col_cnt[0][i - 1] + (grid[i][0] == target);
        }
        for (int i = 1; i < m; i++) {
            grid_cnt[0][i] = grid_cnt[0][i - 1] + (grid[0][i] == target);
            col_cnt[i][0] = (grid[0][i] == target);
            row_cnt[0][i] = row_cnt[0][i - 1] + (grid[0][i] == target);
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                grid_cnt[i][j] = grid_cnt[i - 1][j] + grid_cnt[i][j - 1] - grid_cnt[i - 1][j - 1];
                row_cnt[i][j] = row_cnt[i][j - 1];
                col_cnt[j][i] = col_cnt[j][i - 1];

                if (grid[i][j] == target) {
                    grid_cnt[i][j]++;
                    row_cnt[i][j]++;
                    col_cnt[j][i]++;
                }
            }
        }

        for (int i = 1; i < n; i++) {
            dp[i][0] = (dp[i - 1][0] + col_cnt[0][i - 1]);
            dp_col[0][i] = (dp_col[0][i - 1] + col_cnt[0][i - 1]);
            if (grid[i][0] == target) ret = (ret + dp[i][0]);
        }

        for (int i = 1; i < m; i++) {
            dp[0][i] = dp[0][i - 1] + row_cnt[0][i - 1];
            dp_row[0][i] = dp_row[0][i - 1] + row_cnt[0][i - 1];
            if (grid[0][i] == target) ret = (ret + dp[0][i]);
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                ll topleft = (dp[i - 1][j - 1] + grid_cnt[i - 1][j - 1]);
                ll top = (dp_col[j][i - 1] + col_cnt[j][i - 1]);
                ll left = (dp_row[i][j - 1] + row_cnt[i][j - 1]);
                dp[i][j] = (topleft + top + left);
                dp_row[i][j] = left, dp_col[j][i] = top;
                if (grid[i][j] == target) {
                    ret += dp[i][j];
                }
            }
        }

        return ret;
    };

    function<ll(char)> top_right = [&](char target) {
        vector<vector<ll>> dp(n, vector<ll>(m, 0));
        vector<vector<int>> grid_cnt(n, vector<int>(m, 0));

        vector<vector<int>> row_cnt(n, vector<int>(m, 0)), col_cnt(m, vector<int>(n, 0));
        vector<vector<ll>> dp_row(n, vector<ll>(m, 0)), dp_col(m, vector<ll>(n, 0));

        ll ret = 0;

        grid_cnt[0][m - 1] = row_cnt[0][m - 1] = col_cnt[m - 1][0] = (grid[0][m - 1] == target);
        for (int i = 1; i < n; i++) {
            grid_cnt[i][m - 1] = grid_cnt[i - 1][m - 1] + (grid[i][m - 1] == target);
            row_cnt[i][m - 1] = (grid[i][m - 1] == target);
            col_cnt[m - 1][i] = col_cnt[m - 1][i - 1] + (grid[i][m - 1] == target);
        }
        for (int i = m - 2; i >= 0; i--) {
            grid_cnt[0][i] = grid_cnt[0][i + 1] + (grid[0][i] == target);
            col_cnt[i][0] = (grid[0][i] == target);
            row_cnt[0][i] = row_cnt[0][i + 1] + (grid[0][i] == target);
        }

        for (int i = 1; i < n; i++) {
            for (int j = m - 2; j >= 0; j--) {
                grid_cnt[i][j] = grid_cnt[i - 1][j] + grid_cnt[i][j + 1] - grid_cnt[i - 1][j + 1];
                row_cnt[i][j] = row_cnt[i][j + 1];
                col_cnt[j][i] = col_cnt[j][i - 1];

                if (grid[i][j] == target) {
                    grid_cnt[i][j]++;
                    row_cnt[i][j]++;
                    col_cnt[j][i]++;
                }
            }
        }

        for (int i = 1; i < n; i++) {
            dp[i][m - 1] = (dp[i - 1][m - 1] + col_cnt[m - 1][i - 1]);
            dp_col[m - 1][i] = (dp_col[m - 1][i - 1] + col_cnt[m - 1][i - 1]);
        }

        for (int i = m - 2; i >= 0; i--) {
            dp[0][i] = (dp[0][i + 1] + row_cnt[0][i + 1]);
            dp_row[0][i] = (dp_row[0][i + 1] + row_cnt[0][i + 1]);
        }

        for (int i = 1; i < n; i++) {
            for (int j = m - 2; j >= 0; j--) {
                ll topright = (dp[i - 1][j + 1] + grid_cnt[i - 1][j + 1]) % mod;
                ll top = (dp_col[j][i - 1] + col_cnt[j][i - 1]) % mod;
                ll right = (dp_row[i][j + 1] + row_cnt[i][j + 1]) % mod;
                dp[i][j] = (topright + top + right) % mod;
                dp_row[i][j] = right, dp_col[j][i] = top;
                if (grid[i][j] == target) {
                    ret += topright;
                }
            }
        }

        return ret;
    };

    ll mirko = (top_left('M') + top_right('M'));
    ll slavko = (top_left('S') + top_right('S'));

    cout << mirko << " " << slavko << '\n';
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
