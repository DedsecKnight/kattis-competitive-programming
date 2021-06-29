#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
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

struct SuffixArray {
    string s;
    vector<int> sorted_suffix, lcp, rank;
    int n;
    SuffixArray(string sc) {
        s = sc + "$";
        n = len(s);

        sorted_suffix.resize(n);
        lcp.resize(n);
        rank.resize(n);

        compute_init_state();
        
        vector<pair<int, pair<int, int>>> transition(n), temp_transition(n);
        int k = 1;
        while (k < n) {
            for (int i= 0; i<n; i++) {
                transition[i].first = i;
                transition[i].second = make_pair(rank[i], rank[(i + k) % n]);
            }
            count_sort(transition, temp_transition);
            assign_rank(transition);
            k *= 2;
        }

        for (int i= 0; i<n; i++) sorted_suffix[i] = transition[i].first;
    }

    void compute_init_state() {
        for (int i = 0; i<n; i++) sorted_suffix[i] = i;
        sort(sorted_suffix.begin(), sorted_suffix.end(), [&](int a, int b) {
            if (s[a] != s[b]) return s[a] < s[b];
            return a < b;
        });
        rank[sorted_suffix[0]] = 0;
        for (int i = 1; i<n; i++) {
            if (s[sorted_suffix[i]] == s[sorted_suffix[i-1]]) rank[sorted_suffix[i]] = rank[sorted_suffix[i-1]];
            else rank[sorted_suffix[i]] = rank[sorted_suffix[i-1]] + 1;
        }
    }

    void assign_rank(vector<pair<int, pair<int, int>>> &transition) {
        rank[transition[0].first] = 0;
        for (int i = 1; i<n; i++) {
            if (transition[i].second == transition[i-1].second) rank[transition[i].first] = rank[transition[i-1].first];
            else rank[transition[i].first] = rank[transition[i-1].first] + 1;
        }
    } 
    
    void compute_lcp() {
        int k = 0;
        for (int i = 0; i<n-1; i++) {
            int prev = sorted_suffix[rank[i]-1];
            while (s[i+k] == s[prev + k]) k++;
            lcp[rank[i]] = k;
            k = max(k-1, 0); 
        }
        lcp.erase(lcp.begin());
    }

    void count_sort(vector<pair<int, pair<int, int>>> &transition, vector<pair<int, pair<int, int>>> &temp_transition) {
        vector<int> count(n);
        for (int i = 0; i<n; i++) count[transition[i].second.second]++;
        count[0]--;
        for (int i = 1; i<n; i++) count[i] += count[i-1];
        for (int i = n-1; i>=0; i--) {
            temp_transition[count[transition[i].second.second]--] = transition[i];
        }

        count.assign(n, 0);
        for (int i = 0; i<n; i++) count[temp_transition[i].second.first]++;
        count[0]--;
        for (int i = 1; i<n; i++) count[i] += count[i-1];
        for (int i = n-1; i>=0; i--) {
            transition[count[temp_transition[i].second.first]--] = temp_transition[i];
        }
    }

};

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
        tree.assign(size, 0);
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
    string s; cin >> s;
    int n = len(s);

    SuffixArray suff(s);
    suff.compute_lcp();
    
    SegmentTree<int> tree(n, iinf);
    for (int i = 0; i<n; i++) {
        tree.update(i, i, suff.lcp[i]);
    }
    
    int q; cin >> q;
    while (q--) {
        int left, right; cin >> left >> right;
        left = suff.rank[left], right = suff.rank[right];
        if (left > right) swap(left, right);
        cout << tree.query(left, right-1) << '\n';
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
    
    double time_taken = double(end - start) / 1000.0;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " ms" << '\n';
} 
