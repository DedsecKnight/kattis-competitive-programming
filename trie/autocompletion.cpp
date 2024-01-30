#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

using ui = unsigned int;
using ll = int64_t;
using ull = uint64_t;
using ld = long double;

template <typename K, typename V>
using umap = unordered_map<K, V>;

#define null NULL
#define len(a) static_cast<int>((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
const double PI = 2 * acos(0.0);

constexpr int iinf = 0x3f3f3f3f;
constexpr ll inf = 1'000'000'000'000'000;
constexpr ll mod = 1e9 + 7;

#define var(args...)                           \
    {                                          \
        string _s = #args;                     \
        stringstream _ss;                      \
        string ccurr = "";                     \
        for (int zz = 0; zz < len(_s); zz++) { \
            if (_s[zz] == ' ')                 \
                continue;                      \
            if (_s[zz] == ',') {               \
                _ss << ' ' + ccurr;            \
                ccurr = "";                    \
            } else {                           \
                ccurr += _s[zz];               \
            }                                  \
        }                                      \
        _ss << ' ' + ccurr;                    \
        istream_iterator<string> _it(_ss);     \
        vars(_it, args);                       \
    }
#define debugDecimal(d) cerr << setprecision(d) << fixed

void vars(istream_iterator<string> it) {
    cerr << '\n';
}
template <typename T, typename... Args>
void vars(istream_iterator<string> it, T a, Args... args) {
    cerr << " [" << *it << ": " << a << "] ";
    vars(++it, args...);
}

#define printVerdict(verdict) cout << (verdict ? "YES" : "NO") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define printCase(_) cout << "Case #" << (_) << ": "

template <int I, typename TupleT>
ostream& printTupleImpl(ostream& out, const TupleT& t) {
    if constexpr (I < tuple_size_v<TupleT>) {
        out << get<I>(t) << " ";
        printTupleImpl<I + 1, TupleT>(out, t);
    }
    return out;
}
template <typename... Ts>
ostream& operator<<(ostream& out, const tuple<Ts...>& t) {
    return printTupleImpl<0>(out, t);
}

template <int I, typename TupleT>
istream& readTupleImpl(istream& in, TupleT& t) {
    if constexpr (I < tuple_size_v<TupleT>) {
        in >> get<I>(t);
        readTupleImpl<I + 1, TupleT>(in, t);
    }
    return in;
}

template <typename... Ts>
istream& operator>>(istream& in, tuple<Ts...>& t) {
    return readTupleImpl<0>(in, t);
}

template <typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p) {
    return out << p.first << " " << p.second;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
    for (const T& a : arr)
        out << a << " ";
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& grid) {
    for (const vector<T>& row : grid)
        out << row << '\n';
    return out;
}
template <typename T>
istream& operator>>(istream& in, vector<T>& arr) {
    for (T& a : arr)
        in >> a;
    return in;
}
template <typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) {
    in >> a.first >> a.second;
    return in;
}

template <typename Fun>
class y_combinator_result {
    Fun fun_;

   public:
    template <typename T>
    explicit y_combinator_result(T&& fun) : fun_{std::forward<T>(fun)} {}

    template <typename... ArgTs>
    decltype(auto) operator()(ArgTs&&... args) {
        return fun_(std::ref(*this), std::forward<ArgTs>(args)...);
    }
};

template <typename Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<decay_t<Fun>>(std::forward<Fun>(fun));
}

struct Trie {
    struct TrieNode {
        pair<char, int> parent;
        vector<int> children, words;
        TrieNode() : children(26, -1) {}
    };
    vector<TrieNode> nodes;
    Trie() : nodes(1) {}
    void insert(const string& s) {
        int ptr = 0;
        for (const auto& c : s) {
            if (nodes[ptr].children[c - 'a'] == -1) {
                nodes[ptr].children[c - 'a'] = len(nodes);
                nodes.emplace_back();
                nodes.back().parent = make_pair(c, ptr);
            }
            ptr = nodes[ptr].children[c - 'a'];
        }
        int node_index = ptr;
        ptr = 0;
        for (const auto& c : s) {
            nodes[ptr].words.push_back(node_index);
            ptr = nodes[ptr].children[c - 'a'];
        }
    }
    vector<pair<char, int>> parse_string(const string& s) {
        vector<pair<char, int>> ret;
        for (char c : s) {
            if (c == '#' && !ret.empty() && ret.back().first == '#') {
                ret.back().second++;
            } else {
                ret.emplace_back(c, 1);
            }
        }
        return ret;
    }
    string query(const string& s) {
        auto parsed_s = parse_string(s);
        string ret = "";
        int ptr = 0;
        for (auto [c, cnt] : parsed_s) {
            if (c == '#' && !nodes[ptr].words.empty()) {
                int target_node_index =
                    nodes[ptr].words[(cnt - 1) % len(nodes[ptr].words)];
                string sub = "";
                while (target_node_index != ptr) {
                    sub += nodes[target_node_index].parent.first;
                    target_node_index = nodes[target_node_index].parent.second;
                }
                reverse(sub.begin(), sub.end());
                ret += sub;
                ptr = nodes[ptr].words[(cnt - 1) % len(nodes[ptr].words)];
            } else if (c != '#') {
                if (nodes[ptr].children[c - 'a'] == -1) {
                    nodes[ptr].children[c - 'a'] = len(nodes);
                    nodes.emplace_back();
                    nodes.back().parent = make_pair(c, ptr);
                }
                ret += c;
                ptr = nodes[ptr].children[c - 'a'];
            }
        }
        return ret;
    }
};

inline void prayGod() {
    int n;
    cin >> n;
    vector<string> words(n);
    cin >> words;
    sort(words.begin(), words.end());
    Trie trie;
    for (int i = 0; i < n; i++) {
        trie.insert(words[i]);
    }
    int q;
    cin >> q;
    while (q--) {
        string query;
        cin >> query;
        cout << trie.query(query) << '\n';
    }
}

int main() {
#ifdef LLOCAL
    clock_t start = clock();
#endif
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    prayGod();
#ifdef LLOCAL
    clock_t end = clock();

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    debugDecimal(5) << time_taken << " s" << '\n';
#endif
}
