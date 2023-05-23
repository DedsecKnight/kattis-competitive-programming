#include <iostream>
#include <math.h>
#include <cassert>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#include <queue>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

#define len(a) int((a).size())

#define printDecimal(d) \
    cout << setprecision(d) << fixed

template <typename T>
int sgn(T x) { return ((x > 0) - (x < 0));} 

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
    T dot(P p) const { return x*p.x+y*p.y; }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2());}
    T cross(P p) const { return x*p.y-y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    friend ostream& operator<<(ostream& out, const P& p) { return out << "(" << p.x << "," << p.y << ")"; }
    friend istream& operator>>(istream& in, P& p){ return in >> p.x >> p.y; }
};
using P = Point<double>;

double segDist(const P& s, const P& e, const P& p) {
    if (s == e) return (p-s).dist();
    auto d = (e-s).dist2(), t = min(d, max(.0,(p-s).dot(e-s)));
    return ((p-s)*d-(e-s)*t).dist()/d;
}

#define onSegment(s,e,p) (segDist((s),(e),(p)) < 1e-10)

bool segInter(const P& a, const P& b, const P& c, const P& d, P& inter) {
    auto oa = c.cross(d, a), ob = c.cross(d, b);
    auto oc = a.cross(b, c), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
        inter = (a*ob-b*oa)/(ob-oa);
        return true;
    }
    bool intersect = false;
    if (onSegment(c,d,a)) intersect = true, inter = a;
    else if (onSegment(c,d,b)) intersect = true, inter = b;
    else if (onSegment(a,b,c)) intersect = true, inter = c;
    else if (onSegment(a,b,d)) intersect = true, inter = d;
    return intersect;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    P s, ff, ft;
    double vs, vf;
    vector<pair<P, P>> walkways;
    vector<vector<int>> graph(n);
    vector<pair<bool, P>> fellow_inter(n);
    for (int i = 0;i<n; i++) {
        P from, to; cin >> from >> to;
        walkways.emplace_back(move(from), move(to));
    }
    vector<pair<int, P>> inters;
    for (int i = 0; i<n; i++) {
        for (int j = i+1;j<n; j++) {
            P inter;
            if (segInter(walkways[i].first, walkways[i].second, walkways[j].first, walkways[j].second, inter)) {
                graph[i].push_back(len(inters));
                inters.emplace_back(j, inter);
                graph[j].push_back(len(inters));
                inters.emplace_back(i, inter);
            }
        }
    }
    cin >> s >> vs;
    cin >> ff >> ft >> vf;
    for (int i = 0;i<n; i++) {
        fellow_inter[i].first = segInter(walkways[i].first, walkways[i].second, ff, ft, fellow_inter[i].second);
    }
    vector<double> dist(len(inters), 1e18);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> q;
    for (int i = 0; i<n; i++) {
        if (onSegment(walkways[i].first, walkways[i].second, s)) {
            dist.push_back(0);
            inters.emplace_back(i, s);
            q.emplace(0.0, len(inters)-1);
        }
    }
    double ret = 1e18;
    while (!q.empty()) {
        auto [d, ck] = q.top();
        q.pop();
        if (d != dist[ck]) continue;
        auto [curr, pos] = inters[ck];
        if (fellow_inter[curr].first) {
            auto st = (dist[ck] + (pos-fellow_inter[curr].second).dist())/vs;
            auto frt = (ff-fellow_inter[curr].second).dist()/vf;
            if (st <= frt + 1e-8) ret = min(ret, frt);
        }
        for (const auto& key : graph[curr]) {
            auto new_dist = dist[ck] + (pos - inters[key].second).dist();
            if (dist[key] > new_dist) {
                dist[key] = new_dist;
                q.emplace(new_dist, key);
            }
        }
    }
    if (ret >= 1e18) {
        cout << "Impossible" << '\n';
    } else {
        printDecimal(8) << ret << '\n';
    }
}
