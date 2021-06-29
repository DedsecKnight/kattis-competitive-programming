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
const ld PI = 2 * acos(0.0);

const int iinf = 0x3f3f3f3f;
const ll inf = 1e18;
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
    cout << (verdict ? "YES" : "NO") << '\n'
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

const int nax = 100000;

// KACTL implementation
template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.y, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    bool operator!=(P p) const { return !(*this == p); }
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
    friend ostream &operator<<(ostream &os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

// KACTL implementation
typedef Point<double> P;

bool circleInter(P a, P b, double r1, double r2, pair<P, P> *out) {
    if (a == b) {
        assert(r1 != r2);
        return false;
    }
    P vec = b - a;
    double d2 = vec.dist2(), sum = r1 + r2, dif = r1 - r2,
           p = (d2 + r1 * r1 - r2 * r2) / (d2 * 2), h2 = r1 * r1 - p * p * d2;
    if (sum * sum < d2 || dif * dif > d2) return false;
    P mid = a + vec * p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
    *out = {mid + per, mid - per};
    return true;
}

bool cover(P a, P b, double r1, double r2) {
    double d = (a - b).dist();
    return (d + r2 <= r1);
}

void prayGod() {
    int n;
    cin >> n;
    vector<P> center(n);
    vector<double> radius(n);

    for (int i = 0; i < n; i++) {
        cin >> center[i].x >> center[i].y >> radius[i];
    }

    double ret = 2 * PI * radius.back();

    for (int i = n - 2; i >= 0; i--) {
        bool cover_all = false;
        vector<pair<ld, ld>> events;

        for (int j = i + 1; j < n; j++) {
            if (cover(center[j], center[i], radius[j], radius[i])) {
                cover_all = true;
                break;
            }

            pair<P, P> out;
            if (circleInter(center[j], center[i], radius[j], radius[i], &out)) {
                out.first = out.first - center[i];
                out.second = out.second - center[i];

                if (out.first == out.second) continue;

                ld fangle = out.first.angle(), sangle = out.second.angle();

                if (fangle > sangle) {
                    if (sangle < 0 && fangle >= 0) {
                        events.emplace_back(fangle, PI);
                        events.emplace_back(PI, sangle + 2 * PI);
                    } else {
                        if (fangle < 0) fangle += 2 * PI;
                        if (sangle < 0) sangle += 2 * PI;
                        events.emplace_back(fangle, 2 * PI);
                        events.emplace_back(0, sangle);
                    }
                } else {
                    if (fangle < 0 && sangle >= 0) {
                        if (fangle < 0) fangle += 2 * PI;
                        if (sangle < 0) sangle += 2 * PI;
                        events.emplace_back(fangle, 2 * PI);
                        events.emplace_back(0, sangle);
                    } else {
                        if (fangle < 0) fangle += 2 * PI;
                        if (sangle < 0) sangle += 2 * PI;
                        events.emplace_back(fangle, sangle);
                    }
                }
            }
        }

        if (cover_all) continue;

        double remain = PI * 2 * radius[i];
        if (!events.empty()) {
            sort(events.begin(), events.end());

            ld start = events[0].first, end = events[0].second;
            for (int j = 1; j < len(events); j++) {
                if (end <= events[j].first) {
                    remain -= radius[i] * (end - start);
                    tie(start, end) = events[j];
                } else
                    end = max(end, events[j].second);
            }

            remain -= radius[i] * (end - start);
        }
        ret += max(remain, 0.0);
    }

    printDecimal(7) << ret << '\n';
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
