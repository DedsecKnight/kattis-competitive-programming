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

const int a[]{-1, 1, 0, 0};
const int b[]{0, 0, -1, 1};
 
void prayGod() {
    int t; cin >> t;
    while (t--) {
        int n,m; cin >> n >> m;
        vector<vector<char>> grid(n, vector<char>(m));
        pair<int, int> start, dest;
        for (int i = 0; i<n; i++) {
            string s; cin >> s;
            for (int j = 0; j<m; j++) {
                grid[i][j] = s[j];
                if (s[j] == 'R') start = make_pair(i, j);
                else if (s[j] == 'D') dest = make_pair(i, j);
            }
        }

        deque<pair<pair<int, int>, pair<int, int>>> q;
        int dist[n][m][4][2];

        for (int i = 0; i<n; i++) {
            for (int j = 0; j<m; j++) {
                for (int k = 0; k<4; k++) {
                    for (int z = 0; z<2; z++) {
                        if (i != start.first || j != start.second) dist[i][j][k][z] = iinf;
                        else dist[i][j][k][z] = 0;
                    } 
                }
            }
        }
        
        for (int k = 0; k<4; k++) {
            int new_x = start.first + a[k], new_y = start.second + b[k];
            if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1) || grid[new_x][new_y] == 'B') continue;
            dist[new_x][new_y][k + (k&1 ? -1 : 1)][0] = 1;
            q.emplace_back(make_pair(new_x, new_y), make_pair(k + (k&1 ? -1 : 1), 0));
        }

        while (!q.empty()) {
            pair<pair<int, int>, pair<int, int>> curr = q.front();
            q.pop_front();

            if (!curr.second.second) {
                for (int k = 0; k<4; k++) {
                    if (k == curr.second.first) continue;
                    int new_x = curr.first.first + a[k], new_y = curr.first.second + b[k];
                    if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1) || grid[new_x][new_y] == 'B') continue;

                    int step = (k/2 == curr.second.first/2);
                    int currDist = dist[curr.first.first][curr.first.second][curr.second.first][curr.second.second];

                    if (dist[new_x][new_y][k + (k&1 ? -1 : 1)][step] > currDist + 1) {
                        dist[new_x][new_y][k + (k&1 ? -1 : 1)][step] = currDist + 1;
                        q.emplace_back(make_pair(new_x, new_y), make_pair(k + (k&1 ? -1 : 1), step));
                    }
                }
            }
            else {
                for (int k = (!(curr.second.first/2))*2; k < 2 + (!(curr.second.first/2))*2; k++) {
                    if (k == curr.second.first) continue;
                    int new_x = curr.first.first + a[k], new_y = curr.first.second + b[k];

                    if (!inrange(new_x, 0, n-1) || !inrange(new_y, 0, m-1) || grid[new_x][new_y] == 'B') continue;
                    
                    int currDist = dist[curr.first.first][curr.first.second][curr.second.first][curr.second.second];
                    
                    if (dist[new_x][new_y][k + (k&1 ? -1 : 1)][0] > currDist + 1) {
                        dist[new_x][new_y][k + (k&1 ? -1 : 1)][0] = currDist + 1;
                        q.emplace_back(make_pair(new_x, new_y), make_pair(k + (k&1 ? -1 : 1), 0));
                    }
                }
            }
        }

        int ret = iinf;
        for (int k =0 ; k<4; k++) {
            for (int z = 0; z < 2; z++) ret = min(ret, dist[dest.first][dest.second][k][z]);
        }
        if (ret != iinf) cout << ret << '\n';
        else cout << -1 << '\n';

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
