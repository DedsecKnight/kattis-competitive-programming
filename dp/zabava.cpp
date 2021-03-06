#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printVerdict(verdict) cout << (verdict ? "Yes": "No") << '\n'
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

void prayGod() {
    int n,m,k; cin >> n >> m >> k;
    vector<int> event(n);
    read(event, n);
    
    vector<int> cnt(m, 0);
    for (int e : event) cnt[e-1]++;
    
    function<ll(int)> summation = [&](int val) {
        return ll(val)*(ll(val)+1)/2;
    };
    
    // split[i][j] denotes min noise level when splitting the i-th large group into j sub-groups
    vector<vector<ll>> split(m, vector<ll>(m+k+1, inf));
    for (int i = 0; i<m; i++) {
        for (int j = 1; j<=m+k; j++) {
            int rem = cnt[i] % j;
            split[i][j] = summation(cnt[i]/j + 1) * rem + summation(cnt[i]/j) * (j - rem);
        }
    }
    
    // Time complexity : O(m * (m + k)^2)
    vector<vector<ll>> dp(m, vector<ll>(m+k+1, inf));
    for (int i = 1; i<=m+k; i++) dp[0][i] = split[0][i];
    for (int i = 1; i<m; i++) {
        for (int j = 1; j<=m+k; j++) {
            for (int z = 1; z<=m+k; z++) {
                if (j >= z) dp[i][j] = min(dp[i][j], dp[i-1][j-z] + split[i][z]);
            }
        }
    }
    
    
    ll ret = inf;
    for (int i = 1; i<=m+k; i++) ret = min(ret, dp[m-1][i]);
    cout << ret << '\n';
}
 
int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("input.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    prayGod();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / 1000.0;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " ms" << '\n';
} 
