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
#define printCase(_) cout << "Case #" << (_) << ": "

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
 
const char* INPUT_FILE = "input.txt";
const char* OUTPUT_FILE = "output.txt";

void prayGod() {
    int n,c; cin >> n >> c;
    vector<int> a(n); read(a, n);

    vector<vector<int>> dp(n+1, vector<int>(c+1, -iinf));

    dp[0][0] = 0;
    for (int i = 1; i<=c; i++) dp[0][i] = -iinf;
    for (int i = 1; i<=n; i++) {
        if (i == 1) dp[i][0] = a[i-1];
        else dp[i][0] = min(dp[i-1][0], a[i-1]);
    }

    for (int i = 1; i<=n; i++) {
        for (int j = 1; j<=c; j++) {
            if (dp[i-1][j] == 0) dp[i][j] = a[i-1];
            else if (dp[i-1][j] != -iinf) dp[i][j] = min(dp[i-1][j], a[i-1]);
            
            if (a[i-1] <= j && dp[i-1][j-a[i-1]] != -iinf) {
                if (dp[i][j] != -iinf) dp[i][j] = max(dp[i][j], dp[i-1][j-a[i-1]]);
                else dp[i][j] = dp[i-1][j-a[i-1]];
            }
        }
    }

    for (int i = 0; i<=c; i++) {
        if (dp[n][i] == iinf) continue;
        if (i + dp[n][i] > c) {
            cout << i << '\n';
            return;
        }
    }    
    
    int ret = 0;
    for (int i = 0; i<n; i++) ret += a[i];
    cout << ret << '\n';
}
 
int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen(INPUT_FILE, "r", stdin);
    if (EXTERNAL_OUTPUT) freopen(OUTPUT_FILE, "w", stdout);
    
    prayGod();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}

