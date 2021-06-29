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
    int n; cin >> n;
    vector<int> map_idx(26, -1);

    vector<string> word(n); read(word, n);
    int index = 0;

    for (string w : word) {
        for (char c : w) {
            int idx = c-'A';
            if (map_idx[idx] == -1) map_idx[idx] = index++;
        }
    }

    vector<vector<bool>> possible(index, vector<bool>(10, true));
    for (int i = 0; i<n; i++) {
        int idx = word[i][0] - 'A';
        possible[map_idx[idx]][0] = false;
    }

    int sol_count = 0;

    function<void(vector<int>&)> check_perm = [&](vector<int> &mp) {
        for (int i = 0; i<index; i++) {
            if (!possible[i][mp[i]]) return;
        }
        ll add = 0, required = 0;
        for (int i = 0; i<n-1; i++) {
            ll curr = 0;
            for (char c : word[i]) {
                int idx = map_idx[c-'A'];
                curr = curr*10 + mp[idx];
            }
            add += curr;
        }
        for (char c : word.back()) {
            int idx = map_idx[c-'A'];
            required = required*10 + mp[idx];
        }
        sol_count += required == add;
    };

    function<void(int)> solve = [&](int mask) {
        vector<int> mp;
        for (int i = 0; i<10; i++) {
            if (mask & (1<<i)) mp.push_back(i);
        }
        do {
            check_perm(mp);
        } while (next_permutation(mp.begin(), mp.end()));
    };

    
    for (int mask = 0; mask<(1<<10); mask++) {
        if (__builtin_popcount(mask) != index) continue;
        solve(mask);
    }
    
    cout << sol_count << '\n';
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

