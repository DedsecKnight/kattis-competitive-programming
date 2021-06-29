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

umap<string, int> name_idx;
umap<int, string> idx_name;

struct SegmentTree {
    ll base_val;
    int arr_size;
    vector<pair<ll, int>> tree;
    vector<ll> lazy;
    
    SegmentTree(int n) {
        base_val = -inf, arr_size = n;
        int size = 1;
        while (size < n) size *= 2;
        size = 2*size + 1;
        for (int i = 0; i<size; i++) tree.emplace_back(0, -1);
        lazy.assign(size, 0);
        for (int i = 0; i<n; i++) update_idx(0, 0, arr_size-1, i);
    };

    pair<ll, int> eval(pair<ll, int> a, pair<ll, int> b) { 
        if (idx_name[a.second] == "") return b;
        if (idx_name[b.second] == "") return a;
        if (a.first != b.first) return (a.first > b.first ? a : b);
        return (idx_name[a.second] < idx_name[b.second] ? a : b);
    }
    
    void propagate(int idx, int curr_l, int curr_r) {
        if (lazy[idx]) {
            tree[idx].first += lazy[idx];
            
            if (curr_l != curr_r) {
                lazy[2*idx + 1] += lazy[idx];
                lazy[2*idx + 2] += lazy[idx];
            }
            
            lazy[idx] = 0;
        }
    }

    void update_idx(int idx, int curr_l, int curr_r, int i) {
        if (curr_l > curr_r || curr_r < i || curr_l > i) return;
        if (curr_l == curr_r) {
            tree[idx].second = i;
            return;
        }
        int mid = curr_l + (curr_r - curr_l)/2;
        if (inrange(i, curr_l, mid)) update_idx(idx*2 + 1, curr_l, mid, i);
        else update_idx(idx*2 + 2, mid+1, curr_r, i);
    }
    
    void update(int idx, int curr_l, int curr_r, int l, int r, ll val) {
        if (curr_l > curr_r) return;

        propagate(idx, curr_l, curr_r);

        if (curr_r < l || curr_l > r) return;
        
        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) {
            tree[idx].first += val;
            if (2*idx + 1 < len(lazy)) lazy[2*idx+1] += val;
            if (2*idx + 2 < len(lazy)) lazy[2*idx+2] += val;
            return;
        }

        int mid = curr_l + (curr_r - curr_l)/2;
        update(idx*2 + 1, curr_l, mid, l, r, val);
        update(idx*2 + 2, mid+1, curr_r, l, r, val);
        tree[idx] = eval(tree[2*idx + 1], tree[2*idx + 2]);
    }

    pair<ll, int> query(int idx, int curr_l, int curr_r, int l, int r) {
        if (curr_l > curr_r) return make_pair(base_val, -1);
        
        propagate(idx, curr_l, curr_r);

        if (curr_r < l || curr_l > r) return make_pair(base_val, -1);

        if (inrange(curr_l, l, r) && inrange(curr_r, l, r)) return tree[idx];

        int mid = curr_l + (curr_r - curr_l)/2;
        pair<ll, int> left = query(idx*2+1, curr_l, mid, l, r), right = query(idx*2+2, mid+1, curr_r, l, r);
        return eval(left, right);
    }

    void update(int l, int r, ll val) { update(0, 0, arr_size-1, l, r, val); }
    pair<ll, int> query(int l, int r) { return query(0, 0, arr_size-1, l, r);  }
};


void prayGod() {
    int n;
    ll k; cin >> n >> k;
    
    SegmentTree tree(n + 1);
    tree.update(0, n, -inf);

    int available_idx = 0, prev_time = 0;

    for (int i = 0; i<n; i++) {
        int op, t; cin >> op >> t;
        if (op == 1) {
            tree.update(0, n, (t - prev_time) * k);
            ll s; string name; 
            cin >> name >> s;
            name_idx[name] = available_idx;
            idx_name[available_idx] = name;
            pair<ll, int> curr = tree.query(available_idx, available_idx);
            tree.update(available_idx, available_idx, s - curr.first);
            available_idx++;
            prev_time = t;
        }
        else if (op == 2) {
            pair<ll, int> best = tree.query(0, n);
            if (best.first < 0) cout << "doctor takes a break" << '\n';
            else {
                cout << idx_name[best.second] << '\n';
                tree.update(best.second, best.second, -inf - best.first);
                name_idx.erase(idx_name[best.second]);
                idx_name.erase(best.second);
            }
        }
        else {
            string name; cin >> name;
            if (!present(name_idx, name)) continue;
            int idx = name_idx[name];
            pair<ll, int> curr = tree.query(idx, idx);
            tree.update(idx, idx, -inf - curr.first);
            name_idx.erase(name);
            idx_name.erase(idx);
        }
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
