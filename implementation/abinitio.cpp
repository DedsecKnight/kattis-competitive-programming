/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/abinitio
TAGS: implementation, observation
EXPLANATION: 
- Let a state of the graph G be represented by the following 4 2d arrays:
    + in: A 2d boolean array in which in[i][j] denotes whether i has an incoming edge from j in G
    + in_c: A 2d boolean array in which in_c[i][j] denotes whether i has an incoming edge from j in complement of G
    + out: A 2d boolean array in which out[i][j] denotes whether i has an outgoing edge to j in G
    + out_c: A 2d boolean array in which out_c[i][j] denotes whether i has an outgoing edge to j in complement of G
=> It can be noticed that the changes applied on the 4 above arrays are rather trivial for the first 4 operations.
- For operation #5 (transpose), one can notice that it is equivalent to changing direction of all edges in G, which can be done
by swapping the contents of in[i] and out[i] with each other and those of in_c[i] and out_c[i] with each other for every vertex i. 
- For operation #6 (complement), this can be accomplished by swapping the contents of in[i] and in_c[i] with each other and those of out[i] and out_c[i] with each other.
- To efficiently "swap" the content of 2 arrays (or vectors in my implementation), one can utilize the vector::swap function, which swap contents of 2
arrays in constant time (reference: https://en.cppreference.com/w/cpp/container/vector/swap)
- Time complexity: 
    + Add/remove edge: O(1)
    + Transpose/Complement/Add Node/Isolate Node: O(n)
    + Overall: O(N * Q)
END ANNOTATION
*/
#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

#define len(a) int((a).size())
using ll = long long;
constexpr const ll mod = 1e9 + 7;

#define printDecimal(d) \
    cout << setprecision(d) << fixed

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    int n,m,q; 
    cin >> n >> m >> q;
    
    vector<vector<bool>> in(n, vector<bool>(n, false));
    vector<vector<bool>> in_c(n, vector<bool>(n, true));
    vector<vector<bool>> out(n, vector<bool>(n, false));
    vector<vector<bool>> out_c(n, vector<bool>(n, true));
    
    auto add_edge = [&](int from, int to) {
        out_c[from][to] = false;
        in_c[to][from] = false;
        out[from][to] = true;
        in[to][from] = true;
    };
    auto add_node = [&]() {
        in.emplace_back(n+1, false); in_c.emplace_back(n+1, true);
        out.emplace_back(n+1, false); out_c.emplace_back(n+1, true);
        for (int i = 0; i<n; i++) {
            in_c[i].push_back(true);
            in[i].push_back(false);
            out_c[i].push_back(true);
            out[i].push_back(false);
        }
        n++;
    };
    auto remove_edge = [&](int from, int to) {
        out[from][to] = false;
        in[to][from] = false;
        out_c[from][to] = true;
        in_c[to][from] = true;
    };
    auto isolate_node = [&](int x) {
        for (int i = 0;i<n; i++) {
            if (x != i && out[x][i]) remove_edge(x, i);
            if (x != i && in[x][i]) remove_edge(i, x);
        }
    };
    auto transpose = [&]() {
        for (int i = 0;i<n; i++) {
            in_c[i].swap(out_c[i]);
            in[i].swap(out[i]);
        } 
    };
    auto complement = [&]() {
        for (int i = 0;i<n; i++) {
            in_c[i].swap(in[i]);
            out_c[i].swap(out[i]);
        }
    };
    for (int i = 0; i<m; i++) {
        int a,b; cin >> a >> b;
        add_edge(a, b);    
    }
    while (q--) {
        int op; cin >> op;
        if (op == 1) add_node();
        else if (op == 2) {
            int x,y; cin >> x >> y;
            add_edge(x, y);
        } else if (op == 3) {
            int x; cin >> x;
            isolate_node(x);
        } else if (op == 4) {
            int x,y; cin >> x >> y;
            remove_edge(x, y);
        } else if (op == 5) {
            transpose();
        } else {
            complement();
        }
    }
    cout << n << '\n';
    for (int i = 0;i<n; i++) {
        ll h = 0, p = 1, sz = 0;
        for (int j = 0;j<n; j++) {
            if (!out[i][j] || i == j) continue;
            h = (h + (p * j % mod)) % mod;
            p = (p * 7) % mod;
            sz++;
        }
        cout << sz << " " << h << '\n';
    }

}
