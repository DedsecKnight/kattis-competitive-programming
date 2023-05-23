/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/islandtour
TAGS: bruteforce, implementation
EXPLANATION:
- Let t_ij[a][b] be boolean variable denoting whether i-th person and j-th person will not meet
if i starts at a and j starts at b (i != j). 
- Notice that a tuple (a, b, c) is valid if the following conditions hold: 
    + t01[a][b] = True
    + t02[a][c] = True
    + t12[b][c] = True
- To determine whether t_ij[a][b] holds for arbitrary i,j,a,b, we can determine whether there
exists a attraction k such that i and j will meet at k if they starts at a and b respectively. 
This can be checked by computing the interval of time during which each person will stay at location
k and check if the intervals overlap. 
- Refer to code comments for more details. 
END ANNOTATION
*/
#include <bits/stdc++.h>

using namespace std;

using ui = unsigned int;
using ll = long long;
using ld = long double;

template <typename K, typename V>
using umap = unordered_map<K, V>;

constexpr int iinf = 1e9 + 10;

#define null NULL
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)

int main() {
    int n; cin >> n;
    vector<int> d(n);
    for (int i = 0;i<n; i++) cin >> d[i];
    vector<vector<int>> t(3, vector<int>(n));
    for (int i = 0;i<3; i++) for (int j = 0; j<n; j++) cin >> t[i][j];
    vector<vector<bool>> t01(n, vector<bool>(n, false)), t02(n, vector<bool>(n, false)), t12(n, vector<bool>(n, false));
    vector<vector<int>> p, dist(n, vector<int>(n, iinf));
    // Compute total distance to travel from i to j circularly (n is wrapped to 1)
    for (int i = 0;i<n; i++) {
        dist[i][i] = 0;
        for (int j = i+1; j<i+n; j++) {
            dist[i][j%n] = dist[i][(j-1+n)%n] + d[(j-1+n)%n];
        }
    }
    // Compute prefix sum for time spent visiting a location
    for (int i = 0;i<3; i++) {
        p.emplace_back(begin(t[i]), end(t[i]));
        for (int j = 1; j<n; j++) p.back()[j] += p.back()[j-1];
    }
    function<int(int, int, int)> query = [&](int idx, int i, int j) -> int {
        if (i <= j) return (p[idx][j] - (i-1 >= 0 ? p[idx][i-1] : 0));
        return query(idx, i, n-1) + query(idx, 0, j);
    };
    auto compute_table = [&](vector<vector<bool>>& txy, int x, int y) {
        for (int i = 0;i<n; i++) {
            for (int j = 0;j<n; j++) {
                if (i == j) continue;
                txy[i][j] = true;
                for (int k = 0; k<n; k++) {
                    // Determine time interval at k for 0-th person
                    int li = dist[i][k] + (i!=k)*query(x, i, (k-1+n)%n);
                    int ri = li + t[0][k];
                    // Determine time interval at k for 1-st person
                    int lj = dist[j][k] + (j!=k)*query(y, j, (k-1+n)%n);
                    int rj = lj + t[1][k];
                    // Check if they overlap
                    if (ri > lj && rj > li) {
                        txy[i][j] = false;
                        break;
                    }
                }
            }
        }
    };
    compute_table(t01, 0, 1);
    compute_table(t02, 0, 2);
    compute_table(t12, 1, 2);
    // Determine if solution exists
    vector<int> ret;
    for (int i = 0;i<n; i++) {
        for (int j = 0; j<n; j++) {
            for (int k = 0; k<n; k++) {
                if (t01[i][j] && t02[i][k] && t12[j][k]) {
                    cout << (i+1) << " " << (j+1) << " " << (k+1) << '\n';
                    return; 
                }
            }
        }
    }
    cout << "impossible" << '\n';
}


