#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")

using namespace std;

#define len(a) static_cast<int>((a).size())

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
    vector<vector<int>> graph(n);
    vector<unordered_set<int>> seen(n);
    vector<int> degree(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[--u].push_back(--v);
        graph[v].push_back(u);
        seen[u].insert(v);
        seen[v].insert(u);
        degree[u]++, degree[v]++;
    }
    if (m == 0) {
        for (int i = 0; i < n; i++)
            cout << 1 << " ";
        cout << '\n';
        return 0;
    }
    vector<int> heavy_nodes;
    set<tuple<int, int, int>> triangles;
    for (int i = 0; i < n; i++) {
        if (degree[i] * 1ll * degree[i] > n) {
            heavy_nodes.push_back(i);
        } else {
            for (int x = 0; x < len(graph[i]); x++) {
                for (int y = x + 1; y < len(graph[i]); y++) {
                    if (seen[graph[i][x]].find(graph[i][y]) !=
                        seen[graph[i][x]].end()) {
                        vector<int> new_triangle{graph[i][x], graph[i][y], i};
                        sort(new_triangle.begin(), new_triangle.end());
                        triangles.emplace(new_triangle[0], new_triangle[1],
                                          new_triangle[2]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < len(heavy_nodes); i++) {
        for (int j = i + 1; j < len(heavy_nodes); j++) {
            for (int k = j + 1; k < len(heavy_nodes); k++) {
                vector<int> new_triangle{heavy_nodes[i], heavy_nodes[j],
                                         heavy_nodes[k]};
                bool valid = true;
                for (int a = 0; a < 3; a++) {
                    for (int b = 0; b < 3; b++) {
                        if (a == b)
                            continue;
                        if (seen[new_triangle[a]].find(new_triangle[b]) ==
                            seen[new_triangle[a]].end()) {
                            valid = false;
                        }
                    }
                }
                if (valid) {
                    triangles.emplace(new_triangle[0], new_triangle[1],
                                      new_triangle[2]);
                }
            }
        }
    }
    int max_color_required = triangles.empty() ? 2 : 3;
    vector<vector<pair<int, int>>> tri(n);
    for (const auto& [a, b, c] : triangles) {
        tri[a].emplace_back(b, c);
        tri[b].emplace_back(a, c);
        tri[c].emplace_back(a, b);
    }
    for (int i = 0; i < n; i++) {
        for (const auto& [x, y] : tri[i]) {
            seen[i].erase(x);
            seen[i].erase(y);
        }
        for (const auto& elem : seen[i]) {
            tri[i].emplace_back(elem, -1);
        }
    }
    vector<int> color(n, -1);
    auto dfs = y_combinator([&](auto self, int curr, int par) -> void {
        for (const auto& [x, y] : tri[curr]) {
            if (y != -1) {
                if (color[x] == -1) {
                    color[x] = (color[curr] + 1) % max_color_required;
                    color[y] = (color[curr] + 2) % max_color_required;
                    self(x, curr);
                    self(y, curr);
                }
            } else if (x != par) {
                color[x] = (color[curr] + 1) % max_color_required;
                self(x, curr);
            }
        }
    });
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            dfs(i, -1);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << color[i] + 1 << ' ';
    }
    cout << '\n';
}
