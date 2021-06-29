#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
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
void printArray(vector<T> arr) { for (int i = 0; i<len(arr); i++) {cout << arr[i] << " ";} cout << '\n'; }
template<class T>
void read(vector<T> &a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T> 
void read(T* a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T>
void readIdx(vector<pair<T, int>> &a, int n) { for (int i = 0; i<n; i++) { cin >> a[i].first; a[i].second = i; }} 
template<class T>
void printGrid(vector<vector<T>> &grid) {for (int i =0; i<len(grid); i++) {for (int j =0; j<len(grid[i]); j++) { cout << grid[i][j] << " ";}cout << '\n';}}
template<class T1, class T2>
void readPair(pair<T1, T2> &a) { cin >> a.first >> a.second; }
 
 
const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

void dijkstra_spider(vector<ll> &spider_dist, vector<vector<pair<int, int>>> &graph) {
    auto comp = [&spider_dist](int a, int b) {
        if (spider_dist[a] != spider_dist[b]) return spider_dist[a] < spider_dist[b];
        return a < b;
    };
    set<int, decltype(comp)> q(comp);
    for (int i = 0; i<len(graph); i++) q.insert(i); 
    while (!q.empty()) {
        int curr = *q.begin();
        q.erase(q.begin());
        for (pair<int, int> neighbor : graph[curr]) {
            if (spider_dist[neighbor.first] > spider_dist[curr] + neighbor.second) {
                q.erase(neighbor.first);
                spider_dist[neighbor.first] = spider_dist[curr] + neighbor.second;
                q.insert(neighbor.first);
            }
        }
    }
}
 
void prayGod() {
    int n,m,t; cin >> n >> m >> t;
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i<m; i++) {
        int u,v,w; cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    int start, dest; cin >> start >> dest;
    int k; cin >> k;
    vector<ll> spider_dist(n, inf);
    for (int i = 0; i<k; i++) {
        int temp; cin >> temp;
        spider_dist[temp] = 0;
    }
    
    dijkstra_spider(spider_dist, graph);

    int low = 0, high = spider_dist[start], ret = 0;
    while (low <= high) {
        int mid = low + (high - low)/2;
        vector<ll> dist(n, inf);
        dist[start] = 0;
        auto comp = [&dist](int a, int b) {
            if (dist[a] != dist[b]) return dist[a] < dist[b];
            return a < b;
        };
        set<int, decltype(comp)> q(comp);
        q.insert(start);
        while (!q.empty()) {
            int curr = *q.begin();
            q.erase(q.begin());
            for (pair<int, int> neighbor : graph[curr]) {
                if (spider_dist[neighbor.first] < mid) continue;
                if (dist[neighbor.first] > dist[curr] + neighbor.second) {
                    q.erase(neighbor.first);
                    dist[neighbor.first] = dist[curr] + neighbor.second;
                    q.insert(neighbor.first);
                }
            }
        }
        if (dist[dest] <= t) ret = mid, low = mid+1;
        else high = mid-1;
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
