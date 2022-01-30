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

bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a' ||
           c == 'e' ||
           c == 'i' ||
           c == 'o' ||
           c == 'u';
}

ll total_suff[100010];
ll suff[100010][10];

ll suff_vowel[100010][10];
ll suff_consonant[100010][42];

const char vowels[] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};
const char consonants[] = {'b', 'B', 'c', 'C', 'd', 'D', 'f', 'F', 'g', 'G', 'h', 'H', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z'};
ll ccount[10];
int cidx[52];

void prayGod() {
    string s;
    cin >> s;
    int n = len(s);

    for (int i = 0; i < 10; i++) {
        if (vowels[i] >= 97)
            cidx[vowels[i] - 97] = i;
        else
            cidx[vowels[i] - 65 + 26] = i;
    }

    for (int i = 0; i < 42; i++) {
        if (consonants[i] >= 97)
            cidx[consonants[i] - 97] = i;
        else
            cidx[consonants[i] - 65 + 26] = i;
    }

    for (int i = n - 1; i >= 0; i--) {
        int idx = s[i] >= 97 ? s[i] - 97 : s[i] - 65 + 26;
        if (is_vowel(s[i])) {
            int curr = cidx[idx];
            ccount[curr] = (ccount[curr] + 1) % mod;
        } else {
            int curr = cidx[idx];
            for (int j = 0; j < 10; j++) {
                suff_consonant[i][curr] = (suff_consonant[i][curr] + ccount[j]) % mod;
                total_suff[i] = (total_suff[i] + ccount[j]) % mod;
                suff_vowel[i][j] = (suff_vowel[i][j] + ccount[j]) % mod;
            }
        }
        if (i + 1 < n) {
            total_suff[i] = (total_suff[i] + total_suff[i + 1]) % mod;
            for (int j = 0; j < 10; j++) {
                suff_vowel[i][j] = (suff_vowel[i][j] + suff_vowel[i + 1][j]) % mod;
            }
            for (int j = 0; j < 42; j++) {
                suff_consonant[i][j] = (suff_consonant[i][j] + suff_consonant[i + 1][j]) % mod;
            }
        }
    }

    ll ret = 0;

    for (int x2 = 0; x2 < 42; x2++) {
        memset(ccount, 0, sizeof(ccount));
        for (int i = n - 1; i >= 0; i--) {
            int idx = s[i] >= 97 ? s[i] - 97 : s[i] - 65 + 26;
            for (int j = 0; j < 10 && i + 1 < n; j++) {
                suff[i][j] = suff[i + 1][j];
            }
            if (s[i] == consonants[x2]) {
                for (int j = 0; j < 10; j++) {
                    suff[i][j] = (suff[i][j] + ccount[j]) % mod;
                }
            } else if (is_vowel(s[i])) {
                ccount[cidx[idx]] = (ccount[cidx[idx]] + 1) % mod;
            }
        }
        for (int x1 = 0; x1 < 10; x1++) {
            ll dp = 0, pref = 0;
            for (int i = 0; i < n; i++) {
                int idx = s[i] >= 97 ? s[i] - 97 : s[i] - 65 + 26;
                if (s[i] == consonants[x2] && i - 1 >= 0) {
                    pref = (pref + dp) % mod;
                }
                if (is_vowel(s[i]) && i >= 2 && i < n - 2 && s[i] != vowels[x1]) {
                    ll cnt = suff_vowel[i + 1][x1] + suff_consonant[i + 1][x2] - suff[i + 1][x1];
                    cnt = cnt + suff_vowel[i + 1][cidx[idx]] - suff[i + 1][cidx[idx]];
                    cnt %= mod;
                    ll right_side = (total_suff[i + 1] - cnt + mod) % mod;
                    ll left_side = pref;
                    ret = (ret + left_side * right_side) % mod;
                }
                if (s[i] == vowels[x1]) dp = (dp + 1) % mod;
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
