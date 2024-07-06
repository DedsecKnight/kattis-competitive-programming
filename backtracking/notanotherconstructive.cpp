#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr const int dim1 = 41, dim2 = 2501, dim3 = 20 * 39 + 1,
                           dim4 = 41;
static constexpr const size_t N = dim1 * 1ll * dim2 * dim3 * dim4;
bitset<N> ldp, lv;
char s[41], ans[41];
int s_size, ptr = 0;

#define compress(i, j, a, b)                                  \
    ((i)*1ull * dim2 * dim3 * dim4 + (j)*1ull * dim3 * dim4 + \
     (a)*1ull * dim4 + (b))

static constexpr const array<int, 41> cutoff{
    0,    0,    0,    1,    4,    4,    8,    12,  18,   27,   36,
    48,   64,   80,   100,  125,  150,  180,  216, 252,  294,  343,
    392,  448,  512,  576,  648,  729,  810,  900, 1000, 1100, 1210,
    1331, 1452, 1584, 1728, 1872, 2028, 2197, 2366};

static constexpr const array<int, 41> cutoff_na{
    0,   0,   1,   2,   4,   6,   9,   12,  16,  20,  25,  30,  36,  42,
    49,  56,  64,  72,  81,  90,  100, 110, 121, 132, 144, 156, 169, 182,
    196, 210, 225, 240, 256, 272, 289, 306, 324, 342, 361, 380, 400};

bool solve_left(int rem, int nac, int na, int n) {
    if (n < 0 || na < 0 || nac < 0)
        return 0;
    size_t k = compress(rem, nac, na, n);
    if (lv.test(k))
        return ldp.test(k);
    lv.set(k, true);
    if (rem == 0 || nac > cutoff[rem] || na > cutoff_na[rem] || n > rem) {
        return false;
    }
    switch (s[rem - 1]) {
        case 'N': {
            ldp.set(k, solve_left(rem - 1, nac, na, n - 1));
            break;
        }
        case 'A': {
            ldp.set(k, solve_left(rem - 1, nac, na - n, n));
            break;
        }
        case 'C': {
            ldp.set(k, solve_left(rem - 1, nac - na, na, n));
            break;
        }
        case '?': {
            if (solve_left(rem - 1, nac - na, na, n)) {
                ldp.set(k, true);
                printf("C");
                return true;
            }
            if (solve_left(rem - 1, nac, na - n, n)) {
                ldp.set(k, true);
                printf("A");
                return true;
            }
            if (solve_left(rem - 1, nac, na, n - 1)) {
                ldp.set(k, true);
                printf("N");
                return true;
            }
            if (solve_left(rem - 1, nac, na, n)) {
                ldp.set(k, true);
                printf("Z");
                return true;
            }
            return false;
            break;
        }
        default: {
            ldp.set(k, solve_left(rem - 1, nac, na, n));
            break;
        }
    }
    if (ldp.test(k)) {
        printf("%c", s[rem - 1]);
        return true;
    }
    return false;
}

int main() {
    int k;
    scanf("%d%d", &s_size, &k);
    scanf("%s", s);
    ldp.set(0);
    lv.set(0);

    for (int x = cutoff_na[s_size]; x >= 0; x--) {
        for (int y = s_size; y >= 0; y--) {
            if (solve_left(s_size, k, x, y)) {
                return 0;
            }
        }
    }
    printf("-1");
}
