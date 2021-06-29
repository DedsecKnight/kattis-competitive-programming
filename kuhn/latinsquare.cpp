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

const char* INPUT_FILE = "output.txt";
const char* OUTPUT_FILE = "latin.txt";

void prayGod() {
    int n,z; cin >> n >> z;
    
    vector<bool> seen(n+1, false);

    vector<vector<int>> grid(n, vector<int>(n));

    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            cin >> grid[i][j];
            if (grid[i][j]) seen[grid[i][j]] = true;   
        }
    }

    vector<vector<int>> graph;
    vector<int> match;
    vector<bool> used;

    function<bool(int)> kuhn = [&](int curr) {
        if (used[curr]) return false;
        used[curr] = true;

        for (int neighbor : graph[curr]) {
            if (match[neighbor] == -1 || kuhn(match[neighbor])) {
                match[neighbor] = curr;
                return true;
            }
        }

        return false;
    };

    for (int val = 1; val <= n; val++) {
        if (seen[val]) continue;
        graph.assign(n, {});
        match.assign(n, -1);

        for (int i = 0; i<n; i++) {
            for (int j = 0; j<n; j++) {
                if (!grid[i][j]) graph[i].push_back(j);
            }
        }

        for (int i = 0; i<n; i++) {
            used.assign(n, false);
            kuhn(i);
        }

        for (int i = 0; i<n; i++) {
            if (match[i] == -1) {
                cout << "NO" << '\n';
                return;
            }
            grid[match[i]][i] = val;
        }
    }

    cout << "YES" << '\n';
    printGrid(grid);
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
