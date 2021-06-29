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
    int b,n,e; cin >> b >> n >> e;
    ll sb, sn, se; cin >> sb >> sn >> se;
    int boat_cnt = (b+n+e)/2;

    vector<ll> c(boat_cnt);
    read(c, boat_cnt);
    
    sort(c.begin(), c.end());

    ll ret = 0;
    ll low = 0, high = inf;

    while (low <= high) {
        ll mid = low + (high - low)/2;
        bool possible = true;

        map<ll, int> cnt;
        vector<ll> remain;

        if (e) {remain.push_back(se); cnt[se] = e;}
        if (b) {remain.push_back(sb); cnt[sb] = b;}
        if (n) {remain.push_back(sn); cnt[sn] = n;}

        sort(remain.begin(), remain.end());

        for (int i =0; i<boat_cnt; i++) {
            bool found = false;
            for (int j = 0; j<len(remain) && !found; j++) {
                if (cnt[remain[j]] > 1 && remain[j]*2*c[i] >= mid) {
                    cnt[remain[j]] -= 2;
                    found = true;
                    if (!cnt[remain[j]]) remain.erase(remain.begin() + j);
                    break;
                }
                for (int k = j+1; k<len(remain) && !found; k++) {
                    if ((remain[j] + remain[k]) * c[i] >= mid) {
                        found = true;
                        cnt[remain[j]]--;
                        cnt[remain[k]]--;
                        bool removeJ = !cnt[remain[j]];
                        if (removeJ) remain.erase(remain.begin() + j);
                        if (!cnt[remain[k-removeJ]]) remain.erase(remain.begin() + k - removeJ);
                        break;
                    }
                }
            }
            if (!found) {
                possible = false;
                break;
            }
        }

        if (possible) ret = mid, low = mid+1;
        else high = mid-1;
    }

    cout << ret << '\n';
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