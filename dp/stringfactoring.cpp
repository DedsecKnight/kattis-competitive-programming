/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/stringfactoring
TAGS: dynamic programming, binary search, greedy
EXPLANATION: 

Observation #1: To determine whether 2 "consecutive" substrings can be combined together, one can precompute the lcp of every pair of suffixes to allow O(1) query with O(n^3) precomputation. 

Observation #2: It is possible to have a compression within a compression. Following is an example: 
"FOOFOOFOO" -> (FOO)^3 = (F(O)^2)^3
Let f(s) be length of string after applying compression on s, it can be shown that for the above example, f("FOOFOOFOO") = f("FOO") = 1 + f("O") = 2. Here, it can be inferred that dynamic programming wouldbe involved. 

Observation #3: Consider the problem of trying to find f(i, j), denoting the most optimal compression for the substring s[i..j] of string s. The solution to this problem can be computed from the following possible subproblems: 
1) Substring compression does not happen: f(i, j) = min(f(i + 1, j), f(i, j-1)) + 1 
2) Compressing substring s[i..k] where s[i..k] is repeated concatenation of some substring s[i..z] (i <= z <= k <= j): f(i, j) = f(i, z) + f(k+1, j)
3) Compressing substring s[k..j] where s[k..j] is repeated concatenation of some substring s[z..j] (i <= k <= z <= j): f(i, j) = f(i, k-1) + f(z, j)

Observation #4: Consider subproblem #2 described in observation #3, one can notice that if there are multiple k that works for a certain z, it is safe to greedily pick the largest k such that i <= k <= z. 
Similar logic can be applied for subproblem #3, but here we want to greedily pick the smallest k such that i <= k <= j. The optimal value for k can be determined using binary search (refer to code below for more details). 

Solution sketch: 
- Precompute lcp of every suffixes of the given string s. 
- For every substring of s, use the RMQ data structure (which is built from the computed LCP array) to efficiently determine the number of copies that follows it or precededs it. 
- Let f(i, j) be the solution to the substring s[i..j], where s is the given string. f(i, j) will be computed using dynamic programming using the subproblems defined in Observation #3 and #4, and the final answer will be f(0, |s|-1);

Time complexity: O(n^3 log(n))
END ANNOTATION
*/
#include <bits/stdc++.h>

using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")

#define len(a) static_cast<int>((a).size())
using ll = int64_t;
using ld = long double;
constexpr const int iinf = 1e9 + 7;
constexpr const ll inf = 1e18;
constexpr const ll mod = 998244353;
#define printDecimal(d) std::cout << std::setprecision(d) << std::fixed

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int n = len(s);
    vector<vector<int>> lcp(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; i + k < n && j + k < n && s[i + k] == s[j + k];
                 k++) {
                lcp[i][j]++, lcp[j][i]++;
            }
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, iinf));
    vector<vector<vector<int>>> forward(n, vector<vector<int>>(n)),
        backward(n, vector<vector<int>>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            auto sz = j - i + 1;
            // Determine all the copies that follows s[i..j] and keep track of start point for each copy
            for (int k = j + 1; k + sz <= n && lcp[i][k] >= sz; k += sz) {
                forward[i][j].push_back(k);
            }
            // Determine all copies that precedes s[i..j] and keep track of start point for each copy.
            for (int k = i - sz; k >= 0 && lcp[i][k] >= sz; k -= sz) {
                backward[i][j].push_back(k);
            }
        }
    }
    // Base case for dp
    for (int i = 0; i < n; i++)
        dp[i][i] = 1;
    for (int i = 1; i <= n; i++)
        dp[i][i - 1] = 0;

    // Solve recurrence relation
    for (int dia = 1; dia < n; dia++) {
        for (int j = dia; j < n; j++) {
            int i = j - dia;
            // Case #1: Substring compression does not happen in this case
            dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;

            // Case #2: Compressing substring starting from left endpoint
            for (int a = i; a < j; a++) {
                int sz = a - i + 1;
                if (forward[i][a].empty() || forward[i][a][0] > j - sz + 1)
                    continue;
                // Find the optimal k that works using binary search
                int idx = upper_bound(forward[i][a].begin(),
                                      forward[i][a].end(), j - sz + 1) -
                          forward[i][a].begin() - 1;
                dp[i][j] =
                    min(dp[i][j], dp[i][a] + dp[forward[i][a][idx] + sz][j]);
            }
            // Case #3: Compressing substring starting from right endpoint
            for (int a = j; a > i; a--) {
                if (backward[a][j].empty() || backward[a][j][0] < i)
                    continue;
                // Find the optimal k that works using binary search.
                int low = 0, high = len(backward[a][j]) - 1, best = -1;
                while (low <= high) {
                    auto mid = low + (high - low) / 2;
                    if (backward[a][j][mid] >= i) {
                        best = mid;
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }
                int b = backward[a][j][best];
                dp[i][j] =
                    min(dp[i][j], dp[a][j] + (b - 1 >= 0 ? dp[i][b - 1] : 0));
            }
        }
    }
    cout << dp[0][n - 1] << '\n';
}
