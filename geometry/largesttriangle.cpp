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

enum Orientation { CCL, CW, CCW };
Orientation findOrientation(pair<ld, ld> a, pair<ld, ld> b, pair<ld, ld> c) {
	ld ret = (b.second - a.second) * (c.first - b.first) - (b.first - a.first) * (c.second - b.second);
	if (abs(ret) == 0.0) return CCL;
	return (ret > 0 ? CW : CCW);
}

void prayGod() {
    int n; cin >> n;
    
    set<pair<ld, ld>> seen;
    vector<pair<ld, ld>> points;

    for (int i = 0; i<n; i++) {
        pair<ld, ld> temp; readPair(temp);
        if (present(seen, temp)) continue;
        points.push_back(temp);
        seen.insert(temp);
    }

    n = len(points);

    /*  BEGIN CONVEX HULL */
    sort(points.begin(), points.end(), [&](pair<ld, ld> a, pair<ld, ld> b){
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });

    pair<ld, ld> left = points[0], right = points[n-1];
    vector<pair<ld, ld>> upper{left}, lower{left};

    for (int i = 1; i<n; i++) {
        Orientation curr = findOrientation(left, points[i], right);
        if (i == n-1 || curr == CW) {
            if (len(upper) >= 2) {
                curr = findOrientation(upper[len(upper)-2], upper.back(), points[i]);
                while (len(upper) >= 2 && curr != CW) {
                    upper.pop_back();
                    if (len(upper) >= 2) curr = findOrientation(upper[len(upper)-2], upper.back(), points[i]);
                }
            }
            upper.push_back(points[i]);
        }
        if (i == n-1 || curr == CCW) {
            if (len(lower) >= 2) {
                curr = findOrientation(lower[len(lower)-2], lower.back(), points[i]);
                while (len(lower) >= 2 && curr != CCW) {
                    lower.pop_back();
                    if (len(lower) >= 2) curr = findOrientation(lower[len(lower)-2], lower.back(), points[i]);
                }
            }
            lower.push_back(points[i]);
        }
    }
    for (int i = len(upper)-2; i>0; i--) lower.push_back(upper[i]);
    
    /* END CONVEX HULL */

    // COMPUTE AREA OF THE TRIANGLE FROM POINT P[i], P[j], P[k]
    function<ld(int, int, int)> area = [&](int i, int j, int k) {
        ld r = 0.0;
        r += lower[i].first * lower[j].second + lower[j].first * lower[k].second + lower[k].first * lower[i].second;
        r -= lower[i].second * lower[j].first + lower[j].second * lower[k].first + lower[k].second * lower[i].first;
        return fabs(r)/2.0;
    };

    n = len(lower);
    
    ld ret = 0;

    // COMPUTE LARGEST AREA IN CONVEX HULL (can read this for more details: https://arxiv.org/pdf/1705.11035.pdf)
    for (int i = 0; i<n; i++) {
        int ptr1 = (i+1)%n, ptr2 = (i+2)%n;
        ret = max(ret, area(i, ptr1, ptr2));
        while (true) {
            ld next_area = area(i, ptr1, (ptr2+1)%n), curr_area = area(i, ptr1, ptr2);
            while (ptr2 && next_area >= curr_area) {
                ptr2 = (ptr2 + 1) % n;
                curr_area = next_area;
                next_area = area(i, ptr1, (ptr2 + 1)%n);
            }
            ret = max(ret, curr_area);
            if (!ptr2) break;
            ptr1 = (ptr1 + 1)%n;
        }        
    }

    printDecimal(5) << ret << '\n';
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
