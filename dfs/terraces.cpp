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

const int a[]{-1,1,0,0};
const int b[]{0, 0, -1, 1};

void E() {
    int n,m; cin >> m >> n;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) cin >> grid[i][j];
    }
    vector<vector<bool>> possible(n, vector<bool>(m, true)), visited(n, vector<bool>(m, false));
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            for (int k =0; k<4; k++) {
                int new_x = i+a[k], new_y = j+b[k];
                if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1)) continue;
                if (grid[new_x][new_y] < grid[i][j]) {
                    possible[i][j] = false;
                    break;
                }
            }
        }
    }

    function<void(int, int)> dfs = [&](int i, int j) {
        visited[i][j] = true;
        possible[i][j] = false;
        for (int k = 0; k<4; k++) {
            int new_x = i+a[k], new_y = j+b[k];
            if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1) || visited[new_x][new_y]) continue;
            if (grid[new_x][new_y] == grid[i][j]) dfs(new_x, new_y); 
        }
    };

    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            if (visited[i][j]) continue;
            if (!possible[i][j]) dfs(i, j);
        }
    }

    int ret = 0;
    for (int i= 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            if (possible[i][j])ret++;
        }
    }
    cout << ret << '\n';

}

int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("output.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    E();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}
