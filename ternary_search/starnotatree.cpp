#include <bits/stdc++.h>
#include <cassert>
#include <vector>

using namespace std;

using ui = unsigned int;
using ll = long long;
using ld = long double;

template <typename K, typename V>
using umap = std::unordered_map<K, V>;

#define null NULL
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)

constexpr ll inf = 1000000000000000000;
constexpr int MAXN = 1001;
constexpr int iinf = 1e9 + 10;

template <typename T> int sgn(T x) { return (x > 0) - (x < 0); }
template <typename T> 
struct Point {
  using P = Point;
  T x, y;
  explicit Point(T x_ = 0, T y_ = 0) : x{x_}, y{y_} {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const {return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  double dist() const { return sqrt((double) dist2()); }
  double angle() const { return atan2(y, x); }
}; 

using P = Point<double>;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n; std::cin >> n;
  std::vector<P> points(n);
  for (int i = 0; i <n; i++) {
    std::cin >> points[i].x >> points[i].y;
  }
  auto solve = [&](double x, double y) {
    double d = 0;
    for (auto p : points) {
      d += (p - P(x, y)).dist();
    }
    return d;
  };
  auto solve_y = [&](double x) {
    double ly = 0, ry = 1e4 + 10;
    for (int iter = 0; iter < 100; iter++) {
      auto m1 = ly + (ry - ly) / 3;
      auto m2 = ry - (ry - ly) / 3;
      if (solve(x, m1) < solve(x, m2)) {
        ry = m2;
      } else {
        ly = m1;
      }
    }
    return (ly + ry) / 2;
  };
  double lx = 0, rx = 1e4 + 10;
  for (int iter = 0; iter < 100; iter++) {
    auto m1 = lx + (rx - lx) / 3;
    auto m2 = rx - (rx - lx) / 3;

    if (solve(m1, solve_y(m1)) < solve(m2, solve_y(m2))) {
      rx = m2;
    } else {
      lx = m1;
    }
  }
  auto fx = (lx + rx) / 2;
  auto fy = solve_y(fx);
  std::cout << setprecision(8) << fixed << solve(fx, fy) << '\n';
}  
