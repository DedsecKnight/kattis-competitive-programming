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

void prayGod() {
    int n; cin >> n;
    vector<vector<bool>> possible(n+1, vector<bool>(n+1, true));
    
    deque<pair<int, int>> q;
    q.emplace_back(1, n);
    
    while (!q.empty()) {
        q.emplace_back(-1, -1);
        pair<int, int> curr = q.front();
        q.pop_front();
        set<int> ask;
        while (curr.first != -1) {
            int start = curr.first, end = curr.second;
            int mid = start + (end - start)/2;

            for (int i = start; i<=mid; i++) ask.insert(i);
            
            if (start < mid) q.emplace_back(start, mid);
            if (mid+1 < end) q.emplace_back(mid+1, end);

            curr = q.front();
            q.pop_front();
        }
        
        set<int> turn_on, turn_off;
        for (int i = 1; i<=n; i++) turn_off.insert(i);
        
        string query = "ASK " + to_string(len(ask));

        for (int val : ask) query += " " + to_string(val);
        cout << query << endl;
        
        for (int i = 0; i<len(ask); i++) {
            int temp; cin >> temp;
            turn_off.erase(temp);
            turn_on.insert(temp);
        }

        for (int i = 1; i<=n; i++) {
            if (present(ask, i)) {
                for (int val : turn_off) possible[i][val] = false;
            }
            else {
                for (int val : turn_on) possible[i][val] = false;
            }
        }
    }

    vector<int> ret(n, -1);
    for (int i = 0; i<n; i++) {
        for (int j = 1; j<=n; j++) {
            if (possible[i+1][j]) {
                assert(ret[j-1] == -1);
                ret[j-1] = i+1;
            }
        }
    }
    string answer = "ANSWER";
    for (int i = 0; i<n; i++) {
        assert(ret[i] != -1);
        answer += " " + to_string(ret[i]);
    }
    cout << answer << endl;
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
