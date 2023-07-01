#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

#define len(a) int((a).size())

#define printDecimal(d) \
    cout << setprecision(d) << fixed

struct SegmentTree {
    static constexpr const int inf = 1e9 + 10;
    vector<int> tree, mset, madd;
    int arr_size;
    explicit SegmentTree(int n) : tree(4*n), mset(4*n, inf), madd(4*n, 0), arr_size(n) {}
    int query(int idx, int curr_l, int curr_r, int l, int r) {
        if (r < curr_l || curr_r < l || curr_l > curr_r) return 0;
        if (l <= curr_l && curr_r <= r) return tree[idx];
        push(idx, curr_l, curr_r);
        auto mid = curr_l + (curr_r - curr_l) / 2;
        auto left = query(idx*2+1, curr_l, mid, l, r);
        auto right = query(idx*2+2, mid+1, curr_r, l, r);
        return left + right;
    }
    void set(int idx, int curr_l, int curr_r, int l, int r, int x) {
        if (r < curr_l || curr_r < l || curr_l > curr_r) return;
        if (l <= curr_l && curr_r <= r) {
            mset[idx] = x;
            tree[idx] = x * (curr_r - curr_l + 1);
            madd[idx] = 0;
        } else {
            push(idx, curr_l, curr_r);
            auto mid = curr_l + (curr_r - curr_l) / 2;
            set(idx*2+1, curr_l, mid, l, r, x);
            set(idx*2+2, mid+1, curr_r, l, r, x);
            tree[idx] = tree[idx*2+1] + tree[idx*2+2];
        }
    }
    void add(int idx, int curr_l, int curr_r, int l, int r, int x) {
        if (r < curr_l || curr_r < l || curr_l > curr_r) return;
        if (l <= curr_l && curr_r <= r) {
            if (mset[idx] != inf) mset[idx] += x;
            else madd[idx] += x;
            tree[idx] += x * (curr_r - curr_l + 1);
        } else {
            push(idx, curr_l, curr_r);
            auto mid = curr_l + (curr_r - curr_l)/2;
            add(idx*2+1, curr_l, mid, l, r, x);
            add(idx*2+2, mid+1, curr_r, l, r, x);
            tree[idx] = tree[idx*2+1] + tree[idx*2+2];
        }
    }
    void push(int idx, int curr_l, int curr_r) {
        auto mid = curr_l + (curr_r - curr_l) / 2;
        if (mset[idx] != inf) {
            set(idx*2+1, curr_l, mid, curr_l, curr_r, mset[idx]);
            set(idx*2+2, mid+1, curr_r, curr_l, curr_r, mset[idx]);
            mset[idx] = inf;
        } else if (madd[idx]) {
            add(idx*2+1, curr_l, mid, curr_l, curr_r, madd[idx]);
            add(idx*2+2, mid+1, curr_r, curr_l, curr_r, madd[idx]);
            madd[idx] = 0;
        }
    }
};

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    int n; cin >> n;
    vector<double> events, a(n), b(n);
    vector<pair<double, double>> hills;
    hills.reserve(n);
    events.reserve(2*n);
    auto f = [&](int i, double x) -> double {
        return -(x*x*x)/3 + a[i] * x * x + x * (b[i] - a[i] * a[i]);
    }; 
    double ret = 0.0;
    for (int i = 0;i<n; i++) {
        cin >> a[i] >> b[i];
        hills.emplace_back(a[i]-sqrt(b[i]), a[i]+sqrt(b[i]));
        ret += f(i, hills.back().second) - f(i, hills.back().first);
        events.push_back(hills.back().first);
        events.push_back(hills.back().second);
    }
    sort(begin(events), end(events));
    events.erase(unique(begin(events), end(events)), end(events));
    SegmentTree cnt(len(events)), mark(len(events));
    for (int i = 0; i<n; i++) {
        auto [lb, rb] = hills[i];
        auto lidx = lower_bound(begin(events), end(events), lb) - begin(events);
        auto ridx = lower_bound(begin(events), end(events), rb) - begin(events);
        cnt.add(0, 0, len(events)-1, lidx, ridx-1, 1);
        mark.set(0, 0, len(events)-1, lidx, ridx-1, i);
    } 
    for (int i = 0;i<len(events)-1; i++) {
        auto ccnt = cnt.query(0, 0, len(events)-1, i, i);
        if (ccnt == 1) {
            auto idx = mark.query(0, 0, len(events)-1, i, i);
            ret -= f(idx, events[i+1]) - f(idx, events[i]);
        }
    }
    printDecimal(8) << ret << '\n';
}
