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

const int a[]{-1, 1, 1, -1};
const int b[]{1, -1, 1, -1};

void prayGod() {
    vector<vector<int>> dist(64, vector<int>(64, iinf)), next(64, vector<int>(64, -1));
    for (int i =0; i<64; i++) dist[i][i] = 0, next[i][i] = i;

    for (int i = 0; i<64; i++) {
        int x = i/8, y = i%8;
        for (int z = 1; z <= 8; z++) {
            for (int k = 0; k<4; k++) {
                int new_x = x + z*a[k], new_y =  y+z*b[k];
                if (!inrange(new_x, 0, 7) || !inrange(new_y, 0, 7)) continue;
                int compressed = new_x * 8 + new_y;
                dist[i][compressed] = dist[compressed][i] = 1;
                next[i][compressed] = compressed;
                next[compressed][i] = i;
            }
        }
    }

    for (int k = 0; k<64; k++) {
        for (int i = 0; i<64; i++) {
            for (int j = 0; j<64; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    int t; cin >> t;
    while (t--) {
        
        char col;
        int r,c; cin >> col >> r;
        r = 8- r, c = int(col - 'A');
        int dr, dc; cin >> col >> dr;
        dr = 8-dr, dc = int(col - 'A');

        if (dist[r*8+c][dr*8+dc] == iinf) {
            cout << "Impossible" << '\n';
            continue;
        }

        vector<char> ret;
        function<void(int, int)> construct_path = [&](int u, int v) {
            if (next[u][v] == -1) return;

            ret.push_back(char(u%8+'A'));
            ret.push_back(char(8-(u/8)+'0'));
            
            while (u != v) {
                u = next[u][v];
                ret.push_back(char(u%8+'A'));
                ret.push_back(char(8-(u/8)+'0'));
            }
        };

        construct_path(r*8+c, dr*8 + dc);
        cout << dist[r*8+c][dr*8+dc] << " "; 
        printArray(ret);


    }

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