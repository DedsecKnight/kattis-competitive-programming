#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#ifdef LLOCAL
#include "./debug.h"
#else
#define var(...)
#define debugArr(...)
#endif

using namespace std;

#define len(a) static_cast<int>((a).size())
#define present(c, x) (c.find(x) != c.end())
#define printDecimal(d) std::cout << std::setprecision(d) << std::fixed

using ll = long long;
using ull = unsigned long long;
using ld = long double;
constexpr const int iinf = 1e9 + 7;
constexpr const ll inf = 1e18;
static constexpr const ll mod = 1000000007;

template <typename Fun>
class y_combinator_result {
  Fun fun_;

 public:
  template <typename T>
  explicit y_combinator_result(T&& fun) : fun_{std::forward<T>(fun)} {}

  template <typename... ArgTs>
  decltype(auto) operator()(ArgTs&&... args) {
    return fun_(std::ref(*this), std::forward<ArgTs>(args)...);
  }
};

template <typename Fun>
decltype(auto) y_combinator(Fun&& fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

static constexpr const int SKIP = -2;

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<string> d(n);
  for (int i = 0; i < n; i++) {
    cin >> d[i];
  }
  vector<vector<vector<int>>> pref(m, vector<vector<int>>(10, vector<int>(n)));
  for (int i = 0; i < m; i++) {
    for (int dg = 0; dg < 10; dg++) {
      pref[i][dg][0] = (d[0][i] - '0' != dg);
      for (int j = 1; j < n; j++) {
        pref[i][dg][j] = pref[i][dg][j - 1] + (d[j][i] - '0' != dg);
      }
    }
  }
  vector<vector<vector<vector<int>>>> dp(
      m, vector<vector<vector<int>>>(
             n, vector<vector<int>>(n, vector<int>(10, -1))));
  vector<vector<vector<vector<int>>>> backtrack(
      m, vector<vector<vector<int>>>(
             n, vector<vector<int>>(n, vector<int>(10, -1))));
  auto solve = y_combinator([&](auto self, int i, int l, int r, int lb) -> int {
    if (l > r || i >= m) return 0;
    if (lb > 9) return iinf;
    if (dp[i][l][r][lb] != -1) return dp[i][l][r][lb];
    dp[i][l][r][lb] = self(i, l, r, lb + 1);
    backtrack[i][l][r][lb] = SKIP;
    for (int x = l; x <= r; x++) {
      auto lhs = self(i + 1, l, x, 0) + pref[i][lb][x] -
                 (l - 1 >= 0 ? pref[i][lb][l - 1] : 0);
      auto rhs = self(i, x + 1, r, lb + 1);
      if (lhs + rhs < dp[i][l][r][lb]) {
        dp[i][l][r][lb] = lhs + rhs;
        backtrack[i][l][r][lb] = x;
      }
    }
    return dp[i][l][r][lb];
  });
  auto construct_solution =
      y_combinator([&](auto self, int i, int l, int r, int lb) -> void {
        if (l > r || i >= m) return;
        if (backtrack[i][l][r][lb] == SKIP) {
          self(i, l, r, lb + 1);
        } else {
          for (int x = l; x <= backtrack[i][l][r][lb]; x++) {
            d[x][i] = static_cast<char>(lb + '0');
          }
          self(i + 1, l, backtrack[i][l][r][lb], 0);
          self(i, backtrack[i][l][r][lb] + 1, r, lb + 1);
        }
      });
  solve(0, 0, n - 1, 0);
  construct_solution(0, 0, n - 1, 0);
  for (int i = 0; i < n; i++) {
    cout << d[i] << '\n';
  }
}
