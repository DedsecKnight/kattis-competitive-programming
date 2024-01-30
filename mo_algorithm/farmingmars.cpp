#include <bits/stdc++.h>

using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")

#define len(a) static_cast<int>((a).size())
using ll = int64_t;
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

static constexpr const int BSZ = 700;

struct query {
    int lb, rb, idx;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    std::hash<string> hash_generator{};
    vector<size_t> hashes;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        auto h = hash_generator(s);
        hashes.push_back(h);
    }
    vector<query> queries(m);
    for (int i = 0; i < m; i++) {
        cin >> queries[i].lb >> queries[i].rb;
        queries[i].lb--, queries[i].rb--;
        queries[i].idx = i;
    }
    sort(queries.begin(), queries.end(), [](const auto& x, const auto& y) {
        return make_pair(x.lb / BSZ, x.rb) < make_pair(y.lb / BSZ, y.rb);
    });
    vector<bool> ret(m);
    map<int, int> freq_cnt;
    unordered_map<size_t, int> cnt;
    auto add = [&](int idx) {
        if (--freq_cnt[cnt[hashes[idx]]] == 0) {
            freq_cnt.erase(cnt[hashes[idx]]);
        }
        freq_cnt[++cnt[hashes[idx]]]++;
    };
    auto remove = [&](int idx) {
        if (--freq_cnt[cnt[hashes[idx]]] == 0) {
            freq_cnt.erase(cnt[hashes[idx]]);
        }
        freq_cnt[--cnt[hashes[idx]]]++;
    };
    int cur_l = 0, cur_r = -1;
    for (const auto& q : queries) {
        while (cur_l > q.lb) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.rb) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.lb) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.rb) {
            remove(cur_r);
            cur_r--;
        }
        ret[q.idx] = prev(end(freq_cnt))->first > (q.rb - q.lb + 1) / 2;
    }
    for (int i = 0; i < m; i++) {
        cout << (ret[i] ? "usable" : "unusable") << '\n';
    }
}
