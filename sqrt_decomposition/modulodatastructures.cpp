#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

#define len(a) int((a).size())
using ll = long long;
constexpr const int iinf = 1e9 + 7;

#define printDecimal(d) \
    cout << setprecision(d) << fixed

constexpr const int bound = 500;
array<array<int, bound>, bound> lazy{};
array<int, 200001> arr{};

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    int n,q; cin >> n >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int a,b,c; cin >> a >> b >> c;
            if (b < bound) lazy[b][a] += c;
            else {
                for (int i = a; i <= n; i += b) arr[i] += c;
            }
        } else {
            int d; cin >> d;
            auto ret = arr[d];
            for (int i = 1; i<bound; i++) {
                ret += lazy[i][d % i];
            }
            cout << ret << '\n';
        }
    }
}
