#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;

#ifdef LLOCAL
#include "./debug.h"
#else
#define var(...)
#define debugArr(...)
#endif

using ui = unsigned int;
using ll = long long;
using ull = uint64_t;
using ld = long double;

template <typename K, typename V>
using umap = unordered_map<K, V>;

#define len(a) static_cast<int>((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

constexpr int iinf = 0x3f3f3f3f;
constexpr ll inf = 1000000000000000;
constexpr ll mod = 1000000007;

#define debugDecimal(d) cerr << setprecision(d) << fixed
#define printVerdict(verdict) cout << (verdict ? "YES" : "NO") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define printCase(_) cout << "Case #" << (_) << ": "

template <int I, typename TupleT>
ostream& printTupleImpl(ostream& out, const TupleT& t) {
  if constexpr (I < tuple_size_v<TupleT>) {
    out << get<I>(t) << " ";
    printTupleImpl<I + 1, TupleT>(out, t);
  }
  return out;
}
template <typename... Ts>
ostream& operator<<(ostream& out, const tuple<Ts...>& t) {
  return printTupleImpl<0>(out, t);
}

template <int I, typename TupleT>
istream& readTupleImpl(istream& in, TupleT& t) {
  if constexpr (I < tuple_size_v<TupleT>) {
    in >> get<I>(t);
    readTupleImpl<I + 1, TupleT>(in, t);
  }
  return in;
}

template <typename... Ts>
istream& operator>>(istream& in, tuple<Ts...>& t) {
  return readTupleImpl<0>(in, t);
}

template <typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p) {
  return out << p.first << " " << p.second;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
  for (const T& a : arr) out << a << " ";
  return out;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& grid) {
  for (const vector<T>& row : grid) out << row << '\n';
  return out;
}
template <typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) {
  in >> a.first >> a.second;
  return in;
}
template <typename T>
istream& operator>>(istream& in, vector<T>& arr) {
  for (T& a : arr) in >> a;
  return in;
}

namespace ycomb {
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
}  // namespace ycomb

template <typename Fun>
decltype(auto) y_combinator(Fun&& fun) {
  return ycomb::y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

inline void prayGod() {
  int n, m;
  cin >> n >> m;
  vector<vector<ll>> dist(n + 2, vector<ll>(n + 2, inf));
  for (int i = 0; i < n + 2; i++) {
    dist[i][i] = 0;
  }
  for (int i = 0; i < m; i++) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    dist[u][v] = min(dist[u][v], w);
    dist[v][u] = min(dist[v][u], w);
  }
  for (int k = 0; k < n + 2; k++) {
    for (int i = 0; i < n + 2; i++) {
      for (int j = 0; j < n + 2; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  vector<vector<ll>> dp(1 << (n + 2), vector<ll>(n + 2, inf));
  dp[1][0] = 0;
  for (int mask = 2; mask < (1 << (n + 2)); mask++) {
    for (int i = 1; i <= n + 1; i++) {
      if (mask & (1 << i)) {
        for (int j = 0; j <= n + 1; j++) {
          if (i != j && mask & (1 << j) && dist[j][i] < inf) {
            dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][j] + dist[j][i]);
          }
        }
      }
    }
  }
  vector<ll> f(1 << n, inf);
  for (int mask = (1 << n) - 1; mask >= 0; mask--) {
    f[mask] = min(f[mask], dp[(mask * 2 + 1) | (1 << (n + 1))][n + 1]);
    for (int x = mask; x;) {
      --x &= mask;
      f[x] = min(f[x], f[mask]);
    }
  }
  for (int mask = 0; mask < (1 << n); mask++) {
    f[mask] += 5 * __builtin_popcount(mask);
  }
  int mx_car = (n + 4) / 5;
  vector<vector<ll>> g(1 << n, vector<ll>(mx_car + 1, inf));
  g[0][0] = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    for (int c = 1; c <= mx_car; c++) {
      g[mask][c] = g[mask][c - 1];
      if (__builtin_popcount(mask) <= 5) {
        g[mask][c] = min(g[mask][c], f[mask]);
      }
      for (int x = mask; x;) {
        --x &= mask;
        if (__builtin_popcount(x) <= 5) {
          g[mask][c] = min(g[mask][c], max(g[mask ^ x][c - 1], f[x]));
        }
      }
    }
  }
  cout << g.back().back() << '\n';
}

int main() {
#ifdef LLOCAL
  clock_t start = clock();
#endif
  std::ios_base::sync_with_stdio(false);
  cin.tie(0);

  prayGod();
#ifdef LLOCAL
  clock_t end = clock();

  double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;
  debugDecimal(5) << time_taken << " s" << '\n';
#endif
}
