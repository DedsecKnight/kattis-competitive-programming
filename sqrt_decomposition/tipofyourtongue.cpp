#include <bits/stdc++.h>

using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")

#define len(a) static_cast<int>((a).size())
using ll = long long;
using ld = long double;
constexpr const int iinf = 1e9 + 7;
constexpr const ll inf = 1e18;
constexpr const ll mod = 998244353;
#define printDecimal(d) std::cout << std::setprecision(d) << std::fixed

template <typename Fun>
class y_combinator_result {
    Fun fun_;

   public:
    template <typename T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <typename... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
template <typename Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

struct query {
    string op, pref, suff;
};

using ull = uint64_t;
struct H {
    ull x;
    H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) {
        auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64);
    }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3;

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(const string& str) : ha(len(str) + 1), pw(ha) {
        pw[0] = 1;
        for (int i = 0; i < len(str); i++) {
            ha[i + 1] = ha[i] * C + str[i];
            pw[i + 1] = pw[i] * C;
        }
    }
    H hashInterval(int a, int b) { return ha[b] - ha[a] * pw[b - a]; }
};

H hashString(const string& s) {
    H h{};
    for (char c : s)
        h = h * C + c;
    return h;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<string> dictionary(n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        cin >> dictionary[i];
        m = max(m, len(dictionary[i]));
    }
    vector<bool> need(m + 1, false);
    vector<query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].op >> queries[i].pref >> queries[i].suff;
        if (len(queries[i].pref) <= m) {
            need[len(queries[i].pref)] = true;
        }
    }
    vector<int> special;
    for (int i = 1; i <= m; i++) {
        if (need[i])
            special.push_back(i);
    }
    vector<map<H, int>> by_pref(m + 1), by_suff(m + 1);
    vector<map<pair<H, H>, int>> by_ps_pair(m + 1);
    for (const auto& s : dictionary) {
        HashInterval hi{s};
        for (auto val : special) {
            if (val <= len(s)) {
                auto pref = hi.hashInterval(0, val);
                auto suff = hi.hashInterval(len(s) - val, len(s));
                by_pref[val][pref]++;
                by_suff[val][suff]++;
                by_ps_pair[val][make_pair(pref, suff)]++;
            }
        }
    }
    for (const auto& query : queries) {
        if (len(query.pref) > m) {
            cout << 0 << '\n';
        } else {
            auto pref_hash = hashString(query.pref);
            auto suff_hash = hashString(query.suff);
            if (query.op == "AND") {
                cout << by_ps_pair[len(query.pref)]
                                  [make_pair(pref_hash, suff_hash)]
                     << '\n';
            } else if (query.op == "OR") {
                cout << by_pref[len(query.pref)][pref_hash] +
                            by_suff[len(query.suff)][suff_hash] -
                            by_ps_pair[len(query.suff)]
                                      [make_pair(pref_hash, suff_hash)]
                     << '\n';
            } else {
                cout << by_pref[len(query.pref)][pref_hash] +
                            by_suff[len(query.suff)][suff_hash] -
                            2 * by_ps_pair[len(query.suff)]
                                          [make_pair(pref_hash, suff_hash)]
                     << '\n';
            }
        }
    }
}
