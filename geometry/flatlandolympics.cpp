
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

template <class T>
int sgn(T x) {
  return (x > 0) - (x < 0);
}
template <class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); }  // makes dist()=1
  P perp() const { return P(-y, x); }        // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {  // a[pos] += dif
    for (; pos < len(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {  // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

struct FT2 {
  vector<vector<int>> ys;
  vector<FT> ft;
  FT2(int limx) : ys(limx) {}
  void fakeUpdate(int x, int y) {
    for (; x < len(ys); x |= x + 1) ys[x].push_back(y);
  }
  void init() {
    for (auto& v : ys) sort(begin(v), end(v)), ft.emplace_back(len(v));
  }
  int ind(int x, int y) {
    return (int)(lower_bound(begin(ys[x]), end(ys[x]), y) - ys[x].begin());
  }
  void update(int x, int y, ll dif) {
    for (; x < len(ys); x |= x + 1) ft[x].update(ind(x, y), dif);
  }
  ll query(int x, int y) {
    ll sum = 0;
    for (; x; x &= x - 1) sum += ft[x - 1].query(ind(x - 1, y));
    return sum;
  }
};

using P = Point<ll>;

vector<int> polar_sort(const vector<P>& pts, P center, bool reverse) {
  vector<pair<P, int>> ppts;
  for (int i = 0; i < len(pts); i++) {
    ppts.emplace_back(pts[i] - center, i);
  }
  sort(ppts.begin(), ppts.end(),
       [&reverse](const pair<P, int>& a, const pair<P, int>& b) {
         if (a.first.y * b.first.x != b.first.y * a.first.x) {
           auto delta = a.first.y * b.first.x - b.first.y * a.first.x;
           return reverse ? delta > 0 : delta < 0;
         }
         return a.first.dist2() < b.first.dist2();
       });
  vector<int> ret(pts.size());
  for (int i = 0; i < len(ppts); i++) {
    ret[ppts[i].second] = i;
  }
  return ret;
}

int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

ll solve(vector<P> pts, const P& s, const P& e, bool flip) {
  int n = len(pts);

  auto s_order = polar_sort(pts, s, flip);
  auto e_order = polar_sort(pts, e, !flip);

  FT2 tree{n};
  for (int i = 0; i < n; i++) {
    tree.fakeUpdate(s_order[i], e_order[i]);
  }
  tree.init();

  for (int i = 0; i < n; i++) {
    tree.update(s_order[i], e_order[i], 1);
  }

  ll ret = 0;
  for (int i = 0; i < n; i++) {
    ret += tree.query(s_order[i], e_order[i]);
  }

  return ret;
}

bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

ll solve_collinear(const vector<P>& pts, const P& s, const P& e) {
  ll lcnt = 0, rcnt = 0;
  for (const auto& p : pts) {
    bool left = onSegment(p, e, s), right = onSegment(p, s, e);
    assert(left || right);
    lcnt += left;
    rcnt += right;
  }
  return lcnt * (lcnt - 1) / 2 + rcnt * (rcnt - 1) / 2;
}

inline void prayGod() {
  P s, e;
  cin >> s.x >> s.y >> e.x >> e.y;
  int n;
  cin >> n;
  vector<P> up, down, collinear;
  for (int i = 0; i < n; i++) {
    P p;
    cin >> p.x >> p.y;
    switch (sideOf(s, e, p)) {
      case 1:
        up.push_back(p);
        break;
      case -1:
        down.push_back(p);
        break;
      default:
        collinear.push_back(p);
        break;
    }
  }

  ll ret = solve(up, s, e, false) + solve(down, s, e, true) +
           solve_collinear(collinear, s, e);
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
