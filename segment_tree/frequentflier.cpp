#include <bits/stdc++.h>
#include <type_traits>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;
using ll = long long;

constexpr int iinf = 0x3f3f3f3f;
constexpr ll mod = 1e9 + 7;

template <typename T>
struct SegmentTree {
    vector<T> tree, mset;
    explicit SegmentTree(int n) : tree(4*n), mset(4*n, iinf) {}
    void set(int idx, int curr_l, int curr_r, int l, int r, T x) {
        if (r < curr_l || curr_r < l) return;
        if (l <= curr_l && curr_r <= r) {
            mset[idx] = x;
            tree[idx] = (curr_r - curr_l + 1) * 1ll * x;
        }
        else {
            push(idx, curr_l, curr_r);
            auto mid = curr_l+(curr_r-curr_l)/2;
            set(idx*2+1, curr_l, mid, l, r, x);
            set(idx*2+2, mid+1, curr_r, l, r, x);
            tree[idx] =  tree[idx*2+1] + tree[idx*2+2];  
        }
    }
    void push(int idx, int curr_l, int curr_r) {
        if (mset[idx] != iinf) {
            auto mid = curr_l + (curr_r - curr_l) / 2;
            set(idx*2+1, curr_l, mid, curr_l, curr_r, mset[idx]);
            set(idx*2+2, mid+1, curr_r, curr_l, curr_r, mset[idx]);
            mset[idx] = iinf;
        }
    }
    T query(int idx, int curr_l, int curr_r, int l, int r) {
        if (r < curr_l || curr_r < l) return 0;
        if (l <= curr_l && curr_r <= r) return tree[idx];
        push(idx, curr_l, curr_r);
        auto mid = curr_l+(curr_r-curr_l)/2;
        auto left = query(idx*2+1, curr_l, mid, l, r);
        auto right = query(idx*2+2, mid+1, curr_r, l, r);
        return left + right; 
    } 
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m,k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    for (int i = 0;i<n; i++) cin >> a[i];
    SegmentTree<ll> tree(n);
    ll curr = 0, ret = 0;
    for (int i = 0;i<n+m-1; i++) {
        if (i < n) tree.set(0, 0, n-1, i, i, a[i]);
        if (i-m >= 0) {
            curr -= a[i-m] - tree.query(0, 0, n-1, i-m, i-m);
        }
        auto target = max(0ll, k-curr);
        if (target == 0) continue;
        int low = i-m+1, high = i+1, best = -1;
        while (low <= high) {
            auto mid = low + (high - low) / 2;
            auto val = tree.query(0,0,n-1,mid,i);
            if (val >= target) {
                best = mid;
                low = mid+1;
            } else {
                high = mid-1;
            }
        }
        if (best == -1) {
            auto subsum = tree.query(0,0,n-1,i-m+1,i);
            ret += subsum;
            curr += subsum;
            tree.set(0,0,n-1,i-m+1,i,0);
        } else if (best <= i) {
            auto subsum = tree.query(0, 0, n-1, best+1, i);
            auto rem = tree.query(0,0,n-1,best,best) - (target-subsum);
            curr = k;
            ret += target;
            tree.set(0,0,n-1,best+1,i,0);
            tree.set(0,0,n-1,best,best,rem);
        }  
    }
    cout << ret << '\n';
}