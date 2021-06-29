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
#define printCase(_) cout << "Case #" << (_) << ": "

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
 
const char* INPUT_FILE = "input.txt";
const char* OUTPUT_FILE = "output.txt";


void prayGod() {
    int n,m,k; cin >> n >> m >> k;

    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<int>> pref(n, vector<int>(m));

    for (int i = 0; i<n; i++) {
        string s; cin >> s;
        
        pref[i][0] = s[0] == '*';
        grid[i][0] = s[0];

        for (int j = 1; j<m; j++) {
            grid[i][j] = s[j];
            pref[i][j] = pref[i][j-1] + (s[j] == '*');
        }
    }

    pair<int, int> tleft{-1, -1}, bright{-1, -1};
    int curr_best = 0;

    for (int i = 0; i+k <= n; i++) {
        for (int j = k-1; j<m; j++) {
            int top = i+1, bottom = i+k-2;
            int left = j-k+2, right = j-1;

            int curr = 0;
            for (int z = top; z<=bottom; z++) {
                curr += max(0, pref[z][right] - pref[z][left-1]);
            }

            if (curr > curr_best) {
                tleft = {top-1, left-1};
                bright = {bottom+1, right+1};
                curr_best = curr;
            }
        }
    }

    grid[tleft.first][tleft.second] = grid[tleft.first][bright.second] = grid[bright.first][tleft.second] = grid[bright.first][bright.second] = '+';
    for (int i = tleft.first+1; i < bright.first; i++) {
        grid[i][tleft.second] = grid[i][bright.second] = '|';
    }

    for (int i = tleft.second+1; i<bright.second; i++) {
        grid[tleft.first][i] = grid[bright.first][i] = '-';
    }

    cout << curr_best << '\n';
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) cout << grid[i][j];
        cout << '\n';
    }

}
 
int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen(INPUT_FILE, "r", stdin);
    if (EXTERNAL_OUTPUT) freopen(OUTPUT_FILE, "w", stdout);
    
    prayGod();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}

