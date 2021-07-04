#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
#define PI 2 * acos(0.0)

const int iinf = 0x3f3f3f3f;
const ll inf = 3e17;
const ll mod = 1e9 + 7;

#define var(args...)                           \
    {                                          \
        string _s = #args;                     \
        stringstream _ss;                      \
        string ccurr = "";                     \
        for (int zz = 0; zz < len(_s); zz++) { \
            if (_s[zz] == ' ') continue;       \
            if (_s[zz] == ',') {               \
                _ss << ' ' + ccurr;            \
                ccurr = "";                    \
            } else                             \
                ccurr += _s[zz];               \
        }                                      \
        _ss << ' ' + ccurr;                    \
        istream_iterator<string> _it(_ss);     \
        vars(_it, args);                       \
    }
#define debugDecimal(d) cerr << setprecision(d) << fixed

void vars(istream_iterator<string> it) { cerr << '\n'; }
template <typename T, typename... Args>
void vars(istream_iterator<string> it, T a, Args... args) {
    cerr << " [" << *it << ": " << a << "] ";
    vars(++it, args...);
}

#define printVerdict(verdict) \
    cout << (verdict ? "Yes" : "No") << '\n'
#define printDecimal(d) \
    cout << setprecision(d) << fixed
#define printCase(_) \
    cout << "Case #" << (_) << ": "

template <class T1, class T2, class T3>
void printTuple(const tuple<T1, T2, T3> &t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) { return out << p.first << " " << p.second; }
template <class T>
ostream &operator<<(ostream &out, const vector<T> &arr) {
    for (const T &a : arr) out << a << " ";
    return out;
}
template <class T>
ostream &operator<<(ostream &out, const vector<vector<T>> &grid) {
    for (const vector<T> &row : grid) out << row << '\n';
    return out;
}
template <class T>
istream &operator>>(istream &in, vector<T> &arr) {
    for (T &a : arr) in >> a;
    return in;
}
template <class T>
void readIdx(vector<pair<T, int>> &a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
}
template <class T1, class T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
    in >> a.first >> a.second;
    return in;
}

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

const int nax = 1000001;

// OBJECT REPRESENTING A POINT (OR VECTOR)
struct pt {
    ld x, y;
    pt() { x = y = -1; }
    pt(ld _x, ld _y) { x = _x, y = _y; }
    pt operator+(pt p) { return {x + p.x, y + p.y}; }
    pt operator-(pt p) { return {x - p.x, y - p.y}; }
    pt operator*(ld d) { return {x * d, y * d}; }
    pt operator/(ld d) { return {x / d, y / d}; }
    bool operator==(pt b) { return x == b.x && y == b.y; }
    bool operator!=(pt b) { return !(*this == b); }
    friend ostream &operator<<(ostream &out, pt &p) {
        return out << " (" << p.x << ", " << p.y << ") ";
    }
};

// VECTOR-RELATED OPERATIONS
pt perp(pt p) { return {-p.y, p.x}; }
ld dot(pt p, pt w) { return p.x * w.x + p.y * w.y; }
ld cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }
ld orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

// FIND MAGNITUDE OF VECTOR P
ld sq(pt p) { return p.x * p.x + p.y * p.y; }
ld abs(pt p) { return sqrt(sq(p)); }

// CHECK WHETHER A POINT IS INSIDE POLYGON, OUTSIDE POLYGON, OR ON THE BOUNDARY OF THE POLYGON
const int ON_SEGMENT = -1, INSIDE = 1, OUTSIDE = 0;

bool above(pt a, pt p) { return p.y >= a.y; }
bool crossesRay(pt a, pt p, pt q) { return (above(a, q) - above(a, p)) * orient(a, p, q) > 0; }
bool inDisk(pt a, pt b, pt c) { return dot(a - c, b - c) <= 0; }
bool onSegment(pt a, pt b, pt c) { return orient(a, b, c) == 0 && inDisk(a, b, c); }

int inPolygon(vector<pt> &p, pt a) {
    int cnt = 0;
    for (int i = 0, n = len(p); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a)) return ON_SEGMENT;
        cnt += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return cnt % 2;
}

// OBJECT REPRESENTING A LINE IN FORM AX + BY = C
struct line {
    pt v;
    ld c;
    line(pt _v, ld _c) : v(_v), c(_c) {}
    line(ld a, ld b, ld _c) : v({b, -a}), c(_c) {}
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}

    ld side(pt p) { return cross(v, p) - c; }
    double dist(pt p) { return abs(side(p)) / abs(v); }
    bool cmpProj(pt p, pt q) { return dot(v, p) < dot(v, q); }
};

// DETERMINE DISTANCE BETWEEN POINT P AND THE LINE CREATED BY POINT a AND POINT B
ld segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) return l.dist(p);
    }
    return min(abs(p - a), abs(p - b));
}

void prayGod() {
    int t = 1;
    while (true) {
        int n;
        cin >> n;
        if (!n) break;
        cout << "Case " << (t++) << '\n';
        vector<pt> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }
        int s;
        cin >> s;
        for (int i = 0; i < s; i++) {
            pt p;
            cin >> p.x >> p.y;
            int status = inPolygon(points, p);
            if (status == ON_SEGMENT) {
                cout << "Winged!" << '\n';
                continue;
            } else if (status == INSIDE) {
                cout << "Hit! ";
            } else {
                cout << "Miss! ";
            }
            ld ret = iinf;
            for (int j = 0; j < n; j++) {
                ld temp = segPoint(points[j], points[(j + 1) % n], p);
                ret = min(ret, temp);
            }
            printDecimal(9) << ret << '\n';
        }
    }
}

int main() {
    clock_t start = clock();

    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    if (EXTERNAL_INPUT)
        freopen(INPUT_FILE, "r", stdin);
    if (EXTERNAL_OUTPUT)
        freopen(OUTPUT_FILE, "w", stdout);

    prayGod();

    clock_t end = clock();

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME)
        debugDecimal(5) << time_taken << " s" << '\n';
}
