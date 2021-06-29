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

const int a[]{-1, 1, 0, 0, -1, -1, 1, 1};
const int b[]{0, 0, -1, 1, 1, -1, -1, 1};
 
void prayGod() {
    int n, m; cin >> n >> m;
    vector<vector<ll>> grid(n, vector<ll>(m)), capacity(n, vector<ll>(m, 0));
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) cin >> grid[i][j];
    }
    pair<int, int> start;
    readPair(start);
    start.first--, start.second--;
    capacity[start.first][start.second] = abs(grid[start.first][start.second]);

    auto comp = [&](pair<int, int> a1, pair<int, int> b1) {
        if (capacity[a1.first][a1.second] != capacity[b1.first][b1.second]) return capacity[a1.first][a1.second] > capacity[b1.first][b1.second];
        return a1 < b1;
    };

    set<pair<int, int>, decltype(comp)> q(comp);
    q.insert(start);
    while (!q.empty()) {
        pair<int, int> curr = *q.begin();
        q.erase(q.begin());
        for (int k = 0; k<8; k++) {
            int new_x = curr.first + a[k], new_y = curr.second + b[k];
            if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1) || grid[new_x][new_y] >= 0) continue;
            int possible_capacity = min(capacity[curr.first][curr.second], -grid[new_x][new_y]);
            if (capacity[new_x][new_y] < possible_capacity) {
                q.erase(make_pair(new_x, new_y));
                capacity[new_x][new_y] = possible_capacity;
                q.insert(make_pair(new_x, new_y));
            }
        }
    }

    ll ret = 0;
    for (int i =0; i<n; i++) {
        for (int j =0; j<m; j++) ret += capacity[i][j];
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