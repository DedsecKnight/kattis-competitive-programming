#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;

constexpr ll mod = 1000000007;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n), rev_graph(n);
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        graph[i].push_back(--v);
        rev_graph[v].push_back(i);
    }

    vector<bool> visited(n, false);
    vector<int> order, component;

    function<void(int)> dfs1 = [&](int curr) {
        visited[curr] = true;
        for (const auto &neighbor : graph[curr]) {
            if (!visited[neighbor]) dfs1(neighbor);
        }
        order.push_back(curr);
    };

    function<void(int)> dfs2 = [&](int curr) {
        visited[curr] = true;
        component.push_back(curr);
        for (const auto &neighbor : rev_graph[curr]) {
            if (!visited[neighbor]) dfs2(neighbor);
        }
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs1(i);
    }

    fill(visited.begin(), visited.end(), false);
    reverse(order.begin(), order.end());

    vector<vector<int>> rev_scc(n);
    vector<int> roots(n, 0), root_nodes;

    for (const auto &v : order) {
        if (!visited[v]) {
            dfs2(v);
            int root = component.front();
            for (const auto &u : component) {
                roots[u] = root;
            }
            root_nodes.push_back(root);
            component.clear();
        }
    }

    vector<int> indegree(n);

    for (int v = 0; v < n; v++) {
        for (auto u : graph[v]) {
            int root_v = roots[v], root_u = roots[u];
            if (root_u != root_v) {
                rev_scc[root_u].push_back(root_v);
                indegree[root_v]++;
            }
        }
    }

    for (int v = 0; v < n; v++) {
        sort(rev_scc[v].begin(), rev_scc[v].end());
        rev_scc[v].erase(unique(rev_scc[v].begin(), rev_scc[v].end()), rev_scc[v].end());
    }

    queue<int> q;
    vector<int> top_order;

    for (auto i : root_nodes) {
        if (!indegree[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        top_order.push_back(curr);
        for (const auto &neighbor : rev_scc[curr]) {
            if (--indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<ll> dp(n);

    function<void(int)> dfs3 = [&](int curr) {
        visited[curr] = true;
        dp[curr] = 1;
        for (const auto &neighbor : rev_scc[curr]) {
            if (!visited[neighbor]) {
                dfs3(neighbor);
                dp[curr] = (dp[curr] * dp[neighbor] % mod) % mod;
            }
        }
        dp[curr] = (dp[curr] + 1) % mod;
    };

    ll ret = 1;

    for (const auto &v : top_order) {
        if (!visited[v]) {
            dfs3(v);
            ret = (ret * dp[v]) % mod;
        }
    }

    cout << (ret - 1 + mod) % mod << '\n';
}