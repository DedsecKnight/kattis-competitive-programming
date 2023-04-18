#include <bits/stdc++.h>
using namespace std;

#define len(x) int((x).size())
constexpr double EPS = 1e-8;

template <typename T>
int sgn(T a) { return (a > 0) - (a < 0); }

template <typename T>
struct Point {
    using P = Point;
    T x, y;
    explicit Point(T x_ = 0, T y_ = 0) : x{x_}, y{y_} {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const {return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt(dist2()); }
    P perp() const { return P(-y, x); }
    double angle() const {return atan2(y, x); }
    friend ostream& operator<<(ostream& out, const P& p) {
        return out << "(" << p.x << "," << p.y << ") ";
    }
};

using P = Point<double>;
int lineIntersection(const P& s1, const P& e1, const P& s2, const P& e2, P& r) {
	if ((e1-s1).cross(e2-s2)) { //if not parallell
		r = s2-(e2-s2)*(e1-s1).cross(s2-s1)/(e1-s1).cross(e2-s2);
		return 1;
	} else {
		return -((e1-s1).cross(s2-s1)==0 || s2==e2);
    }
}

struct HalfPlane {
    P p1, p2;
    explicit HalfPlane(P a = P(), P b = P()) : p1(a), p2(b) {}
    P intpo(HalfPlane y) {
        P r; 
        assert(lineIntersection(p1, p2, y.p1, y.p2, r) == 1);
        return r;
    }
    P dir() { return p2-p1; }
    bool contains(P x) { return (p2-p1).cross(x-p1) < EPS; }
    bool out(P x) { return !contains(x); }
};

vector<P> halfPlaneIntersection(vector<HalfPlane> b) {
    sort(begin(b), end(b), [](HalfPlane al, HalfPlane bl) {
        auto a = al.dir(), bb = bl.dir();
        if (a.x * bb.x < 0) return a.x < 0;
        if (abs(a.x) < EPS) {
            if (abs(bb.x) < EPS) return a.y > 0 && bb.y < 0;
            if (bb.x < 0) return a.y > 0;
            if (bb.x > 0) return true;
        } 
        if (abs(bb.x) < EPS) {
            if (a.x < 0) return bb.y < 0;
            if (a.x > 0) return false;
        }
        return a.cross(bb) > 0;
    });
    int n = len(b);
    int q = 1, h = 0, i;
    vector<HalfPlane> c(len(b) + 10);
    for (i=0; i<n; i++) {
        while (q < h && b[i].out(c[h].intpo(c[h-1]))) h--;
        while (q < h && b[i].out(c[q].intpo(c[q+1]))) q++;
        c[++h] = b[i];
        if (q < h && abs(c[h].dir().cross(c[h-1].dir())) < EPS) {
            if (c[h].dir().dot(c[h-1].dir()) > 0) {
                h--;
                if (b[i].out(c[h].p1)) c[h] = b[i];
            } else {
                return {};
            }
        }
    }
    while (q < h-1 && c[q].out(c[h].intpo(c[h-1]))) h--;
    while (q < h-1 && c[h].out(c[q].intpo(c[q+1]))) q++;
    if (h-q <= 1) {
        return {};
    }c[h+1] = c[q];
    vector<P> s;
    for (i = q; i<=h; i++) {
        s.push_back(c[i].intpo(c[i+1]));
    }
    s.push_back(s[0]);
    return s;
} 

struct CutLine {
    P v;
    double c;
    CutLine(double a, double b, double cc) : v(b, -a), c(cc) {}
    double side(P p) { return v.cross(p) - c; }
    double dist(P p) {return abs(side(p)) / v.dist(); }
    double sqDist(P p) {return side(p) * side(p) / double(v.dist2()); }
    P proj(P p) {return p - v.perp()*side(p) / v.dist2(); }
};

int circleLine(P o, double r, CutLine l, pair<P, P>& out) {
    double h2 = r*r - l.sqDist(o);
    if (h2 >= 0) {
        P p = l.proj(o);
        P h = l.v*sqrt(h2) / l.v.dist();
        out = make_pair(p-h, p+h);
    }
    return 1 + sgn(h2);
}

double circlePoly(P c, double r, vector<P> ps) {
    auto tri = [&](P p, P q) {
        auto r2 = r * r / 2;
        P d = q - p;
        auto a = d.dot(p) / d.dist2(), b = (p.dist2()-r*r)/d.dist2();
        auto det = a*a-b;
        if (det <= 0) return atan2(p.cross(q), p.dot(q)) * r2;
        auto s = max(0., -a-sqrt(det)), t = min(1., -a+sqrt(det));
        if (t < 0 || 1 <= s) return atan2(p.cross(q), p.dot(q)) * r2;
        P u = p+d*s, v=p+d*t;
        return atan2(p.cross(u),p.dot(u)) * r2 + u.cross(v)/2 + atan2(v.cross(q), v.dot(q)) * r2; 
    };
    auto sum = 0.0;
    for (int i = 0;i<len(ps); i++) {
        sum += tri(ps[i]-c, ps[(i+1)%len(ps)]-c);
    }
    return sum;
}

int main() {
    int n,m;
    double r; cin >> n >> m >> r;
    vector<P> candles;
    for (int i = 0; i<n; i++) {
        int x, y; cin >> x >> y;
        candles.emplace_back(x, y);
    }
    vector<HalfPlane> halfplanes;
    for (int i = 0; i<m; i++) {
        int a,b,c; cin >> a >> b >> c;
        CutLine cut_line(a, b, -c);
        pair<P, P> intersection;
        assert(circleLine(P(), r, cut_line, intersection) == 2);
        halfplanes.emplace_back(intersection.first, intersection.second);
    }
    bool possible = true;
    for (int mask = 0; mask < (1 << m); mask++) {
        vector<HalfPlane> curr_plane(begin(halfplanes), end(halfplanes));
        for (int i = 0; i<m; i++) {
            if (mask & (1 << i)) swap(curr_plane[i].p1, curr_plane[i].p2);
        }
        int cnt = 0;
        for (int i = 0;i<n; i++) {
            cnt += all_of(begin(curr_plane), end(curr_plane), [&](HalfPlane pl) {
                return pl.contains(candles[i]);
            });
        }
        if (cnt > 1) {
            possible = false;
            break;
        }
        if (cnt > 0) continue;

        // Create bounding box
        curr_plane.emplace_back(P(-1000, 1000), P(1000, 1000));
        curr_plane.emplace_back(P(-1000, -1000), P(-1000, 1000));
        curr_plane.emplace_back(P(1000, -1000), P(-1000, -1000));
        curr_plane.emplace_back(P(1000, 1000), P(1000, -1000));

        // check if intersection between halfplanes and circle is nonempty
        auto hpi = halfPlaneIntersection(curr_plane);
        if (hpi.empty()) continue;
        if (circlePoly(P(), r, hpi) > EPS) {
            possible = false;
            break;
        }
    }
    cout << (possible ? "yes" : "no") << '\n';
}