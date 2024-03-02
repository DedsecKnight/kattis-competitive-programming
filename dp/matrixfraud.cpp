#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>

using namespace std;

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

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    if (n < m) {
        vector<string> new_grid(m);
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                new_grid[j] += grid[i][j];
            }
        }
        grid = std::move(new_grid);
        swap(n, m);
    }
    vector<vector<int>> p1(n, vector<int>(m)), p0(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        p0[i][0] = grid[i][0] == '0';
        p1[i][0] = grid[i][0] == '1';
        for (int j = 1; j < m; j++) {
            p0[i][j] = p0[i][j - 1];
            p1[i][j] = p1[i][j - 1];
            if (grid[i][j] == '0') {
                p0[i][j]++;
            } else {
                p1[i][j]++;
            }
        }
    }
    auto f0 = [&](int i, int l, int r) {
        if (l > r)
            return 0;
        return p0[i][r] - (l - 1 >= 0 ? p0[i][l - 1] : 0);
    };
    auto f1 = [&](int i, int l, int r) {
        if (l > r)
            return 0;
        return p1[i][r] - (l - 1 >= 0 ? p1[i][l - 1] : 0);
    };
    vector<vector<int>> cdp(m, vector<int>(m, iinf)),
        gdp(m, vector<int>(m, iinf)), ndp(m, vector<int>(m, iinf));
    for (int i = 0; i < m; i++) {
        cdp[i][m - 1] = f0(n - 1, i, m - 1) + f1(n - 1, 0, i - 1);
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int l = m - 1; l >= 0; l--) {
            for (int r = m - 1; r >= l; r--) {
                if (r + 1 < m)
                    cdp[l][r] = min(cdp[l][r], cdp[l][r + 1]);
                gdp[l][r] = cdp[l][r];
            }
        }
        for (int l = m - 2; l >= 0; l--) {
            for (int r = 0; r < m; r++) {
                gdp[l][r] = min(gdp[l][r], gdp[l + 1][r]);
            }
        }
        for (int l = 0; l < m; l++) {
            for (int r = l; r < m; r++) {
                int curr_min = gdp[l][r];
                if (r + 1 < m) {
                    curr_min = min(curr_min, cdp[r + 1][r + 1]);
                }
                if (curr_min < iinf) {
                    ndp[l][r] = curr_min + f0(i, l, r) + f1(i, 0, l - 1) +
                                f1(i, r + 1, m - 1);
                } else {
                    ndp[l][r] = iinf;
                }
            }
        }
        ndp.swap(cdp);
    }
    int ret = iinf;
    for (int i = 0; i < m; i++) {
        ret = min(ret, cdp[0][i]);
    }
    cout << ret << '\n';
}
