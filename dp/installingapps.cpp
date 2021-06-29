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

void I() {
    int n,c; cin >> n >> c;
    vector<pair<pair<int, int>, int>> app(n);
    for (int i = 0; i<n; i++) {
        readPair(app[i].first);
        app[i].second = i;
    }

    sort(app.begin(), app.end(), [&](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
        return a.first.second - a.first.first < b.first.second - b.first.first;
    });

    vector<vector<int>> dp(n, vector<int>(c+1, 0));
    vector<vector<pair<int, int>>> backtrack(n, vector<pair<int, int>>(c+1, make_pair(-1, -1)));
    
    int ret = 0;
    pair<int, int> start_pair = {-1, -1};

    for (int i = 1; i<=c; i++) {
        dp[n-1][i] = dp[n-1][i-1];
        backtrack[n-1][i] = backtrack[n-1][i-1];
        int required = max(app[n-1].first.first, app[n-1].first.second);
        if (required <= i) dp[n-1][i] = 1, backtrack[n-1][i] = {n-1, i};

        if (dp[n-1][i] > ret) {
            ret = dp[n-1][i];
            start_pair = backtrack[n-1][i];
        }

    }

    for (int i = n-2; i>=0; i--) {
        for (int j = 1; j<=c; j++) {
            if (dp[i][j-1] > dp[i+1][j]) {
                dp[i][j] = dp[i][j-1];
                backtrack[i][j] = backtrack[i][j-1];
            }
            else {
                dp[i][j] = dp[i+1][j];
                backtrack[i][j] = backtrack[i+1][j];
            }
            int required = max(app[i].first.first, app[i].first.second);
            if (required <= j) {
                if (dp[i][j] < dp[i+1][j - app[i].first.second] + 1) {
                    dp[i][j] = dp[i+1][j - app[i].first.second] + 1;
                    backtrack[i][j] = make_pair(i, j);
                }
            }
            if (dp[i][j] > ret) {
                ret = dp[i][j];
                start_pair = backtrack[i][j];
            }
        }
    }

    cout << ret << '\n';
    if (!ret) return;

    vector<int> list;
    for (int i = 0; i<ret; i++) {
        start_pair = backtrack[start_pair.first][start_pair.second];
        list.push_back(app[start_pair.first].second + 1);
        start_pair.second -= app[start_pair.first++].first.second;
    }

    printArray(list);


}

/*

Sort by (storage - download)

*/

int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("output.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    I();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}
