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
const ll mod = 1e9 + 9;
 
 
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
    int n,m; cin >> n >> m;
    vector<vector<pair<int, ll>>> graph(n), reverse_graph(n);
    for (int i = 0; i<m; i++) {
        int u,v; 
        ll w; cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        reverse_graph[v].emplace_back(u, w);
    }
    int s,t; cin >> s >> t;
    
    vector<ll> dist(n, inf);
    
    dist[s] = 0;

    auto comp = [&dist](int a, int b) {
        if (dist[a] != dist[b]) return dist[a] < dist[b];
        return a < b;
    };

    set<int, decltype(comp)> q(comp);
    q.insert(s);

    while (!q.empty()) {
        int curr = *q.begin();
        q.erase(q.begin());
        for (pair<int, ll> neighbor : graph[curr]) {
            if (dist[neighbor.first] > dist[curr] + neighbor.second) {
                q.erase(neighbor.first);
                dist[neighbor.first] = dist[curr] + neighbor.second;
                q.insert(neighbor.first);
            }
        }
    }

    vector<ll> cnt(n, 0), cnt2(n, 0);
    vector<bool> visited(n, false);
    
    visited[s] = true;
    cnt[s] = 1;
    cnt2[t] = 1;
    
    function<void(int)> dfs1 = [&](int curr) {
        visited[curr] = true;
        for (pair<int, ll> neighbor : reverse_graph[curr]) {
            if (dist[neighbor.first] + neighbor.second != dist[curr]) continue;
            if (!visited[neighbor.first]) dfs1(neighbor.first);
            cnt[curr] += cnt[neighbor.first];
            cnt[curr] %= mod;
        } 
    };

    function<void(int)> dfs2 = [&](int curr) {
        visited[curr] = true;
        for (pair<int, ll> neighbor : graph[curr]) {
            if (dist[curr] + neighbor.second != dist[neighbor.first]) continue;
            if (!visited[neighbor.first]) dfs2(neighbor.first);
            cnt2[curr] += cnt2[neighbor.first];
            cnt2[curr] %= mod;
        }
    };

    set<int> seen{s, t};
    vector<int> ret;
    
    dfs1(t);
    visited.assign(n, false);
    visited[t] = true;
    dfs2(s);

    for (int i = 0; i<n; i++) cnt[i] = ((cnt[i] % mod) * (cnt2[i] % mod)) % mod;

    for (int i = 0; i<n; i++) {
        if (i == s || i == t) continue;
        if (cnt[i] == cnt[t]) seen.insert(i);
    }

    while (!seen.empty()) {
        ret.push_back(*seen.begin());
        seen.erase(seen.begin());
    }

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
