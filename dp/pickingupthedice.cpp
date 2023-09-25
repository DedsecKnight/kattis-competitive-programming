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

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

void prayGod() {
    int k, t;
    cin >> k >> t;
    vec<int> dices(k);
    cin >> dices;
    int total = accumulate(dices.begin(), dices.end(), 0);

    vec<vec<ll>> dp(k + 1, vec<ll>(t + 1));
    dp[0][0] = 1;

    vector<vector<vector<int>>> possible(k+1, vector<vector<int>>(k+1, vector<int>(t+1, -1)));
    function<bool(int, int, int)> check = [&](int i, int j, int z) {
      if (possible[i][j][z] != -1) return bool(possible[i][j][z]);
      if (i == 0) return bool(possible[i][j][z] = z == 0);
      if (j == 0) return bool(possible[i][j][z] = i == 0 && z == 0);
      
      int ret = check(i, j-1, z);
      if (z - dices[j-1] >= 0) ret = ret || check(i-1, j-1, z-dices[j-1]);
      return bool(possible[i][j][z] = ret);
    };

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= t; j++) {
            for (int z = 1; z <= 6; z++) {
                if (j - z >= 0)
                    dp[i][j] += dp[i - 1][j - z];
                else
                    break;
            }
        }
    }

    vec<ll> pow6(k + 1);
    pow6[0] = 1;

    for (int i = 1; i <= k; i++) {
        pow6[i] = pow6[i - 1] * 6;
    }

    ld best_prob = 0.0;
    int ret = 1e9 + 10;
    
    for (int remain_dices = 0; remain_dices <= k; remain_dices++) {
        for (int remain_sum = 0; remain_sum <= t; remain_sum++) {
            if (!check(k-remain_dices, k, t-remain_sum)) continue;
            auto curr_prob = (ld) dp[remain_dices][remain_sum] / pow6[remain_dices];
            if (curr_prob > best_prob) {
                best_prob = curr_prob;
                ret = remain_dices;
            } else if (curr_prob == best_prob) {
                ret = min(ret, remain_dices);
            }
        }
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
