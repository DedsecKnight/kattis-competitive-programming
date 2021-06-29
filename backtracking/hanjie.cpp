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
    int n,m; cin >> n >> m;
    vector<vector<bool>> grid(n, vector<bool>(m, false));
    
    vector<vector<int>> col_list(m), row_list(n);
    
    vector<pair<int, int>> solve_order;

    for (int i = 0; i<n; i++) {
        int k; cin >> k;
        for (int j =0; j<k; j++) {
            int temp; cin >> temp;
            row_list[i].push_back(temp);
            solve_order.emplace_back(i, temp);
        }
    }

    for (int i= 0; i<m; i++) {
        int k; cin >> k;
        for (int j = 0; j<k; j++) {
            int temp; cin >> temp;
            col_list[i].push_back(temp);
        }
    }

    if (solve_order.empty()) {
        cout << 1 << '\n';
        return;
    }

    function<bool()> valid = [&]() {
        for (int j = 0; j<m; j++) {
            int ptr = 0, col_idx = 0;
            for (int i = 0; i<n; i++) {
                if (grid[i][j] && !grid[ptr][j]) ptr = i;
                else if (grid[ptr][j] && !grid[i][j]) {
                    int cnt = i-ptr;
                    if (col_idx >= len(col_list[j]) || cnt != col_list[j][col_idx]) return false;
                    col_idx++;
                    ptr = i;
                }
            }
            if (ptr < n && grid[ptr][j]) {
                int cnt = n-ptr;
                if (col_idx >= len(col_list[j]) || cnt != col_list[j][col_idx]) return false;
                col_idx++;
            }
            if (col_idx < len(col_list[j])) return false;
        }
        return true;
    };

    int possible = 0;

    function<void(int, int)> solve = [&](int idx, int col) {
        if (solve_order[idx].second + col > m) return;
        for (int i = col; i < col + solve_order[idx].second && i < m; i++) grid[solve_order[idx].first][i] = true;
    
        if (idx >= len(solve_order) - 1) possible += valid();
        else {
            int next_pos = (solve_order[idx+1].first == solve_order[idx].first ? col + solve_order[idx].second + 1 : 0);
            for (int i = next_pos; i+solve_order[idx+1].second <= m; i++) solve(idx+1, i);
        }

        for (int i = col; i < col + solve_order[idx].second && i < m; i++) grid[solve_order[idx].first][i] = false;  
    };
    
    for (int i = 0; i + solve_order[0].second <= m; i++) solve(0, i);
    cout << possible << '\n';
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
