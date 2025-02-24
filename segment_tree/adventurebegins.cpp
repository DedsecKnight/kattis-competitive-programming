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

struct data_t {
  ll sum{0}, sum_sq{0};
};

struct Tree {
  vector<data_t> tree;
  vector<ll> madd;
  explicit Tree(int n) : tree(4 * n), madd(4 * n) {}
  void propagate(int idx, int curr_l, int curr_r) {
    if (madd[idx]) {
      auto mid = curr_l + (curr_r - curr_l) / 2;
      add(idx * 2 + 1, curr_l, mid, curr_l, curr_r, madd[idx]);
      add(idx * 2 + 2, mid + 1, curr_r, curr_l, curr_r, madd[idx]);
      madd[idx] = 0;
    }
  }
  void add(int idx, int curr_l, int curr_r, int l, int r, ll x) {
    if (curr_l > curr_r || curr_r < l || r < curr_l) return;
    if (l <= curr_l && curr_r <= r) {
      madd[idx] = (madd[idx] + x) % mod;
      int sz = curr_r - curr_l + 1;
      auto x2 = x * x % mod;
      tree[idx].sum_sq = (tree[idx].sum_sq + sz * 1ll * x2 % mod) % mod;
      ll delta = (x * 2 % mod) * tree[idx].sum % mod;
      tree[idx].sum_sq = (tree[idx].sum_sq + delta) % mod;
      tree[idx].sum = (tree[idx].sum + x * sz % mod) % mod;
    } else {
      propagate(idx, curr_l, curr_r);
      auto mid = curr_l + (curr_r - curr_l) / 2;
      add(idx * 2 + 1, curr_l, mid, l, r, x);
      add(idx * 2 + 2, mid + 1, curr_r, l, r, x);
      tree[idx].sum = (tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum) % mod;
      tree[idx].sum_sq =
          (tree[idx * 2 + 1].sum_sq + tree[idx * 2 + 2].sum_sq) % mod;
    }
  }
  pair<ll, ll> query(int idx, int curr_l, int curr_r, int l, int r) {
    if (curr_l > curr_r || curr_r < l || r < curr_l) return make_pair(0, 0);
    if (l <= curr_l && curr_r <= r) {
      return make_pair(tree[idx].sum, tree[idx].sum_sq);
    }
    propagate(idx, curr_l, curr_r);
    auto mid = curr_l + (curr_r - curr_l) / 2;
    auto left = query(idx * 2 + 1, curr_l, mid, l, r);
    auto right = query(idx * 2 + 2, mid + 1, curr_r, l, r);
    return make_pair((left.first + right.first) % mod,
                     (left.second + right.second) % mod);
  }
};

inline void prayGod() {
  int n, q;
  cin >> n >> q;
  Tree t1{n}, t2{n};
  vector<ll> inv(n + 1);
  inv[1] = 1;
  for (int i = 2; i <= n; i++) {
    inv[i] = mod - (mod / i) * inv[mod % i] % mod;
  }
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      auto s = inv[v - u + 1];
      auto ss = s * s % mod;
      t1.add(0, 0, n - 1, u, v, s);
      t2.add(0, 0, n - 1, u, v, ss);
    } else {
      auto t1v = t1.query(0, 0, n - 1, 0, n - 1);
      auto t2v = t2.query(0, 0, n - 1, 0, n - 1);
      auto ans = (t1v.first + t1v.second) % mod;
      ans = (ans - t2v.first + mod) % mod;
      cout << ans << '\n';
    }
  }
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
