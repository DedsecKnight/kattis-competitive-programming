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

int find_rep(int u, vector<int> &parent) {
    if (parent[u] == u) return u;
    return parent[u] = find_rep(parent[u], parent);
}

void merge(int u, int v, vector<int> &set_size, vector<int> &parent, vector<ll> &total) {
    u = find_rep(u, parent), v = find_rep(v, parent);
    if (u == v) return;
    if (set_size[u] < set_size[v]) swap(u, v);
    set_size[u] += set_size[v];
    total[u] += total[v];
    parent[v] = u;
}

void prayGod() {
    int n; cin >> n;
    vector<int> a(n), p(n), parent(n), set_size(n);
    vector<ll> total(n);
    read(a, n); read(p, n);
    reverse(p.begin(), p.end());

    function<ll(int)> round_up = [&](int val) {
        int div = (val + 9)/10;
        return ll(div*10);
    };

    ll curr_sum = 0;

    for (int i = 0; i<n; i++) {
        p[i]--;
        parent[i] = i;
        set_size[i] = 1;
        total[i] = a[i];
    }
    
    vector<bool> exist_leader(n, false);
    ll ret = 0;
    int leader_cnt = 0;

    function<void(int, int)> check_merge = [&](int neighbor, int curr) {
        if (!inrange(neighbor, 0, n-1)) return;
        int neighbor_parent = find_rep(neighbor, parent);
        if (exist_leader[neighbor_parent]) {
            leader_cnt--;
            exist_leader[neighbor_parent] = false;
            curr_sum -= round_up(total[neighbor_parent]);
            merge(neighbor_parent, curr, set_size, parent, total);
        }
    };

    for (int i = 0; i<n; i++) {
        check_merge(p[i] + 1, p[i]);
        check_merge(p[i] - 1, p[i]);
        
        int new_parent = find_rep(p[i], parent);
        curr_sum += round_up(total[new_parent]);
        if (!exist_leader[new_parent]) leader_cnt++;
        exist_leader[new_parent] = true;

        ret = max(ret, curr_sum * leader_cnt);
    }

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