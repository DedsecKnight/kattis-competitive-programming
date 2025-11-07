
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
constexpr ll inf = 1000000000000000000ll;
constexpr ll mod = 1000000007;

#define debugDecimal(d) cerr << setprecision(d) << fixed
#define printVerdict(verdict) cout << (verdict ? "Yes" : "No") << '\n'
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

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

inline void prayGod() {
  string s;
  cin >> s;
  int m = len(s);
  vector<vector<int>> nxt(m, vector<int>(26, -1));
  nxt[m - 1][s[m - 1] - 'a'] = m - 1;
  for (int i = m - 2; i >= 0; i--) {
    for (int j = 0; j < 26; j++) {
      nxt[i][j] = nxt[i + 1][j];
    }
    nxt[i][s[i] - 'a'] = i;
  }
  int n, q;
  cin >> n >> q;
  vector<vector<pair<int, int>>> r(m);
  vector<string> words(n);
  cin >> words;
  sort(words.begin(), words.end());
  auto calc_rb = [&](int i, int j) -> int {
    int pos = nxt[i][words[j][0] - 'a'];
    for (int k = 1; k < len(words[j]) && pos != -1; k++) {
      if (pos == m - 1) {
        return -1;
      }
      pos = nxt[pos + 1][words[j][k] - 'a'];
    }
    return pos;
  };
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      auto rb = calc_rb(i, j);
      if (rb != -1) r[i].emplace_back(rb, j);
    }
  }
  vector<vector<tuple<int, int, int>>> query_buckets(m);
  for (int i = 0; i < q; i++) {
    int l, rb, k;
    cin >> l >> rb >> k;
    l--, rb--;
    query_buckets[l].emplace_back(rb, k, i);
  }
  vector<int> ans(q, -1);
  for (int l = 0; l < m; l++) {
    sort(query_buckets[l].begin(), query_buckets[l].end());
    sort(r[l].begin(), r[l].end());
    int ptr = 0;
    Tree<int> tree;
    for (auto [rb, k, idx] : query_buckets[l]) {
      while (ptr < len(r[l]) && r[l][ptr].first <= rb) {
        tree.insert(r[l][ptr].second);
        ptr++;
      }
      if (len(tree) >= k) {
        ans[idx] = *tree.find_by_order(k - 1);
      }
    }
  }
  for (int i = 0; i < q; i++) {
    if (ans[i] == -1) {
      cout << "NO SUCH WORD" << '\n';
    } else {
      int sz = min(len(words[ans[i]]), 10);
      cout << words[ans[i]].substr(0, sz) << '\n';
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
