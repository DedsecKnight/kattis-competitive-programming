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
const double PI = 2 * acos(0.0);

const int iinf = 0x3f3f3f3f;
const ll inf = 1000000000000000010;
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

// Error handling for out of bounds
template <class T>
class vec : public std::vector<T> {
   public:
    using std::vector<T>::vector;
    T &operator[](int i) {
        return std::vector<T>::at(i);
    }
    const T &operator[](int i) const {
        return std::vector<T>::at(i);
    }
};

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "cases.txt";
const char *OUTPUT_FILE = "output.txt";

struct SegmentTree {
    vec<ll> tag, total, pref;
    int arr_size;
    int iter_count, query_count;

    SegmentTree(const vec<ll> &event_point) {
        arr_size = len(event_point);
        iter_count = query_count = 0;
        tag.assign(arr_size * 4, 0ll);
        total.assign(arr_size * 4, 0ll);
        for (int i = 0; i < len(event_point) - 1; i++) {
            pref.push_back(ll(event_point[i + 1] - event_point[i]));
        }
        pref.push_back(0ll);
        for (int i = 1; i < len(pref); i++) {
            pref[i] += pref[i - 1];
        }
    }

    ll eval(int curr_l, int curr_r) {
        ll ret = pref[curr_r];
        if (curr_l - 1 >= 0) ret -= pref[curr_l - 1];
        return ret;
    }

    ll update(int idx, int curr_l, int curr_r, int l, int r, ll x) {
        if (curr_l > r || curr_r < l) return 0;

        if (curr_l >= l && curr_r <= r) {
            tag[idx] += x;
        } else {
            int mid = curr_l + (curr_r - curr_l) / 2;
            update(idx * 2 + 1, curr_l, mid, l, r, x);
            update(idx * 2 + 2, mid + 1, curr_r, l, r, x);
        }

        if (tag[idx] > 0)
            total[idx] = eval(curr_l, curr_r);
        else {
            ll left = idx * 2 + 1 < len(tag) ? total[idx * 2 + 1] : 0;
            ll right = idx * 2 + 2 < len(tag) ? total[idx * 2 + 2] : 0;
            total[idx] = left + right;
        }

        return total[idx];
    }

    ll update(int l, int r, ll x) {
        return update(0, 0, arr_size - 1, l, r, x);
    }
};

void prayGod() {
    int n;
    cin >> n;
    set<ll> seen_y;
    vec<pair<pair<ll, ll>, pair<ll, ll>>> rects;
    for (int i = 0; i < n; i++) {
        ll x1, y1;
        cin >> x1 >> y1;
        ll x2, y2;
        cin >> x2 >> y2;
        seen_y.insert(y1);
        seen_y.insert(y2);
        rects.emplace_back(make_pair(x1, y1), make_pair(x2, y2));
    }

    vec<ll> pos(seen_y.begin(), seen_y.end());
    umap<ll, int> discrete;

    for (ll i = 0; i < len(pos); i++) {
        discrete[pos[i]] = i;
    }

    SegmentTree tree(pos);
    vec<pair<pair<ll, ll>, pair<int, int>>> intervals;

    for (auto &r : rects) {
        ll x1 = r.first.first, x2 = r.second.first;
        int y1 = discrete[r.first.second], y2 = discrete[r.second.second];
        intervals.emplace_back(make_pair(x1, 1), make_pair(y1, y2));
        intervals.emplace_back(make_pair(x2, -1), make_pair(y1, y2));
    }

    sort(intervals.begin(), intervals.end());

    ll prevX = intervals[0].first.first;
    ll curr_total = 0;
    ll ret = 0;

    for (auto &i : intervals) {
        ret += curr_total * (i.first.first - prevX);
        curr_total = tree.update(i.second.first, i.second.second - 1, i.first.second);
        prevX = i.first.first;
    }

    cout << ret << '\n';
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
