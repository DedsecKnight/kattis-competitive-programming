#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

template <class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0)  // if parallel
    return {-(s1.cross(e1, s2) == 0), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

using P = Point<double>;
static constexpr double EPS = 1e-8;

double segDist(P& s, P& e, P& p) {
  if (s == e) return (p - s).dist();
  auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
  return ((p - s) * d - (e - s) * t).dist() / d;
}

bool onSegment(P s, P e, P p) { return segDist(s, e, p) <= EPS; }

int sideOf(const P& s, const P& e, const P& p, double eps = EPS) {
  auto a = (e - s).cross(p - s);
  double l = (e - s).dist() * eps;
  return (a > l) - (a < -l);
}

bool inPolygon(const vector<P>& p, P a, bool strict = true) {
  int cnt = 0, n = len(p);
  for (int i = 0; i < n; i++) {
    P q = p[(i + 1) % n];
    if (onSegment(p[i], q, a)) return !strict;
    cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
  }
  return cnt;
}

double lineDist(const P& a, const P& b, const P& p) {
  return (double)(b - a).cross(p - a) / (b - a).dist();
}

double polygonArea2(const vector<P>& v) {
  double a = v.back().cross(v[0]);
  for (int i = 0; i < len(v) - 1; i++) a += v[i].cross(v[i + 1]);
  return a;
}

ll onLine(const P& a, const P& b) {
  ll dx = static_cast<ll>(fabs(a.x - b.x));
  ll dy = static_cast<ll>(fabs(a.y - b.y));
  return gcd(dx, dy);
}

vector<P> segInter(P a, P b, P c, P d) {
  auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c),
       od = a.cross(b, d);
  // Checks if intersection is single non-endpoint point.
  if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
    return {(a * ob - b * oa) / (ob - oa)};
  set<P> s;
  if (onSegment(c, d, a)) s.insert(a);
  if (onSegment(c, d, b)) s.insert(b);
  if (onSegment(a, b, c)) s.insert(c);
  if (onSegment(a, b, d)) s.insert(d);
  return {begin(s), end(s)};
}

inline void prayGod() {
  int n;
  cin >> n;
  vector<P> pts(n);
  for (int i = 0; i < n; i++) {
    cin >> pts[i].x >> pts[i].y;
  }
  ll ret = 0;
  for (int i = 0; i < n; i++) {
    auto res = lineInter(pts[(i + n - 1) % n], pts[i], pts[(i + 1) % n],
                         pts[(i + 2) % n]);
    if (res.first == 0) {
      P a = pts[(i + n - 1) % n], b = pts[i], c = pts[(i + 1) % n],
        d = pts[(i + 2) % n];
      if (a.x == b.x) {
        assert(c.x == d.x);
        if (fabs(a.x - c.x) > 1) {
          cout << "infinitely many" << '\n';
          return;
        }
      } else {
        auto s2 = polygonArea2({a, b, c, d});
        ll bb = onLine(a, b) + onLine(b, c) + onLine(c, d) + onLine(d, a);
        auto ii = s2 - bb + 2;
        if (ii > 0) {
          cout << "infinitely many" << '\n';
          return;
        }
      }
      continue;
    }
    assert(res.first == 1);
    if (sideOf(pts[i], pts[(i + 1) % n], res.second) ==
        sideOf(pts[i], pts[(i + 1) % n], pts[(i + 2) % n])) {
      cout << "infinitely many" << '\n';
      return;
    }
    double minX = 1e9, maxX = -1e9;
    double minY = 1e9, maxY = -1e9;
    vector<P> tri{pts[i], res.second, pts[(i + 1) % n]};
    for (const auto& p : tri) {
      minX = min(minX, p.x);
      minY = min(minY, p.y);
      maxX = max(maxX, p.x);
      maxY = max(maxY, p.y);
    }
    for (int y = floor(minY) - 10; y <= ceil(maxY) + 10; y++) {
      double lb = 1e9, rb = -1e9;
      bool line_overlap = false;
      for (int j = 0; j < 3; j++) {
        auto inter = segInter(P{-1e7, double(y)}, P{1e7, double(y)}, tri[j],
                              tri[(j + 1) % 3]);
        if (len(inter) == 1) {
          lb = min(lb, inter[0].x);
          rb = max(rb, inter[0].x);
        }
        if (len(inter) > 1) {
          line_overlap = true;
        }
      }
      if (line_overlap) continue;
      if (fabs(lb - ceil(lb)) <= EPS) {
        lb = ceil(lb) + 1;
      } else {
        lb = ceil(lb);
      }

      if (fabs(rb - floor(rb)) <= EPS) {
        rb = floor(rb) - 1;
      } else {
        rb = floor(rb);
      }
      if (lb <= rb) {
        ret += static_cast<ll>(round(rb)) - static_cast<ll>(round(lb)) + 1;
      }
    }
  }
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
