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
const ll inf = 2e18;
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
    int n; ll k; cin >> n >> k;
    vector<vector<int>> graph(n);

    for (int i = 0; i<n-1; i++) {
        int u,v; cin >> u >> v;
        graph[--u].push_back(--v);
        graph[v].push_back(u);
    }

    vector<vector<ll>> dp(n);

    function<ll(ll, ll)> mult = [&](ll a, ll b) {
        if (a >= inf / b) return inf;
        return a*b;
    };

    function<ll(ll, ll)> add = [&](ll a, ll b) {
        if (a >= inf - b) return inf;
        return a + b;
    };

    function<void(int, int)> merge = [&](int a, int b) {
        vector<ll> ret(min(n+1, len(dp[a]) + len(dp[b])), 0);
        for (int i = 0; i<len(dp[a]); i++) {
            for (int j = 0; j<len(dp[b]); j++) {
                if (!dp[a][i] || !dp[b][j] || i+j >= len(ret)) continue;
                ll new_coefficient = mult(dp[a][i], dp[b][j]);
                ret[i+j] = add(ret[i+j], new_coefficient);
            }
        }
        dp[a].resize(len(ret));
        for (int i = 0; i<len(ret); i++) dp[a][i] = ret[i];
        
    };

    function<void(int, int)> dfs = [&](int curr, int par) {
        dp[curr] = {0, 1};
        for (int neighbor : graph[curr]) {
            if (neighbor == par) continue;
            dfs(neighbor, curr);
            merge(curr, neighbor);
        }   
        dp[curr][0]++;
    };

    dfs(0, -1);

    for (int j = 1; j<=n; j++) {
        for (int i = 0; i<n; i++) {
            if (j < len(dp[i])) k -= dp[i][j];
            if (k <= 0) {
                cout << j << '\n';
                return;
            }
        }
    }

    cout << -1 << '\n';

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