#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define ordered_set(type, comp) tree <type, null_type, decltype(comp), rb_tree_tag, tree_order_statistics_node_update>
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
void printTuple(tuple<T1, T2, T3> t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(pair<T1, T2> p) { cout << p.first << " " << p.second << '\n'; }
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
    ld l,a,b,t,r; cin >> l >> a >> b >> t >> r;
    int n; cin >> n;

    vector<ld> cart(n), dp(n);
    read(cart, n);

    if (!n) {
        cout << 0 << '\n';
        return;
    }

    ld curr_best = l/a;
    int best_start = -1;

    vector<int> next(n, -1);

    function<void(int)> update_dist = [&](int i) {
        ld new_dist = dp[i] + cart[i]/a;
        if (new_dist < curr_best) {
            curr_best = new_dist;
            best_start = i;
        }
    };

    for (int i = 0; i<n; i++) {
        ld wait = cart[i] + a*t;
        if (wait >= l) dp[i] = ld(l - cart[i]) / a;
        else {
            ld finish_coffee = wait + b*r;
            if (finish_coffee >= l) dp[i] = t + (l - wait)/b;
            else dp[i] = t + r + (l - finish_coffee)/a;
        }
        update_dist(i);
    }
    
    function<int(int, ll)> search_max = [&](int i, ld target) {
        int low = i+1, high = n-1, ret = -1;
        while (low <= high) {
            int mid = low + (high - low)/2;
            if (cart[mid] <= target) ret = mid, low = mid+1;
            else high = mid-1;
        }
        return ret;
    };

    function<int(int, ll)> search_min = [&](int i, ld target) {
        int low = i+1, high = n-1, ret = -1;
        while (low <= high) {
            int mid = low + (high - low)/2;
            if (cart[mid] > target) ret = mid, high = mid-1;
            else low = mid+1;
        }
        return ret;
    };

    function<void(int, int)> solve = [&](int i, int idx) {
        if (idx == -1) return;
        ld wait = cart[i] + a*t, new_candidate = 1e18;
        if (wait >= cart[idx]) new_candidate = dp[idx] + (cart[idx] - cart[i])/a;
        else {
            ld finish_coffee = wait + b*r;
            if (finish_coffee >= cart[idx]) new_candidate = dp[idx] + t + (cart[idx] - wait)/b;
            else new_candidate = dp[idx] + t + r + (cart[idx] - finish_coffee)/a;
        }
        if (new_candidate < dp[i]) {
            dp[i] = new_candidate;
            next[i] = idx;
        }
    };

    for (int i = n-2; i>=0; i--) {
        solve(i, i+1);

        ld coffee_finish = cart[i] + a*t + b*r;
        solve(i, search_max(i, coffee_finish));

        solve(i, search_min(i, coffee_finish));

        update_dist(i);
    }

    vector<int> ret;

    while (best_start != -1) {
        ret.push_back(best_start);
        best_start = next[best_start];
    }

    cout << len(ret) << '\n';
    printArray(ret);

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
