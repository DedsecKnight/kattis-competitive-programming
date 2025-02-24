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
constexpr const ll inf = numeric_limits<ll>::max();
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

using bs = bitset<5001>;

int main() {
  int n;
  int impl, think;
  cin >> n >> impl >> think;
  vector<pair<pair<int, int>, pair<int, int>>> problems;
  for (int i = 0; i < n; i++) {
    int il, ih, tl, th;
    cin >> il >> ih >> tl >> th;
    if (ih < impl || th < think) {
      problems.emplace_back(make_pair(-1, -1), make_pair(-1, -1));
    } else {
      il = max(il - impl, 0);
      ih = max(ih - impl, 0);
      tl = max(tl - think, 0);
      th = max(th - think, 0);
      problems.emplace_back(make_pair(il, ih), make_pair(tl, th));
    }
  }
  vector<bs> precomp(n);
  for (int i = 0; i < n; i++) {
    for (int k = 0; k <= n; k++) {
      if (k >= problems[i].second.first && k <= problems[i].second.second) {
        precomp[i].set(k, true);
      }
    }
  }
  vector<bs> curr(n + 1);
  curr[0].set(0, true);
  for (int i = 0; i < n; i++) {
    vector<bs> nxt(n + 1);
    for (int j = 0; j <= n; j++) {
      nxt[j] |= curr[j];
      if (j < problems[i].first.first || j > problems[i].first.second) {
        continue;
      }
      auto tmp = curr[j] & precomp[i];
      if (j + 1 <= n) {
        nxt[j + 1] |= tmp;
      }
      nxt[j] |= tmp << 1;
    }
    nxt.swap(curr);
  }
  int ret = 0;
  for (int j = 0; j <= n; j++) {
    for (int k = 0; k <= n; k++) {
      if (curr[j].test(k)) {
        ret = max(ret, j + k);
      }
    }
  }
  cout << ret << '\n';
}
