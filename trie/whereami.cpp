#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#ifdef LLOCAL
#include "debug.h"
#else
#define var(...)
#define debugArr(...)
#endif

using namespace std;

#define len(a) static_cast<int>((a).size())
#define present(c, x) (c.find(x) != c.end())
#define printDecimal(d) std::cout << std::setprecision(d) << std::fixed

using ll = long long;
using ull = unsigned long long;
using ld = long double;
constexpr const int iinf = 1e9 + 7;
constexpr const ll inf = 1e18;
constexpr const ll mod = 1'000'000'007;

struct TrieNode {
    int num_s{0}, weight{0};
    array<int, 2> children{-1, -1};
    pair<int, int> last_start;
};

static constexpr const int dx[] = {-1, 0, 1, 0};
static constexpr const int dy[] = {0, 1, 0, -1};

int n, m;
int grid[100][100];
int idx[100][100];
vector<pair<int, int>> moves[10000];
array<vector<pair<int, int>>, 2> part;
int num_cross;
int pr[100][100], pc[100][100];

void traverse_grid(int x, int y) {
    int nptr = 0;
    int top = x, bottom = x, left = y, right = y;
    int pos = x * m + y;
    auto& compressed = moves[pos];
    compressed.emplace_back(grid[x][y], 1);
    for (int num_steps = grid[x][y]; num_steps < num_cross;) {
        switch (nptr) {
            case 0: {
                top--;
                int cost = 0;
                if (left >= 0 && left < m) {
                    if (bottom - 1 < 0) {
                        cost = 0;
                    } else if (0 > top && 0 <= bottom - 1) {
                        cost = pc[left][min(bottom - 1, n - 1)];
                    } else {
                        cost = pc[left][min(n - 1, bottom - 1)] -
                               (top - 1 >= 0 ? pc[left][top - 1] : 0);
                    }
                }
                assert(!compressed.empty());
                if ((compressed.back().first == 0 && cost == 0) ||
                    (compressed.back().first == 1 && cost == bottom - top)) {
                    compressed.back().second += bottom - top;
                    num_steps += (compressed.back().first) * (bottom - top);
                } else {
                    for (int i = bottom - 1; i >= top && num_steps < num_cross;
                         i--) {
                        if (i >= 0 && i < n && left >= 0 && left < m) {
                            if (compressed.empty() ||
                                compressed.back().first != grid[i][left]) {
                                compressed.emplace_back(grid[i][left], 1);
                            } else {
                                compressed.back().second++;
                            }
                            num_steps += grid[i][left] == 1;
                        } else {
                            if (compressed.empty() ||
                                compressed.back().first != 0) {
                                compressed.emplace_back(0, 1);
                            } else {
                                compressed.back().second++;
                            }
                        }
                    }
                }
                break;
            }
            case 1: {
                right++;
                int cost = 0;
                if (top >= 0 && top < n) {
                    if (right < 0) {
                        cost = 0;
                    } else if (0 > left + 1 && 0 <= right) {
                        cost = pr[top][min(right, m - 1)];
                    } else {
                        cost = pr[top][min(right, m - 1)] -
                               (left >= 0 ? pr[top][left] : 0);
                    }
                }
                assert(!compressed.empty());
                if ((compressed.back().first == 0 && cost == 0) ||
                    (compressed.back().first == 1 && cost == right - left)) {
                    compressed.back().second += right - left;
                    num_steps += compressed.back().first * (right - left);
                } else {
                    for (int i = left + 1; i <= right && num_steps < num_cross;
                         i++) {
                        if (i >= 0 && i < m && top >= 0 && top < n) {
                            if (compressed.empty() ||
                                compressed.back().first != grid[top][i]) {
                                compressed.emplace_back(grid[top][i], 1);
                            } else {
                                compressed.back().second++;
                            }
                            num_steps += grid[top][i] == 1;
                        } else {
                            if (compressed.empty() ||
                                compressed.back().first != 0) {
                                compressed.emplace_back(0, 1);
                            } else {
                                compressed.back().second++;
                            }
                        }
                    }
                }
                break;
            }
            case 2: {
                bottom++;
                int cost = 0;
                if (right >= 0 && right < m) {
                    if (bottom < 0) {
                        cost = 0;
                    } else if (0 > top + 1 && 0 <= bottom) {
                        cost = pc[right][min(bottom, n - 1)];
                    } else {
                        cost = pc[right][min(bottom, n - 1)] -
                               (top >= 0 ? pc[right][top] : 0);
                    }
                }
                assert(!compressed.empty());
                if ((compressed.back().first == 0 && cost == 0) ||
                    (compressed.back().first == 1 && cost == bottom - top)) {
                    compressed.back().second += bottom - top;
                    num_steps += (compressed.back().first) * (bottom - top);
                } else {
                    for (int i = top + 1; i <= bottom && num_steps < num_cross;
                         i++) {
                        if (i >= 0 && i < n && right >= 0 && right < m) {
                            if (compressed.empty() ||
                                compressed.back().first != grid[i][right]) {
                                compressed.emplace_back(grid[i][right], 1);
                            } else {
                                compressed.back().second++;
                            }
                            num_steps += grid[i][right] == 1;
                        } else {
                            if (compressed.empty() ||
                                compressed.back().first != 0) {
                                compressed.emplace_back(0, 1);
                            } else {
                                compressed.back().second++;
                            }
                        }
                    }
                }
                break;
            }
            case 3: {
                left--;
                // [left, right-1]
                int cost = 0;
                if (bottom >= 0 && bottom < n) {
                    if (right - 1 < 0) {
                        cost = 0;
                    } else if (0 > left && 0 <= right - 1) {
                        cost = pr[bottom][min(right - 1, m - 1)];
                    } else {
                        cost = pr[bottom][min(right - 1, m - 1)] -
                               (left - 1 >= 0 ? pr[bottom][left - 1] : 0);
                    }
                }
                assert(!compressed.empty());
                if ((compressed.back().first == 0 && cost == 0) ||
                    (compressed.back().first == 1 && cost == right - left)) {
                    compressed.back().second += right - left;
                    num_steps += (compressed.back().first) * (right - left);
                } else {
                    for (int i = right - 1; i >= left && num_steps < num_cross;
                         i--) {
                        if (i >= 0 && i < m && bottom >= 0 && bottom < n) {
                            if (compressed.empty() ||
                                compressed.back().first != grid[bottom][i]) {
                                compressed.emplace_back(grid[bottom][i], 1);
                            } else {
                                compressed.back().second++;
                            }
                            num_steps += grid[bottom][i] == 1;
                        } else {
                            if (compressed.empty() ||
                                compressed.back().first != 0) {
                                compressed.emplace_back(0, 1);
                            } else {
                                compressed.back().second++;
                            }
                        }
                    }
                }
                break;
            }
            default: {
                assert(false);
            }
        }
        nptr = (nptr + 1) % 4;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> m >> n;
    num_cross = 0;
    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;
        for (int j = 0; j < m; j++) {
            if (line[j] == 'X') {
                grid[i][j] = 1, num_cross++;
                pr[i][j] = 1;
                pc[j][i] = 1;
            }
            if (j - 1 >= 0)
                pr[i][j] += pr[i][j - 1];
            if (i - 1 >= 0)
                pc[j][i] += pc[j][i - 1];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            traverse_grid(i, j);
            part[moves[i * m + j][0].first].emplace_back(i, j);
        }
    }
    vector<TrieNode> nodes(1);
    queue<pair<int, array<vector<pair<int, int>>, 2>>> q;
    q.emplace(0, part);
    array<vector<pair<int, int>>, 2> next;
    while (!q.empty()) {
        auto& [ptr, curr] = q.front();
        for (int v = 0; v < 2; v++) {
            if (!curr[v].empty()) {
                next[0].clear();
                next[1].clear();
                nodes.emplace_back();
                nodes[ptr].children[v] = len(nodes) - 1;
                int min_dist = iinf;
                for (const auto& [i, j] : curr[v]) {
                    min_dist =
                        min(min_dist, moves[i * m + j][idx[i][j]].second);
                }
                nodes[nodes[ptr].children[v]].weight = min_dist;
                nodes[nodes[ptr].children[v]].num_s = len(curr[v]);
                for (const auto& [i, j] : curr[v]) {
                    moves[i * m + j][idx[i][j]].second -= min_dist;
                    nodes[nodes[ptr].children[v]].last_start = make_pair(i, j);
                    if (moves[i * m + j][idx[i][j]].second == 0) {
                        if (++idx[i][j] < len(moves[i * m + j]))
                            next[v ^ 1].emplace_back(i, j);
                    } else {
                        next[v].emplace_back(i, j);
                    }
                }
                q.emplace(nodes[ptr].children[v], next);
            }
        }
        q.pop();
    }

    int max_depth = 0;
    queue<pair<int, int>> qq;
    qq.emplace(0, 0);
    vector<pair<int, int>> furthest;
    unordered_map<int, int> cnt;
    while (!qq.empty()) {
        auto [curr, depth] = qq.front();
        qq.pop();
        if (nodes[curr].num_s == 1) {
            cnt[depth]++;
            if (max_depth < depth) {
                max_depth = depth;
                furthest = {make_pair(nodes[curr].last_start.second + 1,
                                      n - nodes[curr].last_start.first)};
            } else if (max_depth == depth) {
                furthest.emplace_back(nodes[curr].last_start.second + 1,
                                      n - nodes[curr].last_start.first);
            }
            continue;
        }
        for (int v = 0; v < 2; v++) {
            if (nodes[curr].children[v] != -1) {
                qq.emplace(nodes[curr].children[v], depth + nodes[curr].weight);
            }
        }
    }

    double e = 0.0;
    for (const auto& [k, v] : cnt) {
        e += double(k * v) / double(n * m);
    }
    printDecimal(3) << e << '\n' << max_depth << '\n';
    sort(furthest.begin(), furthest.end(), [](auto x, auto y) {
        if (x.second != y.second)
            return x.second < y.second;
        return x.first < y.first;
    });
    for (const auto& [x, y] : furthest) {
        cout << "(" << x << "," << y << ") ";
    }
}
