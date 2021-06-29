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

const int a[]{-1, 1, 0, 0};
const int b[]{0, 0, -1, 1};
 
void prayGod() {
    int n,m; cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) cin >> grid[i][j];
    }
    
    pair<int, int> target;
    readPair(target);
    target.first--, target.second--;

    umap<int, int> horizontal;
    pair<int, int> start;

    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            if (grid[i][j] < 0) {
                if (grid[i][j] == -1) start = make_pair(i, j);
                continue;
            }
            if (!present(horizontal, grid[i][j])) {
                for (int k = 0; k<4; k++) {
                    int new_x = i+a[k], new_y = j+b[k];
                    if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1)) continue;
                    if (grid[new_x][new_y] == grid[i][j]) {
                        horizontal[grid[i][j]] = (k >= 2);
                        break;
                    }
                }
            }
        }
    }

    int total = 1e9;
    vector<int> curr, ret;

    function<void(int, pair<int, int>)> solve = [&](int prev, pair<int, int> curr_position) {
        if (target == curr_position) {
            if (len(curr) < total) {
                ret = curr;
                total = len(curr);
            }
            else if (len(curr) == total) {
                bool smaller = false;
                for (int i = 0; i<total; i++) {
                    if (curr[i] == ret[i]) continue;
                    smaller = curr[i] < ret[i];
                    break;
                }
                if (smaller) ret = curr;
            }
            return;
        }
        int i = curr_position.first, j = curr_position.second;
        for (int k = 0; k<4; k++) {
            int new_x = i+a[k], new_y = j+b[k];
            if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1) || grid[new_x][new_y] < 0 || grid[new_x][new_y] == prev) continue;
            if (horizontal[grid[new_x][new_y]] == (k >= 2)) {
                curr.push_back(grid[new_x][new_y]);
                new_x += a[k], new_y += b[k];
                swap(grid[new_x][new_y], grid[i][j]);
                solve(grid[i][j], make_pair(new_x, new_y));
                swap(grid[new_x][new_y], grid[i][j]);
                curr.pop_back();
            }
        }
    };

    solve(1e9, start);
    
    if (total == 1e9) cout << "impossible" << '\n';
    else printArray(ret);
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