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

const int nax = 5e6 + 10;

void prayGod() {
    int n; cin >> n;
    vector<int> a(n); read(a, n);
    if (n < 3) {
        cout << 0 << '\n';
        return;
    }
    sort(a.begin(), a.end());
    
    function<int(int, int, int)> search = [&](int low, int high, int target) {
        int ret = -1;
        while (low <= high) {
            int mid = low + (high - low)/2;
            if (a[mid] < target) ret = mid, low = mid+1;
            else high = mid-1;
        }
        return ret;
    };

    function<ll(int, int)> binpow = [&](int a1, int b1) {
        if (!b1) return 1ll;
        if (b1 == 1) return ll(a1);
        ll ret = binpow(a1, b1/2);
        ret *= ret;
        if (b1 & 1) ret *= ll(a1);
        return ret;
    };

    ll ret = 0;
    for (int i = 0; i<n-1; i++) {
        for (int j = i+1; j<n; j++) {
            int curr = search(j+1, n-1, a[i] + a[j]);
            if (curr != -1) ret += binpow(2, curr - j) - 1;
        }
    }
    cout << ret << '\n';

}
 
int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("output.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    prayGod();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
} 
