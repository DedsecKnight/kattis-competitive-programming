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
constexpr ll inf = 1000000000000000010;
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

void prayGod() {
    int n;
    double l;
    cin >> n >> l;
    vector<double> pos(n);
    cin >> pos;

    sort(pos.begin(), pos.end());

    vector<double> relative_pos(n, 0.0);
    for (int i = 0; i < n; i++) {
        relative_pos[i] = pos.back() - pos[i];
    }

    vector<pair<double, double>> ranges;

    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            auto dist = relative_pos[i] - relative_pos[j];
            double curr_l = l - 1, curr_r = l + 1;
            ranges.emplace_back(dist + 1e-10, 1e15);
            while (true) {
                auto lb = dist / curr_r + 1e-10 + 0.0, rb = dist / curr_l - 1e-10 + 0.0;
                curr_l = curr_l + l + 0.0, curr_r = curr_r + l + 0.0;
                if (0.1 > rb) break;
                ranges.emplace_back(max(0.1, lb), rb);
            }
        }
    }

    sort(ranges.begin(), ranges.end());
    vector<pair<double, double>> merged;
    if (ranges.empty()) {
        printDecimal(10) << 10.0 << '\n';
        return;
    }
    auto s = ranges[0].first, e = ranges[0].second;

    for (int i = 1; i < len(ranges); i++) {
        if (ranges[i].first - e > 1e-9) {
            merged.emplace_back(s, e);
            s = ranges[i].first, e = ranges[i].second;
        } else {
            s = min(s, ranges[i].first);
            e = max(e, ranges[i].second);
        }
    }
    merged.emplace_back(s, e);

    bool found = false;
    double ret = 0.0;

    for (int i = len(merged) - 1; i > 0; i--) {
        auto candidate = merged[i].first - 1e-9;
        if (candidate > merged[i - 1].second && ret - 10.0 <= 1e-9) {
            ret = candidate;
            found = true;
            break;
        }
    }

    if (!found && inrange(merged[0].first - 1e-9, 0.1, 10.0)) {
        found = true;
        ret = merged[0].first - 1e-9;
    }

    if (!found)
        cout << "no fika" << '\n';
    else
        printDecimal(10) << ret << '\n';
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