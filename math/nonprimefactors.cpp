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

ll binpow(int a, int b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    ll ret = binpow(a, b/2);
    ret *= ret;
    if (b&1) ret *= a;
    return ret;
}

void prayGod() {
    int q, n = 2; cin >> q;
    vector<int> query_list;

    while (q--) {
        int temp; cin >> temp;
        n = max(n, temp);
        query_list.push_back(temp);
    }

    vector<ll> p_cnt(n+1, 1);
    vector<int> prime_cnt(n+1, 0);
    vector<bool> isPrime(n+1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i*2; j<=n; j+=i) {
                int low = 1, high = int(log(j) / log(i)) + 3, ret = 1;
                while (low <= high) {
                    int mid = low + (high - low)/2;
                    ll curr = binpow(i, mid);
                    if (j % curr == 0) ret = mid, low = mid+1;
                    else high = mid-1;
                }
                p_cnt[j] *= (ret + 1);
                prime_cnt[j]++;
                isPrime[j] = false;
            }
        }
    } 
    
    for (int i = 2; i<=n; i++) p_cnt[i] -= prime_cnt[i];

    for (int query : query_list) cout << p_cnt[query] << '\n';
    
}
 
int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("output.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    prayGod();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / 1000.0;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " ms" << '\n';
} 
