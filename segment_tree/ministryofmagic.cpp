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

struct SegmentTreeMin {
    vector<int> tree;
    int arr_size;

    SegmentTreeMin(int n) {
        arr_size = n;
        int sz = 1;
        while (sz < n) sz *= 2;
        tree.assign(2 * sz + 1, 0);
    }

    void set(int idx, int curr_l, int curr_r, int i, int x) {
        if (curr_l > curr_r) return;
        if (curr_l == curr_r) {
            tree[idx] = x;
            return;
        }
        int mid = curr_l + (curr_r - curr_l) / 2;
        if (i <= mid)
            set(idx * 2 + 1, curr_l, mid, i, x);
        else
            set(idx * 2 + 2, mid + 1, curr_r, i, x);
        tree[idx] = min(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }

    void set(int i, int x) {
        set(0, 0, arr_size - 1, i, x);
    }

    int getMinIdx(int idx, int curr_l, int curr_r) {
        if (curr_l > curr_r) return -1;
        if (curr_l == curr_r) return curr_l;

        int mid = curr_l + (curr_r - curr_l) / 2;
        if (tree[idx * 2 + 1] <= tree[idx * 2 + 2]) {
            return getMinIdx(idx * 2 + 1, curr_l, mid);
        } else {
            return getMinIdx(idx * 2 + 2, mid + 1, curr_r);
        }
    }

    int getMinIdx() {
        return getMinIdx(0, 0, arr_size - 1);
    }
};

void prayGod() {
    int c, p;
    cin >> c >> p;

    vector<vector<int>> preference(p, vector<int>(c));
    vector<int> ptr(p, 0), weight(p);

    SegmentTreeMin tree(c);

    vector<int> current_vote(c, 0);

    for (int i = 0; i < p; i++) {
        cin >> weight[i];
        for (int j = 0; j < c; j++) {
            cin >> preference[i][j];
            preference[i][j]--;
        }
    }

    int sum_weight = accumulate(weight.begin(), weight.end(), 0);

    for (int _ = 0; _ < c - 1; _++) {
        auto comp = [&](int a, int b) {
            if (current_vote[a] != current_vote[b]) return current_vote[a] > current_vote[b];
            return a < b;
        };

        set<int, decltype(comp)> chosen(comp);
        for (int i = 0; i < p; i++) {
            while (ptr[i] < c && current_vote[preference[i][ptr[i]]] == iinf) ptr[i]++;

            current_vote[preference[i][ptr[i]]] += weight[i];
            tree.set(preference[i][ptr[i]], current_vote[preference[i][ptr[i]]]);

            chosen.erase(preference[i][ptr[i]]);
            chosen.insert(preference[i][ptr[i]]);
        }

        int best_candidate = *chosen.begin();

        if (current_vote[best_candidate] * 2 > sum_weight) {
            cout << best_candidate + 1 << '\n';
            return;
        }

        int eliminated = tree.getMinIdx();
        current_vote[eliminated] = iinf;

        tree.set(eliminated, iinf);

        for (int i = 0; i < p; i++) {
            if (preference[i][ptr[i]] == eliminated) continue;
            current_vote[preference[i][ptr[i]]] -= weight[i];
            tree.set(preference[i][ptr[i]], current_vote[preference[i][ptr[i]]]);
        }
    }

    for (int i = 0; i < c; i++) {
        if (current_vote[i] != iinf) {
            cout << i + 1 << '\n';
            return;
        }
    }

    assert(false);
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
