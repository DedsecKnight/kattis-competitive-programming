#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define printVerdict(verdict) cout << (verdict ? "YES" : "NO") << '\n'
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
void printArray(const vector<T> &arr) {
    for (int i = 0; i < len(arr); i++) {
        cout << arr[i] << " ";
    }
    cout << '\n';
}
template <class T>
void read(vector<T> &a, int n) {
    for (int i = 0; i < n; i++)
        cin >> a[i];
}
template <class T>
void read(T *a, int n) {
    for (int i = 0; i < n; i++)
        cin >> a[i];
}
template <class T>
void readIdx(vector<pair<T, int>> &a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
}
template <class T>
void printGrid(const vector<vector<T>> &grid) {
    for (int i = 0; i < len(grid); i++) {
        for (int j = 0; j < len(grid[i]); j++) {
            cout << grid[i][j] << " ";
        }
        cout << '\n';
    }
}
template <class T1, class T2>
void readPair(pair<T1, T2> &a) { cin >> a.first >> a.second; }

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

void prayGod() {
    string input;
    getline(cin, input);
    int n = stoi(input);

    vector<vector<int>> graph(n);
    vector<int> color(n, -1);

    function<vector<int>()> parse = [&]() {
        string curr = "";
        vector<int> ret;
        for (char c : input) {
            if (c == ' ') {
                ret.push_back(stoi(curr));
                curr = "";
            } else
                curr += c;
        }
        if (curr != "") ret.push_back(stoi(curr));
        return ret;
    };

    function<bool(int, int)> possible = [&](int idx, int max_color) {
        if (idx >= n) return true;
        int remain_color = (1 << max_color) - 1;
        for (int neighbor : graph[idx]) {
            if (color[neighbor] == -1) continue;
            remain_color &= ~(1 << color[neighbor]);
        }
        if (!remain_color) return false;
        for (int i = 0; i < max_color; i++) {
            if (remain_color & (1 << i)) {
                color[idx] = i;
                if (possible(idx + 1, max_color)) return true;
                color[idx] = -1;
            }
        }
        return false;
    };

    for (int i = 0; i < n; i++) {
        getline(cin, input);
        graph[i] = parse();
    }

    int low = 1, high = n, best = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        color.assign(n, -1);
        if (possible(0, mid)) {
            best = mid;
            high = mid - 1;
        } else
            low = mid + 1;
    }

    cout << best << '\n';
}

int main() {
    clock_t start = clock();

    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    if (EXTERNAL_INPUT)
        freopen(INPUT_FILE, "r", stdin);
    if (EXTERNAL_OUTPUT)
        freopen(OUTPUT_FILE, "w", stdout);

    prayGod();

    clock_t end = clock();

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME)
        debugDecimal(5) << time_taken << " s" << '\n';
}