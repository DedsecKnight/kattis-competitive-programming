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

const int x[]{-1,1,0,0};
const int y[]{0, 0, -1, 1};


void G() {
    int r,c,n; cin >> r >> c >> n;
    
    vector<vector<int>> grid(r, vector<int>(c));
    vector<vector<bool>> pass(r, vector<bool>(c, false));

    for (int i = 0; i<r; i++) {
        for (int j = 0; j<c; j++) cin >> grid[i][j];
    }

    for (int i = 1; i<r-1; i++) {
        for (int j = 1; j<c-1; j++) {
            bool valid = true;
            int max_hori = -iinf, min_vert = iinf;
            for (int k = 0; k<4 && valid; k++) {
                int new_x = i+x[k], new_y = j+y[k];
                if (grid[new_x][new_y] == -1) valid = false;
                else if (k < 2) min_vert = min(min_vert, grid[new_x][new_y]);
                else max_hori = max(max_hori, grid[new_x][new_y]);
            }
            if (!valid) continue;
            if (max_hori < grid[i][j] && min_vert > grid[i][j]) pass[i][j] = true;
        }
    }

    vector<vector<int>> curr_dp(r, vector<int>(c, iinf));
    
    for (int curr_pass = 0; curr_pass<=n; curr_pass++) {
        vector<vector<int>> prev_dp = curr_dp;
        for (int i = 0; i<r; i++) {
            for (int j = 0; j<c; j++) curr_dp[i][j] = iinf;
        }
        for (int i = 0; i<r && curr_pass==0; i++) {
            if (grid[i][0] == -1) continue;
            curr_dp[i][0] = grid[i][0];
        }
        for (int j = 1; j<c; j++) {
            for (int i = 0; i<r; i++) {
                if (grid[i][j] == -1) continue;
                for (int k = 0; k<3; k++) {
                    int new_x = i+x[k], new_y = j-1;
                    if (!inrange(new_x, 0, r-1) || !inrange(new_y, 0, c-1) || grid[new_x][new_y] == -1) continue;
                    if (pass[i][j]) curr_dp[i][j] = min(curr_dp[i][j], prev_dp[new_x][new_y] + grid[i][j]);
                    else curr_dp[i][j] = min(curr_dp[i][j], curr_dp[new_x][new_y] + grid[i][j]);
                }
            }
        }
    }

    int best = iinf;
    for (int i = 0; i<r; i++) best = min(best, curr_dp[i][c-1]);
    if (best != iinf) cout << best << '\n';
    else cout << "impossible" << '\n';
}

int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("output.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    G();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}
