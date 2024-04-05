#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")

#ifdef LLOCAL
#include "debug.h"
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
constexpr const ll mod = 1'000'000'007;

template <typename Fun>
class y_combinator_result {
    Fun fun_;

   public:
    template <typename T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <typename... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
template <typename Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

template <class T>
int sgn(T x) {
    return (x > 0) - (x < 0);
}
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
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

using P = Point<ll>;
vector<P> convexHull(vector<P> pts) {
    if (len(pts) <= 1)
        return pts;
    sort(begin(pts), end(pts));
    vector<P> h(len(pts) + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(begin(pts), end(pts)))
        for (P p : pts) {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0)
                t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

void rotate_polygon(vector<P>& poly) {
    size_t pos = 0;
    for (size_t i = 1; i < poly.size(); i++) {
        if (poly[i].y < poly[pos].y ||
            (poly[i].y == poly[pos].y && poly[i].x < poly[pos].x))
            pos = i;
    }
    rotate(begin(poly), begin(poly) + pos, end(poly));
}

vector<P> minkowski(vector<P> poly1, vector<P> poly2) {
    if (poly1.empty() || poly2.empty())
        return {};
    rotate_polygon(poly1);
    rotate_polygon(poly2);
    size_t n = poly1.size(), m = poly2.size();
    poly1.push_back(poly1[0]);
    poly1.push_back(poly1[1]);
    poly2.push_back(poly2[0]);
    poly2.push_back(poly2[1]);
    vector<P> ret;
    size_t i = 0, j = 0;
    while (i < n || j < m) {
        ret.push_back(poly1[i] + poly2[j]);
        auto c = (poly1[i + 1] - poly1[i]).cross(poly2[j + 1] - poly2[j]);
        i += c >= 0 && i < n;
        j += c <= 0 && j < m;
    }
    return convexHull(ret);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<P>> candidates(n);
    vector<bool> is_leaf(n, false);
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        if (k == 0) {
            is_leaf[i] = true;
            int x, y;
            cin >> x >> y;
            candidates[i].emplace_back(x, y);
        } else {
            for (int j = 0; j < k; j++) {
                int x;
                cin >> x;
                graph[i].push_back(--x);
            }
        }
    }
    auto neg = [&](const vector<P>& pts) {
        vector<P> ret;
        for (const auto& p : pts) {
            ret.emplace_back(-p.x, -p.y);
        }
        return ret;
    };
    auto solve = y_combinator([&](auto self, int curr) -> void {
        if (is_leaf[curr])
            return;
        vector<vector<P>> left, right;
        for (const auto& neighbor : graph[curr]) {
            self(neighbor);
            if (left.empty()) {
                left.push_back(neg(candidates[neighbor]));
            } else {
                left.push_back(
                    minkowski(left.back(), neg(candidates[neighbor])));
            }
        }
        if (len(graph[curr]) == 1) {
            candidates[curr] = candidates[graph[curr][0]];
            return;
        }
        for (int i = len(graph[curr]) - 1; i >= 0; i--) {
            auto neighbor = graph[curr][i];
            if (right.empty()) {
                right.push_back(neg(candidates[neighbor]));
            } else {
                right.push_back(
                    minkowski(right.back(), neg(candidates[neighbor])));
            }
        }
        reverse(right.begin(), right.end());
        for (int i = 0; i < len(graph[curr]); i++) {
            vector<P> curr_set{candidates[graph[curr][i]]};
            if (i - 1 >= 0)
                curr_set = minkowski(curr_set, left[i - 1]);
            if (i + 1 < len(graph[curr]))
                curr_set = minkowski(curr_set, right[i + 1]);
            candidates[curr].insert(candidates[curr].end(), curr_set.begin(),
                                    curr_set.end());
        }
        candidates[curr] = convexHull(candidates[curr]);
    });
    solve(0);
    cout << max_element(candidates[0].begin(), candidates[0].end(),
                        [](const auto& x, const auto& y) {
                            return x.dist2() < y.dist2();
                        })
                ->dist2()
         << '\n';
}