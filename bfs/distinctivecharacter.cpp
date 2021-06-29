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
    int n,k; cin >> n >> k;
    function<int(string)> parse = [&](string bit) {
        int ret = 0, curr = 1;
        for (int i = k-1; i>=0; i--) {
            if (bit[i] == '1') ret += curr;
            curr *= 2;
        }
        return ret;
    };
    vector<int> dist(1<<k, iinf);
    deque<int> q;
    for (int i=  0; i<n; i++) {
        string s; cin >> s;
        int val = parse(s);
        dist[val] = 0;
        q.push_back(val);
    }
    while (!q.empty()) {
        int curr = q.front();
        q.pop_front();
        for (int i = 0; i<k; i++) {
            int temp = curr ^ (1<<i);
            if (dist[temp] > dist[curr] + 1) {
                dist[temp] = dist[curr] + 1;
                q.push_back(temp);
            }
        }
    }
    int best = 0, currMax = dist[0];
    for (int i = 1; i<(1<<k); i++) {
        if (currMax < dist[i]) currMax = dist[i], best = i;
    } 

    string ret = "";
    for (int i = 0; i<k; i++) {
        ret += to_string(best%2);
        best /= 2;
    }
    reverse(ret.begin(), ret.end());
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