#include <bits/stdc++.h>

using namespace std;

using ui = unsigned int;
using ll = long long;
using ld = long double;

template <typename K, typename V>
using umap = unordered_map<K, V>;

#define null NULL
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

constexpr int iinf = 0x3f3f3f3f;
constexpr ll inf = 1000000000000000000;
constexpr ll mod = 1e9 + 7;

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

template <int I, typename TupleT>
ostream &printTupleImpl(ostream &out, const TupleT &t) {
    if constexpr (I < tuple_size_v<TupleT>) {
        out << get<I>(t) << " ";
        printTupleImpl<I + 1, TupleT>(out, t);
    }
    return out;
}
template <typename... Ts>
ostream &operator<<(ostream &out, const tuple<Ts...> &t) {
    return printTupleImpl<0>(out, t);
}

template <int I, typename TupleT>
istream &readTupleImpl(istream &in, TupleT &t) {
    if constexpr (I < tuple_size_v<TupleT>) {
        in >> get<I>(t);
        readTupleImpl<I + 1, TupleT>(in, t);
    }
    return in;
}

template <typename... Ts>
istream &operator>>(istream &in, tuple<Ts...> &t) {
    return readTupleImpl<0>(in, t);
}

template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) { return out << p.first << " " << p.second; }
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &arr) {
    for (const T &a : arr) out << a << " ";
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, const vector<vector<T>> &grid) {
    for (const vector<T> &row : grid) out << row << '\n';
    return out;
}
template <typename T>
istream &operator>>(istream &in, vector<T> &arr) {
    for (T &a : arr) in >> a;
    return in;
}
template <typename T>
void read_pair(vector<pair<T, int>> &a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
}
template <typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
    in >> a.first >> a.second;
    return in;
}

// Error handling for out of bounds
template <typename T>
class vec : public std::vector<T> {
    static_assert(!is_same_v<bool, T>, "vec cannot accept bool type. Please use vector<bool> instead");

   public:
    using std::vector<T>::vector;
    T &operator[](int i) {
        return std::vector<T>::at(i);
    }
    const T &operator[](int i) const {
        return std::vector<T>::at(i);
    }
};

constexpr bool PRINT_EXEC_TIME = true;
constexpr bool EXTERNAL_INPUT = false;
constexpr bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "cases.txt";
const char *OUTPUT_FILE = "output.txt";

constexpr int MAXN = 1e5 + 10;

template <typename T>
int sgn(T v) { return (v > 0) - (v < 0); }

template <typename T>
struct Point {
    using P = Point;
    T x, y;
    explicit Point(T x_ = 0, T y_ = 0) : x{x_}, y{y_} {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P rotate(double a) const { return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    double dist() const { return sqrt((double)dist2()); }
    T dist2() const { return x * x + y * y; }
};
template <typename P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template <typename T>
T polygonArea(vector<Point<T>> &v) {
    T a = v.back().cross(v[0]);
    for (int i = 0; i < len(v) - 1; i++)
        a += v[i].cross(v[i + 1]);
    return fabs(a) * 0.5;
}

using P = Point<double>;

double rat(P a, P b) { return sgn(b.x) ? a.x / b.x : a.y / b.y; }
double polyUnion(vector<vector<P>> &poly) {
    double ret = 0;
    for (int i = 0; i < len(poly); i++)
        for (int v = 0; v < len(poly[i]); v++) {
            P A = poly[i][v], B = poly[i][(v + 1) % len(poly[i])];
            vector<pair<double, int>> segs = {{0, 0}, {1, 0}};
            for (int j = 0; j < len(poly); j++)
                if (i != j) {
                    for (int u = 0; u < len(poly[j]); u++) {
                        P C = poly[j][u], D = poly[j][(u + 1) % len(poly[j])];
                        int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
                        if (sc != sd) {
                            double sa = C.cross(D, A), sb = C.cross(D, B);
                            if (min(sc, sd) < 0)
                                segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
                        } else if (!sc && !sd && j < i && sgn((B - A).dot(D - C)) > 0) {
                            segs.emplace_back(rat(C - A, B - A), 1);
                            segs.emplace_back(rat(D - A, B - A), -1);
                        }
                    }
                }
            sort(begin(segs), end(segs));
            for (auto &s : segs) s.first = min(max(s.first, 0.0), 1.0);
            double sum = 0;
            int cnt = segs[0].second;
            for (int j = 1; j < len(segs); j++) {
                if (!cnt) sum += segs[j].first - segs[j - 1].first;
                cnt += segs[j].second;
            }
            ret += A.cross(B) * sum;
        }
    return ret / 2;
}

void prayGod() {
    int n, m;
    cin >> n >> m;
    vec<P> object(n), container(m);
    for (int i = 0; i < n; i++) {
        cin >> object[i].x >> object[i].y;
    }
    for (int i = 0; i < m; i++) {
        cin >> container[i].x >> container[i].y;
    }
    auto container_area = polygonArea(container);
    for (int degree = 0; degree < 360; degree++) {
        vector<P> rotated_object(n);
        transform(begin(object), end(object), begin(rotated_object), [&](const P &p) {
            return p.rotate(PI * ld(degree) / 180.0);
        });
        vector<vector<P>> polygons{container, rotated_object};
        auto union_area = polyUnion(polygons);
        if (fabs(union_area - container_area) <= 1e-9) {
            cout << degree << '\n';
            return;
        }
    }

    cout << "impossible" << '\n';
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