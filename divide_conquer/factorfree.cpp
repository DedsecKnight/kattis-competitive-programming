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

void F() {
    int n; cin >> n;
    vector<int> a(n);
    read(a, n);

    vector<int> parent(n, -1);
    vector<set<int>> factor(n);
    
    const int ALL_PRIME = 1e4 + 1;
    vector<bool> is_prime(ALL_PRIME, true);
    is_prime[0] = is_prime[1] = false;

    vector<int> prime;

    for (int i = 2; i<ALL_PRIME; i++) {
        if (!is_prime[i]) continue;
        prime.push_back(i);
        for (int j = i*2; j<ALL_PRIME; j+=i) is_prime[j] = false;
    }

    for (int i = 0; i<n; i++) {
        int temp = a[i];
        for (int d : prime) {
            if (d*d > temp) break;
            if (temp % d == 0) {
                factor[i].insert(d);
                while (temp % d == 0) temp /= d;
            }
        }
        if (temp > 1) factor[i].insert(temp);
    }

    vector<pair<int, int>> intervals(n, make_pair(0, n-1));

    umap<int, int> pref, suff;
    for (int i = 0; i<n; i++) {
        for (int f : factor[i]) {
            if (present(pref, f)) intervals[i].first = max(intervals[i].first, pref[f] + 1);
            pref[f] = i;
        }
    }
    for (int i = n-1; i>=0; i--) {
        for (int f : factor[i]) {
            if (present(suff, f)) intervals[i].second = min(intervals[i].second, suff[f] - 1);
            suff[f] = i;
        }
    }
    
    function<bool(int, int, int)> solve = [&](int curr_root, int left, int right) {
        if (left > right) return true;
        if (left == right) {
            parent[left] = curr_root;
            return true;
        }
        
        int ptr1 = left, ptr2 = right;
        while (ptr1 <= ptr2) {
            if (intervals[ptr1].first <= left && intervals[ptr1].second >= right) {
                if (solve(ptr1+1, left, ptr1-1) && solve(ptr1+1, ptr1+1, right)) {
                    parent[ptr1] = curr_root;
                    return true;
                }
                return false;
            }
            if (ptr2 != ptr1 && intervals[ptr2].first <= left && intervals[ptr2].second >= right) {
                if (solve(ptr2+1, left, ptr2-1) && solve(ptr2+1, ptr2+1, right)) {
                    parent[ptr2] = curr_root;
                    return true;
                }
                return false;
            }
            ptr1++, ptr2--;
        }
        return false;
    };
    bool possible = solve(0, 0, n-1);
    if (!possible) {
        cout << "impossible" << '\n';
        return;
    } 
    printArray(parent);
}

int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("output.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    F();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}

/*
Tips to solve this problem
- Use Sieve to find all necessary primes
- In recursion construction, instead of pruning from one side, do it from both side simultaneously
- If there are multiple candidate for a range, it does not matter which one should be chosen
*/