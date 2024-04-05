#include <bits/stdc++.h>
#ifdef LLOCAL
#include "debug.h"
#else
#define var(...)
#define debugArr(...)
#endif

using namespace std;

using ui = unsigned int;
using ll = long long;
using ull = uint64_t;
using ld = long double;

#define len(a) static_cast<int>((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

static constexpr const int iinf = 0x3f3f3f3f;
static constexpr const ll inf = 1'000'000'000'000'000;
static constexpr const ll mod = 1e9 + 7;

#define debugDecimal(d) cerr << setprecision(d) << fixed
#define printVerdict(verdict) cout << (verdict ? "YES" : "NO") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define printCase(_) cout << "Case #" << (_) << ": "

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
template <typename T>
istream& operator>>(istream& in, vector<T>& arr) {
  for (T& a : arr) in >> a;
  return in;
}
template <typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) {
  in >> a.first >> a.second;
  return in;
}

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

inline void prayGod() {
  vector<int> data(3);
  cin >> data;
  sort(data.begin(), data.end());
  int MAXN = data.back() * 2 + 2;
  vector<ll> fact(MAXN), invfact(MAXN), inv(MAXN), p2(MAXN);
  invfact[0] = fact[0] = inv[1] = fact[1] = invfact[1] = 1;
  p2[0] = 1;
  p2[1] = 2;
  for (int i = 2; i < MAXN; i++) {
    inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    fact[i] = fact[i - 1] * i % mod;
    invfact[i] = invfact[i - 1] * inv[i] % mod;
    p2[i] = p2[i - 1] * 2 % mod;
  }
  auto C = [&](int n, int k) -> ll {
    if (n > k) return (fact[n] * invfact[k] % mod) * invfact[n - k] % mod;
    return n == k;
  };
  auto f = [&](int k) -> ll {
    if (k == 0) return 0ll;
    ll ret = 0;
    for (int t1 = data[1] - data[0]; t1 <= k; t1++) {
      int t2 = data[0] - data[1] + t1;
      int t3 = k - t1 - t2;
      if (t2 < 0 || t1 + t2 > k || t1 + t3 > data[1]) continue;
      ll curr = fact[k] * invfact[t1] % mod;
      curr = curr * invfact[t2] % mod;
      curr = curr * invfact[t3] % mod;
      curr = curr * C(data[1] + t2 - 1, k - 1) % mod;
      curr = curr * p2[k - t1 - t2] % mod;
      ret = (ret + curr) % mod;
    }
    return ret;
  };
  ll ret = (f(data.back()) * 2 % mod + f(data.back() - 1)) % mod;
  ret = (ret + f(data.back() + 1)) % mod;
  cout << ret << '\n';
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
