#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

#define len(a) int((a).size())

#define printDecimal(d) \
    cout << setprecision(d) << fixed

using ll = long long;

const double eps = 1e-12;
int solveLinear(vector<vector<double>>& A, vector<double>&b, vector<double>& x) {
    int n = len(A), m = len(x), rank = 0, br, bc;
    if (n) assert(len(A[0]) == m);
    vector<int> col(m); iota(begin(col), end(col), 0);
    for (int i= 0;i<n; i++) {
        double v, bv = 0;
        for (int r = i; r<n; r++) {
            for (int c = i; c < m; c++) {
                if ((v = fabs(A[r][c])) > bv) {
                    br = r, bc = c, bv = v;
                }
            }
        }
        if (bv <= eps) {
            for (int j = i; j<n; j++) if (fabs(b[j]) > eps) return -1;
            break;
        }
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        for (int j = 0; j<n; j++) swap(A[j][i], A[j][bc]);
        bv = 1/A[i][i];
        for (int j = i+1; j<n; j++) {
            double fac = A[j][i] * bv;
            b[j] -= fac * b[i];
            for (int k = i+1; k<m; k++) A[j][k] -= fac * A[i][k];
        }
        rank++;
    }
    x.assign(m, 0);
    for (int i = rank; i--; ) {
        b[i] /= A[i][i];
        x[col[i]] = b[i];
        for (int j = 0;j<i; j++) b[j] -= A[j][i] * b[i];
    }
    return rank;
}

int main() {
    int c; cin >> c;
    int n = int(ceil(log2(c)));
    queue<tuple<int, ll, ll>> q;
    int sz = 2*n + 2, nxt = 1;
    vector<vector<tuple<int, double, int>>> graph(sz);
    q.emplace(0, 0, (1ll << n) - 1);
    c--;
    while (!q.empty()) {
        auto [node, lb, rb] = q.front();
        q.pop();
        if (rb < c) {
            graph[node].emplace_back(2*n+1, 1.0, __builtin_ctz(rb-lb+1));
        } else if (c < lb) {
            graph[node].emplace_back(0, 1.0, 0);
        } else  {
            if (lb == rb) {
                graph[node].emplace_back(2*n+1, 1.0, 0);
                continue;
            }
            int l = nxt++;
            int r = nxt++;
            graph[node].emplace_back(l, 0.5, 1);
            graph[node].emplace_back(r, 0.5, 1);
            auto mid = lb + (rb - lb) / 2;
            q.emplace(l, lb, mid);
            q.emplace(r, mid+1, rb);
        }
    }
    vector<vector<double>> transition(sz, vector<double>(sz));
    vector<double> b(sz), x(sz);
    for (int i = 0; i<sz; i++) {
        transition[i][i] = 1.0;
        for (const auto& [child, prob, step] : graph[i]) {
            transition[i][child] = -prob;
            b[i] += prob * step;
        }
    }
    solveLinear(transition, b, x);
    printDecimal(8) << x[0] << '\n';

}
