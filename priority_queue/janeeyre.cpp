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

void parse1(string input, string &title, ll &time) {
    if (input == "") return;
    string curr = "";
    int idx = 1;
    while (idx < len(input) && input[idx] != '"') {
        curr += input[idx];
        idx++;
    }
    idx+=2;
    title = curr, curr = "";
    while (idx < len(input)) {
        curr += input[idx];
        idx++;
    }
    time = stoll(curr);
}

void parse2(string input, string &title, ll &read_time, ll &appear_time) {
    if (input == "") return;
    string curr = "";
    int idx = 0;
    while (idx < len(input) && input[idx] != ' ') {
        curr += input[idx];
        idx++;
    }
    appear_time = stoll(curr);
    curr = "";
    idx+=2;
    while (idx < len(input) && input[idx] != '"') {
        curr += input[idx];
        idx++;
    }
    idx+=2;
    title = curr, curr = "";
    while (idx < len(input)) {
        curr += input[idx];
        idx++;
    }
    read_time = stoll(curr);
    //cerr << var(appear_time) << var(title) << var(read_time) << '\n';
}

void prayGod() {
    int n,m,k; cin >> n >> m >> k;
    cin.ignore();
    string target = "Jane Eyre";
    auto comp = [&](pair<string, ll> a, pair<string, ll> b) {
        return a.first < b.first;
    };
    set<pair<string, ll>, decltype(comp)> stack(comp);
    for (int i = 0; i<n; i++) {
        string title, input;
        ll time;
        getline(cin, input);
        parse1(input, title, time);
        stack.insert(make_pair(title, time));
    }
    stack.insert(make_pair(target, k));
    vector<pair<ll, pair<string, ll>>> friend_book;
    for (int i = 0; i<m; i++) {
        ll appear_time, read_time;
        string input, title;
        getline(cin, input);
        parse2(input, title, read_time, appear_time);
        friend_book.emplace_back(appear_time, make_pair(title, read_time));
    }
    sort(friend_book.begin(), friend_book.end());
    ll curr_time = 0;
    for (int i = 0; i<len(friend_book); i++) {
        while (!stack.empty() && curr_time < friend_book[i].first) {
            curr_time += stack.begin()->second;
            if (stack.begin()->first == target) {
                cout << curr_time << '\n';
                return;
            }
            stack.erase(stack.begin());
        }
        stack.insert(friend_book[i].second);
    }
    while (!stack.empty()) {
        curr_time += stack.begin()->second;
        if (stack.begin()->first == target) {
            cout << curr_time << '\n';
            return;
        }
        stack.erase(stack.begin());
    }
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
