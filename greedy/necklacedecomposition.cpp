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

vector<int> Z(const string& S) {
    vector<int> z(len(S));
    int l = -1, r = -1;
    for (int i = 1; i < len(S); i++) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while (i + z[i] < len(S) && S[i + z[i]] == S[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = len(s);
        vector<vector<bool>> is_necklace(n, vector<bool>(n, true));
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                string curr = "";
                for (int k = i; k <= j; k++) {
                    curr += s[k];
                }
                curr += curr;
                auto z = Z(curr);
                for (int k = 1; k < j - i + 1; k++) {
                    if (z[k] < j - i + 1 && curr[z[k]] > curr[k + z[k]]) {
                        is_necklace[i][j] = false;
                    }
                }
            }
        }
        string ret = "";
        for (int i = 0; i < n;) {
            int target = -1;
            for (int j = n - 1; j >= i; j--) {
                if (is_necklace[i][j]) {
                    target = j;
                    break;
                }
            }
            ret += "(" + s.substr(i, target - i + 1) + ")";
            i = target + 1;
        }
        cout << ret << '\n';
    }
}
