#include <bits/stdc++.h>

using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")

#define len(a) static_cast<int>((a).size())
using ll = long long;
using ld = long double;
constexpr const int iinf = 1e9 + 7;
constexpr const ll inf = 1e18;
constexpr const ll mod = 1'000'000'007;
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

ll modpow(ll b, ll e) {
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1)
            ans = ans * b % mod;
    return ans;
}

template <typename T>
struct SegmentTree {
    vector<T> tree, mset;
    explicit SegmentTree(int n, T init = T{})
        : tree(4 * n, init), mset(4 * n, -1) {}
    void set(int idx, int curr_l, int curr_r, int l, int r, T x) {
        if (curr_r < l || r < curr_l) {
            return;
        }
        if (l <= curr_l && curr_r <= r) {
            mset[idx] = x;
            tree[idx] = modpow(x, curr_r - curr_l + 1);
        } else {
            propagate(idx, curr_l, curr_r);
            auto mid = curr_l + (curr_r - curr_l) / 2;
            set(idx * 2 + 1, curr_l, mid, l, r, x);
            set(idx * 2 + 2, mid + 1, curr_r, l, r, x);
            tree[idx] = tree[idx * 2 + 1] * tree[idx * 2 + 2] % mod;
        }
    }
    void propagate(int idx, int curr_l, int curr_r) {
        if (curr_l > curr_r)
            return;
        if (mset[idx] != -1) {
            auto mid = curr_l + (curr_r - curr_l) / 2;
            set(idx * 2 + 1, curr_l, mid, curr_l, curr_r, mset[idx]);
            set(idx * 2 + 2, mid + 1, curr_r, curr_l, curr_r, mset[idx]);
            mset[idx] = -1;
        }
    }
    T query(int idx, int curr_l, int curr_r, int l, int r) {
        if (r < curr_l || curr_r < l || curr_l > curr_r)
            return T{1};
        if (l <= curr_l && curr_r <= r) {
            return tree[idx];
        }
        propagate(idx, curr_l, curr_r);
        auto mid = curr_l + (curr_r - curr_l) / 2;
        auto left = query(idx * 2 + 1, curr_l, mid, l, r);
        auto right = query(idx * 2 + 2, mid + 1, curr_r, l, r);
        return left * right % mod;
    }
};

struct FakeLinkCutTree {
    SegmentTree<int> leader;
    SegmentTree<ll> value_tree;
    vector<int> last;
    ll sum;
    int sz;
    explicit FakeLinkCutTree(int n)
        : leader{n}, value_tree{n, 1}, last(n), sum{}, sz{n} {}
    void set_value(int index, ll value) {
        leader.set(0, 0, sz - 1, index, index, index);
        last[index] = index;
        value_tree.set(0, 0, sz - 1, index, index, value);
        sum += value;
    }
    void link(int i, int j) {
        auto leader_i = leader.query(0, 0, sz - 1, i, i);
        sum = (sum - value_tree.query(0, 0, sz - 1, leader_i, last[leader_i]) +
               mod * 10000) %
              mod;

        sum = (sum - value_tree.query(0, 0, sz - 1, j, last[j]) + mod * 10000) %
              mod;
        leader.set(0, 0, sz - 1, j, last[j], leader_i);
        last[leader_i] = last[j];
        last[j] = -1;
        sum = (sum + value_tree.query(0, 0, sz - 1, leader_i, last[leader_i])) %
              mod;
    }
    void cut(int i, int j) {
        auto curr_leader = leader.query(0, 0, sz - 1, i, i);
        auto rb = last[curr_leader];
        sum = (sum - value_tree.query(0, 0, sz - 1, curr_leader, rb) +
               mod * 10000) %
              mod;
        leader.set(0, 0, sz - 1, j, rb, j);
        last[j] = rb;
        last[curr_leader] = i;
        sum = (sum + value_tree.query(0, 0, sz - 1, curr_leader, i)) % mod;
        sum = (sum + value_tree.query(0, 0, sz - 1, j, rb)) % mod;
    }
    ll get_sum() { return sum; }
    void swap_value(int i, int j) {
        auto leader_i = leader.query(0, 0, sz - 1, i, i);
        auto leader_j = leader.query(0, 0, sz - 1, j, j);
        if (leader_i != leader_j) {
            sum = (sum -
                   value_tree.query(0, 0, sz - 1, leader_i, last[leader_i]) +
                   mod * 10000) %
                  mod;
            sum = (sum -
                   value_tree.query(0, 0, sz - 1, leader_j, last[leader_j]) +
                   mod * 10000) %
                  mod;
        }
        auto old_i = value_tree.query(0, 0, sz - 1, i, i);
        auto old_j = value_tree.query(0, 0, sz - 1, j, j);
        value_tree.set(0, 0, sz - 1, i, i, old_j);
        value_tree.set(0, 0, sz - 1, j, j, old_i);
        if (leader_i != leader_j) {
            sum = (sum +
                   value_tree.query(0, 0, sz - 1, leader_i, last[leader_i])) %
                  mod;
            sum = (sum +
                   value_tree.query(0, 0, sz - 1, leader_j, last[leader_j])) %
                  mod;
        }
    }
    void swap(FakeLinkCutTree& other) {
        leader.tree.swap(other.leader.tree);
        leader.mset.swap(other.leader.mset);
        value_tree.tree.swap(other.value_tree.tree);
        value_tree.mset.swap(other.value_tree.mset);
        last.swap(other.last);
        std::swap(sum, other.sum);
        std::swap(sz, other.sz);
    }
    void initialize_sum() {
        sum = 0;
        for (int i = 0; i < sz; i++) {
            if (last[i] != -1)
                sum = (sum + value_tree.query(0, 0, sz - 1, i, last[i])) % mod;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    string rev_s{s};
    for (char& c : rev_s) {
        if (c == '+')
            c = '*';
        else if (c == '*')
            c = '+';
    }
    FakeLinkCutTree fwd{n}, rev{n};
    for (int i = 0, j = 0; i < len(s); i += 2, j++) {
        fwd.set_value(j, ll(s[i] - '0'));
        rev.set_value(j, ll(s[i] - '0'));
    }
    for (int i = 0; i < n - 1; i++) {
        if (s[i * 2 + 1] == '+') {
            rev.link(i, i + 1);
        } else {
            fwd.link(i, i + 1);
        }
    }
    fwd.initialize_sum();
    rev.initialize_sum();
    cout << fwd.get_sum() << '\n';
    while (m--) {
        char op;
        cin >> op;
        if (op == 's') {
            int i, j;
            cin >> i >> j;
            fwd.swap_value(--i, --j);
            rev.swap_value(i, j);
        } else if (op == 'f') {
            int i;
            cin >> i;
            i--;
            if (s[i * 2 + 1] == '+') {
                fwd.link(i, i + 1);
                rev.cut(i, i + 1);
            } else {
                rev.link(i, i + 1);
                fwd.cut(i, i + 1);
            }
            s[i * 2 + 1] = (s[i * 2 + 1] == '+' ? '*' : '+');
            rev_s[i * 2 + 1] = (rev_s[i * 2 + 1] == '+' ? '*' : '+');
        } else {
            fwd.swap(rev);
            s.swap(rev_s);
        }
        cout << fwd.get_sum() << '\n';
    }
}
