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

void prayGod() {
    int a,b,e,p; cin >> a >> b >> e >> p;
    vector<vector<int>> graph(e), reverse_graph(e);
    
    for (int i = 0; i<p; i++) {
        int x,y; cin >> x >> y;
        graph[x].push_back(y);
        reverse_graph[y].push_back(x);
    }

    function<pair<int, int>(int)> bfs = [&](int start) {
        vector<bool> visited(e, false);
        visited[start] = true;
        deque<int> q; q.push_back(start);
        int high = 1, low = 1;
        while (!q.empty()) {
            int curr = q.front(); q.pop_front();
            for (int neighbor : graph[curr]) {
                if (visited[neighbor]) continue;
                visited[neighbor] = true;
                high++;
                q.push_back(neighbor);
            }
        }
        
        visited.assign(e, false);
        q.push_back(start);
        while (!q.empty()) {
            int curr = q.front(); q.pop_front();
            for (int neighbor : reverse_graph[curr]) {
                if (visited[neighbor]) continue;
                visited[neighbor] = true;
                low++;
                q.push_back(neighbor);
            }
        }

        return make_pair(low, e-high+1);
    };

    int surea = 0, sureb = 0, nob = 0;

    for (int i = 0; i<e; i++) {
        pair<int, int> temp = bfs(i);
        int low = temp.first, high = temp.second;
        //cerr << var(i) << var(low) << var(high) << '\n';

        if (high <= a) surea++;
        if (high <= b) sureb++;
        if (low > b) nob++;
    }
    
    cout << surea << '\n';
    cout << sureb << '\n';
    cout << nob << '\n';

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