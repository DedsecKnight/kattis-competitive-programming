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
    int g; cin >> g;

    function<int(const vector<int>&, int)> search_max = [&](const vector<int> &arr, int target) {
        int low = 0, high = len(arr)-1, best = -1;
        while (low <= high) {
            int mid = low + (high - low)/2;
            if (arr[mid] <= target) {
                best = mid;
                low = mid+1;
            }
            else high = mid-1;
        }
        if (best == -1 || arr[best] != target) return -1;
        return best;
    };

    function<int(const vector<int>&, int)> search_min = [&](const vector<int> &arr, int target) {
        int low = 0, high = len(arr)-1, best = -1;
        while (low <= high) {
            int mid = low + (high - low)/2;
            if (arr[mid] >= target) {
                best = mid;
                high = mid-1;
            }
            else low = mid+1;
        }
        if (best == -1 || arr[best] != target) return -1;
        return best;
    };

    for (int zzz = 1; zzz<=g; zzz++) {
        int m; cin >> m;
        
        vector<int> left, right;
        for (int i = 0; i<m; i++) {
            int a; cin >> a;
            if (i < m/2) left.push_back(a);
            else right.push_back(a);
        }

        int n,t; cin >> n >> t;
        int l_size = len(left), r_size = len(right);

        vector<vector<int>> possible(l_size + 1);
        for (int mask = 0; mask<(1<<l_size); mask++) {
            int curr_sum = 0;
            for (int i = 0; i<l_size; i++) {
                if (mask & (1<<i)) curr_sum += left[i];
            }
            possible[__builtin_popcount(mask)].push_back(curr_sum);
        }

        int win = 0, lose = 0;

        for (int i = 0; i<=l_size; i++) sort(possible[i].begin(), possible[i].end());
        for (int mask = 0; mask < (1<<r_size); mask++) {
            int curr_sum = 0;
            for (int i = 0; i<r_size; i++) {
                if (mask & (1<<i)) curr_sum += right[i];
            }
            int left_size = n - __builtin_popcount(mask);
            if (!inrange(left_size, 0, l_size)) continue;
            
            int left_idx = search_min(possible[left_size], t - curr_sum);
            if (left_idx == -1) {
                lose += len(possible[left_size]);
                continue;
            }
            int right_idx = search_max(possible[left_size], t - curr_sum);

            int curr_win = right_idx - left_idx + 1;

            win += curr_win;
            lose += len(possible[left_size]) - curr_win;

        }

        cout << "Game " << zzz << " -- " << win << " : " << lose << '\n';

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

