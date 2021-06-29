#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define printVerdict(verdict) cout << (verdict ? "yes": "no") << '\n'
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

void J() {
    int n; cin >> n;
    vector<pair<int, pair<int, int>>> faucet(n);
    for (int i = 0; i<n; i++) {
        cin >> faucet[i].first;
        readPair(faucet[i].second);
    }
    
    int min_global_flow = 0, max_global_flow = 0;
    ll min_target = 0, max_target = 0;

    for (int i = 0; i<n; i++) {
        min_global_flow += faucet[i].second.first;
        max_global_flow += faucet[i].second.second;

        min_target += ll(faucet[i].first) * faucet[i].second.first;
        max_target += ll(faucet[i].first) * faucet[i].second.second;
    }

    sort(faucet.begin(), faucet.end(), [&](pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
        return a.first < b.first;
    });
    
    int t; cin >> t;
    while (t--) {
        int required_temperature, required_flow;
        cin >> required_temperature >> required_flow;
        if (!inrange(required_flow, min_global_flow, max_global_flow)) {
            cout << "no" << '\n';
            continue;
        }
        ll target = ll(required_temperature) * required_flow;
        
        // Find min possible temperature
        ll min_possible = min_target;
        int flow_need = required_flow - min_global_flow;
        for (int i = 0; i<n && flow_need > 0; i++) {
            int possible_delta = min(flow_need, faucet[i].second.second - faucet[i].second.first);
            min_possible += ll(possible_delta) * faucet[i].first;
            flow_need -= possible_delta;
        }

        // Find max possible temperature
        ll max_possible = max_target;
        int flow_redundant = max_global_flow - required_flow;
        for (int i = 0; i<n && flow_redundant > 0; i++) {
            int possible_delta = min(flow_redundant, faucet[i].second.second - faucet[i].second.first);
            max_possible -= ll(possible_delta) * faucet[i].first;
            flow_redundant -= possible_delta;
        }

        // Check valid temperature
        printVerdict(inrange(target, min_possible, max_possible));
    }

}

int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen("output.txt", "r", stdin);
    if (EXTERNAL_OUTPUT) freopen("output.txt", "w", stdout);
    
    J();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}
