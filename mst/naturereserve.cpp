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

int findRep(int u, vector<int> &union_data) {
    if (union_data[u] < 0) return u;
    return union_data[u] = findRep(union_data[u], union_data);
} 

ll merge(int u, int v, int energyCost, ll currCost, vector<int> &union_data) {
    u = findRep(u, union_data);
    v = findRep(v, union_data);

    if (u == v) return currCost;
    if (union_data[u] > union_data[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    union_data[u] += union_data[v];
    union_data[v] = u;
    currCost += energyCost;
    return currCost;
}

void prayGod() {
    int t; cin >> t;
    while (t--) {
        int n,m,l,s; cin >> n >> m >> l >> s;
        vector<int> union_data(n+1, -1);

        ll minCost = 0;
        for (int i = 0; i<s; i++) {
            int temp; cin >> temp;
            minCost = merge(0, temp, 0, minCost, union_data);
        }

        vector<pair<pair<int, int>, int>> edgeList;
        for (int i = 0; i<m; i++) {
            int u, v, w; cin >> u >> v >> w;
            edgeList.emplace_back(make_pair(u, v), w);
        }

        sort(edgeList.begin(), edgeList.end(), [&](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
            return a.second < b.second;
        });

        int maxSize = 1;
        for (int i= 0; i<n+1; i++) {
            if (union_data[i] < 0) maxSize = max(maxSize, -union_data[i]);
        }

        for (pair<pair<int, int>, int> e : edgeList) {
            if (maxSize >= n+1) break;
            minCost = merge(e.first.first, e.first.second, e.second + l, minCost, union_data);
            int repu = findRep(e.first.first, union_data), repv = findRep(e.first.second, union_data);
            maxSize = max(maxSize, max(-union_data[repu], -union_data[repv]));
        } 

        cout << minCost << '\n';
    }
    
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

