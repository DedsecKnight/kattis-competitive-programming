#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

#define len(a) int((a).size())
using ll = long long;
using ld = long double;
constexpr const int iinf = 1e9 + 7;

#define printDecimal(d) \
    std::cout << std::setprecision(d) << std::fixed

using C = std::complex<double>;

void fft(std::vector<C>& a) {
    int n = len(a), L = 31 - __builtin_clz(n);
    static std::vector<std::complex<ld>> R(2, 1);
    static std::vector<C> rt(2, 1);
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = std::polar(1.0L, std::acos(-1.0L) / k);
        for (int i = k; i<2*k; i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    std::vector<int> rev(n);
    for (int i = 0; i<n; i++) rev[i] = (rev[i/2] | (i&1) << L) / 2;
    for (int i = 0; i<n; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int k = 1; k<n; k*=2) {
        for (int i = 0; i<n; i+=2*k) {
            for (int j = 0; j<k; j++) {
                auto x = (double*)&rt[j+k], y = (double*)&a[i+j+k];
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                a[i+j+k] = a[i+j] - z;
                a[i+j] += z;
            }
        }
    }
}

std::vector<double> conv(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.empty() || b.empty()) return {};
    std::vector<double> res(len(a) + len(b) - 1);
    int L = 32 - __builtin_clz(len(res)), n = 1 << L;
    std::vector<C> in(n), out(n);
    std::copy(a.begin(), a.end(), in.begin());
    for (int i = 0; i<len(b); i++) in[i].imag(b[i]);
    fft(in);
    for (auto& x : in) x *= x;
    for (int i = 0; i<n; i++) out[i] = in[-i & (n-1)] - std::conj(in[i]);
    fft(out);
    for (int i = 0; i<len(res); i++) res[i] = std::imag(out[i]) / (4 * n);
    return res;
}

int main() {
    int k,n; 
    std::cin >> k >> n;
    int sz = (1 << k);
    std::vector<std::pair<double, int>> ppl(n-1);
    for (int i = 0; i<n-1; i++) {
        std::cin >> ppl[i].first >> ppl[i].second;
    }
    std::vector<double> curr(sz*2);
    curr[0] = 1;
    for (const auto& [prob, delta] : ppl) {
        std::vector<double> nxt(sz);
        for (int i = 0; i<sz; i++) {
            auto v = (i + delta) % sz;
            nxt[v] += curr[i] * prob;
        }
        for (int i = 0; i<sz; i++) {
            curr[i] = curr[i] * (1 - prob) + nxt[i];
        } 
    }
    std::vector<double> f(2 * sz);
    for (int i= 0; i<len(f); i++) {
        f[i] = double(__builtin_popcount(i % sz));
    }
    std::reverse(curr.begin(), curr.end());
    for (int i = 0; i<sz; i++) curr.push_back(0.0);
    auto c = conv(f, curr);
    int ret = -1;
    double mx = -1.0;
    for (int i = 2*sz - 1; i < 3*sz - 1; i++) {
        if (c[i] > mx) {
            mx = c[i];
            ret = i - 2*sz + 1;
        }
    }
    std::cout << ret << '\n';
}
