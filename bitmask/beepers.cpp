#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define printVerdict(verdict) cout << (verdict ? "YES": "NO") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define debugDecimal(d) cerr << setprecision(d) << fixed
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define PI 3.14159265

const int iinf = 0x3f3f3f3f;
const ll inf = 1e18;
const ll mod = 1e9 + 7;


template <class T1, class T2, class T3>
void printTuple(const tuple<T1, T2, T3> &t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(const pair<T1, T2> &p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(const vector<T> &arr) { for (int i = 0; i<len(arr); i++) {cout << arr[i] << " ";} cout << '\n'; }
template<class T>
void read(vector<T> &a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T>
void read(T* a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T>
void readIdx(vector<pair<T, int>> &a, int n) { for (int i = 0; i<n; i++) { cin >> a[i].first; a[i].second = i; }}
template<class T>
void printGrid(const vector<vector<T>> &grid) {for (int i =0; i<len(grid); i++) {for (int j =0; j<len(grid[i]); j++) { cout << grid[i][j] << " ";}cout << '\n';}}
template<class T1, class T2>
void readPair(pair<T1, T2> &a) { cin >> a.first >> a.second; }

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

void F() {
    int t; cin >> t;
    while (t--) {
        int width, height; cin >> width >> height;
        pair<int, int> start; readPair(start);

        int n; cin >> n;
        vector<pair<int, int>> pos(n);

        for (int i =0; i<n; i++) readPair(pos[i]);
        pos.insert(pos.begin(), start);

        function<int(pair<int, int>, pair<int, int>)> get_dist = [&](pair<int, int> a, pair<int, int> b) {
            return abs(a.first - b.first) + abs(a.second - b.second);
        };

        vector<vector<int>> dp(n+1, vector(1<<(n+1), -1));
        for (int i = 1; i<=n; i++) dp[i][(1<<(n+1)) - 1] = get_dist(pos[i], start);
        
        function<int(int, int)> solve = [&](int curr_pos, int mask) {
            if (dp[curr_pos][mask] != -1) return dp[curr_pos][mask];
            dp[curr_pos][mask] = iinf;
            for (int i = 0; i<=n; i++) {
                if (mask & (1<<i)) continue;
                dp[curr_pos][mask] = min(dp[curr_pos][mask], solve(i, mask | (1<<i)) + get_dist(pos[i], pos[curr_pos]));
            }
            return dp[curr_pos][mask];
        };

        cout << solve(0, 1) << '\n';
    }
}

int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("output.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    F();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}
