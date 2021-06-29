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

template<class T>
struct SegmentTree {
    T base_val;
    int arr_size;
    vector<T> tree, lazy;
    
    SegmentTree(int n, T base) {
        base_val = base, arr_size = n;
        int size = 1;
        while (size < n) size *= 2;
        size = 2*size + 1;
        tree.assign(size, base);
        lazy.assign(size, 0);
    };

    T eval(T a, T b) { return min(a, b); }
    
    void propagate(int idx, int curr_l, int curr_r) {
        if (lazy[idx]) {
            tree[idx] += lazy[idx];
            
            if (curr_l != curr_r) {
                lazy[2*idx + 1] += lazy[idx];
                lazy[2*idx + 2] += lazy[idx];
            }
            
            lazy[idx] = 0;
        }
    }

    void update(int idx, int curr_l, int curr_r, int l, int r, T val) {
        if (curr_l > curr_r) return;

        propagate(idx, curr_l, curr_r);

        if (curr_r < l || curr_l > r) return;
        
        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) {
            tree[idx] += val;
            if (2*idx + 1 < len(lazy)) lazy[2*idx+1] += val;
            if (2*idx + 2 < len(lazy)) lazy[2*idx+2] += val;
            return;
        }

        int mid = curr_l + (curr_r - curr_l)/2;
        update(idx*2 + 1, curr_l, mid, l, r, val);
        update(idx*2 + 2, mid+1, curr_r, l, r, val);
        tree[idx] = eval(tree[2*idx + 1], tree[2*idx + 2]);
    }

    T query(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r) return base_val;
        
        propagate(idx, curr_l, curr_r);

        if (curr_r < l || curr_l > r) return base_val;

        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) return tree[idx];

        int mid = curr_l + (curr_r - curr_l)/2;
        T left = query(idx*2+1, curr_l, mid, l, r), right = query(idx*2+2, mid+1, curr_r, l, r);
        return eval(left, right);
    }

    void update(int l, int r, T val) { update(0, 0, arr_size-1, l, r, val); }
    T query(int l, int r) { return query(0, 0, arr_size-1, l, r);  }
};



void prayGod() {
    int n; cin >> n;
    vector<int> a(n);
    read(a, n);
    
    umap<int, int> last_seen;
    vector<int> next(n, -1), prev(n, -1);

    for (int i = n-1; i>=0; i--) {
        if (present(last_seen, a[i])) next[i] = last_seen[a[i]];
        last_seen[a[i]] = i; 
    }

    SegmentTree<int> tree(n+1, 1e9 + 10);
    vector<int> curr_tree(n+1, 1e9 + 10);

    for (int i = 0; i<n; i++) {
        if (next[i] == -1) continue;
        tree.update(i, i, a[i] - curr_tree[i]);
        curr_tree[i] = a[i];
        prev[next[i]] = i;
    }

    pair<int, int> ret = {1e9, 1e9};

    for (int i = 0; i<n; i++) {
        if (prev[i] == -1) continue;
        int best = tree.query(prev[i] + 1, i-1);
        if (best != 1e9 + 10) {
            pair<int, int> new_candidate = make_pair(a[i], best);
            if (ret > new_candidate) ret = new_candidate;
        }
        tree.update(prev[i], prev[i], 1e9 + 10 - curr_tree[prev[i]]);
        curr_tree[prev[i]] = 1e9 + 10;
    }
    
    if (ret.first == 1e9) {
        cout << -1 << '\n';
        return;
    }

    printPair(ret);
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