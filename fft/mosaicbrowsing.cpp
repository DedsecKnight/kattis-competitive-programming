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

struct FFT {
    using C = complex<double>;
    using vll = vector<ll>;

    static void fft(vector<C> &a) {
        int n = len(a), L = 31 - __builtin_clz(n);
        static vector<complex<ld>> R(2, 1);
        static vector<C> rt(2, 1);
        for (static int k = 2; k < n; k *= 2) {
            R.resize(n);
            rt.resize(n);
            auto x = polar(1.0L, acos(-1.0L) / k);
            for (int i = k; i < 2 * k; i++) {
                rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
            }
        }
        vector<int> rev(n);
        for (int i = 0; i < n; i++) {
            rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        }
        for (int i = 0; i < n; i++) {
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k];
                    C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
            }
        }
    }

    template <int M>
    static vll conv(const vll &a, const vll &b) {
        if (a.empty() || b.empty()) return {};
        vll res(len(a) + len(b) - 1);
        int B = 32 - __builtin_clz(len(res)), n = 1 << B, cut = int(sqrt(M));
        vector<C> L(n), R(n), outs(n), outl(n);
        for (int i = 0; i < len(a); i++) {
            L[i] = C((int)a[i] / cut, (int)a[i] % cut);
        }
        for (int i = 0; i < len(b); i++) {
            R[i] = C((int)b[i] / cut, (int)b[i] % cut);
        }
        FFT::fft(L), FFT::fft(R);
        for (int i = 0; i < n; i++) {
            int j = -i & (n - 1);
            outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
            outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
        }
        FFT::fft(outl), FFT::fft(outs);
        for (int i = 0; i < len(res); i++) {
            ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
            ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
            res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
        }
        return res;
    }
};

struct WildcardMatching {
    vector<vector<ll>> P, T;
    WildcardMatching(const vector<int> &t, const vector<int> &p) : P(3, vector<ll>(len(p))), T(3, vector<ll>(len(t))) {
        for (int i = 0; i < len(t); i++) {
            T[0][i] = t[i];
            for (int j = 1; j < 3; j++) {
                T[j][i] = T[j - 1][i] * T[0][i];
            }
        }

        for (int i = 0; i < len(p); i++) {
            P[0][i] = p[i];
            for (int j = 1; j < 3; j++) {
                P[j][i] = P[j - 1][i] * P[0][i];
            }
        }

        for (int i = 0; i < 3; i++) {
            reverse(P[i].begin(), P[i].end());
        }
    }

    vector<ll> find_all_occurrences() {
        vector<ll> d(len(T[0]));
        for (int i = 0; i < 3; i++) {
            auto res = FFT::conv<mod>(P[i], T[2 - i]);
            for (int j = 0; j < len(T[0]); j++) {
                if (i % 2 == 0)
                    d[j] += res[len(P[0]) - 1 + j];
                else
                    d[j] -= 2 * res[len(P[0]) - 1 + j];
            }
        }
        return d;
    }
};

void prayGod() {
    int rp, cp;
    cin >> rp >> cp;
    vector<vector<int>> motif(rp, vector<int>(cp));
    cin >> motif;

    int rq, cq;
    cin >> rq >> cq;
    vector<int> grid(rq * cq);
    cin >> grid;

    vector<int> motif_1d;
    for (int i = 0; i < rp; i++) {
        for (int j = 0; j < cp; j++) {
            motif_1d.push_back(motif[i][j]);
        }
        for (int j = cp; j < cq && i != rp - 1; j++) {
            motif_1d.push_back(0);
        }
    }

    vector<pair<int, int>> ret;

    auto d = WildcardMatching(grid, motif_1d).find_all_occurrences();
    for (int i = 0; i <= rq - rp; i++) {
        for (int j = 0; j <= cq - cp; j++) {
            if (d[i * cq + j] == 0) {
                ret.emplace_back(i + 1, j + 1);
            }
        }
    }

    cout << len(ret) << '\n';
    for (const auto &[i, j] : ret) {
        cout << i << " " << j << '\n';
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