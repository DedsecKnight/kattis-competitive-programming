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

struct Node {
    vector<Node *> children;
    bool end_word;
    Node() : end_word{false} {
        children.assign(52, nullptr);
    }
};

struct Trie {
    Node *root;
    Trie() {
        root = new Node();
    }
    void insert(const string &word) {
        Node *ptr = root;
        for (char c : word) {
            int idx = isupper(c) ? (c - 'A') : (c - 'a' + 26);
            if (!ptr->children[idx]) ptr->children[idx] = new Node();
            ptr = ptr->children[idx];
        }
        ptr->end_word = true;
    }

    int eval(const string &word, int idx, Node *node) {
        if (idx >= len(word)) {
            return node->end_word ? 0 : iinf;
        }
        if (isdigit(word[idx])) {
            int ret = iinf;
            for (Node *ptr : node->children) {
                if (!ptr) continue;
                ret = min(ret, eval(word, idx + 1, ptr) + 1);
            }
            return ret;
        } else {
            int pos = isupper(word[idx]) ? (word[idx] - 'A') : (word[idx] - 'a' + 26);
            if (!node->children[pos]) return iinf;
            return eval(word, idx + 1, node->children[pos]);
        }
    }

    int eval(const string &word) {
        return eval(word, 0, root);
    }
};

void prayGod() {
    int n;
    cin >> n;

    Trie trie;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        trie.insert(s);
    }

    function<bool(string &, int)> find = [&](string &word, int swap_cnt) {
        if (swap_cnt > 3) return false;
        int min_cost = trie.eval(word) + swap_cnt;
        if (min_cost <= 3) return true;
        for (int i = 0; i < len(word) - 1; i++) {
            swap(word[i], word[i + 1]);
            bool check = find(word, swap_cnt + 1);
            swap(word[i], word[i + 1]);
            if (check) return true;
        }
        return false;
    };

    string target;
    while (cin >> target) {
        if (!find(target, 0)) cout << target << '\n';
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
