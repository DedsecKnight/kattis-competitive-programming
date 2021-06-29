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
    vector<vector<char>> grid(4, vector<char>(4)), end_grid(4, vector<char>(4));

    for (int i = 0; i<4; i++) {
        string s; cin >> s;
        for (int j = 0; j<4; j++) grid[i][j] = s[j];
    }

    end_grid[0].assign(4, 'R');
    end_grid[1].assign(4, 'G');
    end_grid[2].assign(4, 'B');
    end_grid[3].assign(4, 'Y');

    function<void(vector<vector<char>>&, int, int)> move_row = [&](vector<vector<char>>& state, int row_idx, int cycle_time) {
        for (int i = 0; i<cycle_time; i++) {
            char temp = state[row_idx][0];
            for (int j = 1; j<5; j++) {
                int idx = j%4;
                swap(temp, state[row_idx][idx]);
            }
        }
    };

    function<void(vector<vector<char>>&, int, int)> move_col = [&](vector<vector<char>>& state, int col_idx, int cycle_time) {
        for (int i = 0; i<cycle_time; i++) {
            char temp = state[0][col_idx];
            for (int j = 1; j<5; j++) {
                int idx = j%4;
                swap(temp, state[idx][col_idx]);
            }
        }
    };

    int ret = 1e9 + 10;

    function<void(
        map<vector<vector<char>>, int>&, 
        map<vector<vector<char>>, int>&, 
        deque<vector<vector<char>>>&,
        bool&
    )> bfs = [&](
        map<vector<vector<char>>, int>& d1, 
        map<vector<vector<char>>, int>&d2, 
        deque<vector<vector<char>>>&q,
        bool &found
    ) {
        vector<vector<char>> curr = q.front(); q.pop_front();
        if (present(d2, curr)) {
            found = true;
            ret = min(ret, d2[curr] + d1[curr]);
        }

        int curr_dist = d1[curr];

        for (int i = 0; i<4; i++) {
            // 2 possible ways to turn a row
            move_row(curr, i, 1);
            if (!present(d1, curr)) {
                q.push_back(curr);
                d1[curr] = curr_dist + 1;
            }
            move_row(curr, i, 2);
            if (!present(d1, curr)) {
                q.push_back(curr);
                d1[curr] = curr_dist + 1;
            }
            move_row(curr, i, 1);

            // 2 possible ways to turn a column
            move_col(curr, i, 1);
            if (!present(d1, curr)) {
                q.push_back(curr);
                d1[curr] = curr_dist + 1;
            }
            move_col(curr, i, 2);
            if (!present(d1, curr)) {
                q.push_back(curr);
                d1[curr] = curr_dist + 1;
            }
            move_col(curr, i, 1);

        }

    };

    map<vector<vector<char>>, int> dist, dist_end; 
    dist[grid] = dist_end[end_grid] = 0;

    deque<vector<vector<char>>> qs{grid}, qe{end_grid};
    int temp = 0;

    while (!qs.empty() && !qe.empty()) {
        bool found = false;
        bfs(dist, dist_end, qs, found);
        bfs(dist_end, dist, qe, found);
        if (found){
            if (temp == 5) {
                cout << ret << '\n';
                return;
            }
            else temp++;
        }
    }
    
    cout << ret << '\n';
    

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

