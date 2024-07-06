#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define len(a) static_cast<int>((a).size())

struct centroid_tree {
  vector<vector<int>> graph;
  vector<bool> visited;
  vector<int> par, sz;
  int n;
  explicit centroid_tree(int s) : n{s}, graph(s), visited(s), par(s), sz(s) {}
  void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  int find_size(int v, int p = -1) {
    if (visited[v]) return 0;
    sz[v] = 1;
    for (int x : graph[v]) {
      if (x != p) sz[v] += find_size(x, v);
    }
    return sz[v];
  }
  int find_centroid(int v, int p, int n) {
    for (int x : graph[v]) {
      if (x != p) {
        if (!visited[x] && sz[x] > n / 2) {
          return find_centroid(x, v, n);
        }
      }
    }
    return v;
  }
  void build(int v = 0, int p = -1) {
    find_size(v);
    int c = find_centroid(v, -1, sz[v]);
    visited[c] = true;
    par[c] = p;
    for (int x : graph[c]) {
      if (!visited[x]) {
        build(x, c);
      }
    }
  }
};

struct Line {
  mutable ll k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const ll inf = LLONG_MAX;
  ll div(ll a, ll b) {  // floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k)
      x->p = x->m > y->m ? inf : -inf;
    else
      x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

template <class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= len(V); pw *= 2, ++k) {
      jmp.emplace_back(len(V) - pw * 2 + 1);
      for (int j = 0; j < len(jmp[k]); j++)
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b);  // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

struct LCA {
  int T = 0;
  vector<int> time, path, ret;
  RMQ<int> rmq;

  LCA(vector<vector<int>>& C) : time(len(C)), rmq((dfs(C, 0, -1), ret)) {}
  void dfs(vector<vector<int>>& C, int v, int par) {
    time[v] = T++;
    for (int y : C[v])
      if (y != par) {
        path.push_back(v), ret.push_back(time[v]);
        dfs(C, y, v);
      }
  }

  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
};

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

int main() {
  int n;
  cin >> n;
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
  }
  vector<vector<pair<int, ll>>> graph(n);
  centroid_tree ct{n};
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    graph[--u].emplace_back(--v, w);
    graph[v].emplace_back(u, w);
    ct.add_edge(u, v);
  }
  ct.build();
  LCA lt{ct.graph};
  vector<ll> d(n);
  y_combinator([&](auto self, int curr, int par, ll dist) -> void {
    d[curr] = dist;
    for (auto [neighbor, weight] : graph[curr]) {
      if (neighbor != par) {
        self(neighbor, curr, dist + weight);
      }
    }
  })(0, -1, 0);
  auto dist = [&](int u, int v) {
    auto l = lt.lca(u, v);
    return d[u] + d[v] - 2 * d[l];
  };
  vector<LineContainer> ds(n);
  vector<ll> val(n);
  for (int i = 0; i < n; i++) {
    val[i] = p[i] * 1ll * p[i];
  }
  for (int i = 0; i < n; i++) {
    int curr = i;
    ds[curr].add(-p[i], 0);
    while (ct.par[curr] != -1) {
      curr = ct.par[curr];
      if (!ds[curr].empty()) {
        val[i] = min(val[i], -ds[curr].query(p[i]) + dist(i, curr));
      }
      val[curr] = min(val[curr], p[curr] * 1ll * p[i] + dist(i, curr));
      ds[curr].add(-p[i], -dist(i, curr));
    }
  }
  for (int i = 0; i < n; i++) {
    ds[i].clear();
  }
  for (int i = n - 1; i >= 0; i--) {
    int curr = i;
    ds[curr].add(-p[i], 0);
    while (ct.par[curr] != -1) {
      curr = ct.par[curr];
      if (!ds[curr].empty()) {
        val[i] = min(val[i], -ds[curr].query(p[i]) + dist(i, curr));
      }
      ds[curr].add(-p[i], -dist(i, curr));
    }
  }
  cout << accumulate(val.begin(), val.end(), 0ll) << '\n';
}
