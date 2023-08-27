#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

#define len(a) int((a).size())
using ll = long long;
constexpr const int iinf = 1e9 + 7;

#define printDecimal(d) \
    cout << setprecision(d) << fixed

static constexpr const std::array<int, 9> horizontal = {0, 2, 4, 5, 7, 9, 10, 12, 14};
static constexpr const std::array<int, 8> vertical = {1, 3, -1, 6, 8, -1, 11, 13};

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    std::vector<std::vector<std::pair<int, char>>> graph(81);
    std::vector<int> lb(81, 1), rb(81, 9);
    const auto add_edge = [&graph](int u, int v, char constraint) {
        graph[u].emplace_back(v, constraint);
    };
    for (int line_index = 0; line_index<15; line_index++) {
        std::string line; std::cin >> line;
        int index = std::find(horizontal.begin(), horizontal.end(), line_index) - horizontal.begin();
        if (index != 9) {
            for (int i = 0, c = 0; i<len(line); i+=2, c++) {
                add_edge(index*9+3*c, index*9+3*c+1, line[i]);
                add_edge(index*9+3*c+1, index*9+3*c+2, line[i+1]);
            }
        } else {
            index = std::find(vertical.begin(), vertical.end(), line_index) - vertical.begin();
            for (int i = 0; i<len(line); i++) {
                add_edge(index*9+i, (index+1)*9+i, line[i]);
            }
        }
    }
    bool found = false;
    std::vector<std::vector<int>> state(9, std::vector<int>(9)), ret;
    std::vector<std::bitset<10>> rows(9), cols(9);
    std::vector<std::vector<std::bitset<10>>> subsquare(3, std::vector<std::bitset<10>>(3));
    const auto possible = [&subsquare, &rows, &cols](int i, int j, int v) {
        return !subsquare[i/3][j/3].test(v) && !rows[i].test(v) && !cols[j].test(v);
    };
    const auto set = [&subsquare, &rows, &cols, &state](int i, int j, int v) {
        subsquare[i/3][j/3].set(v, true);
        rows[i].set(v, true);
        cols[j].set(v, true);
        state[i][j] = v;
    };
    const auto unset = [&subsquare, &rows, &cols, &state](int i, int j, int v) {
        subsquare[i/3][j/3].set(v, false);
        rows[i].set(v, false);
        cols[j].set(v, false);
        state[i][j] = 0;
    };
    std::function<void(int)> solve = [&](int curr) {
        if (found) return;
        if (curr >= 81) {
            ret = state;
            found = true;
            return;
        }
        for (int v = lb[curr]; v <= rb[curr]; v++) {
            if (!possible(curr / 9, curr % 9, v)) continue;
            set(curr/9, curr%9, v);
            std::vector<std::pair<int, int>> prev_state;
            for (const auto& [neighbor, constraint] : graph[curr]) {
                prev_state.emplace_back(lb[neighbor], rb[neighbor]);
                if (constraint == '<') {
                    rb[neighbor] = std::min(rb[neighbor], 9 - v);
                } else if (constraint == '>') {
                    lb[neighbor] = std::max(lb[neighbor], 11 - v);
                } else {
                    rb[neighbor] = std::min(rb[neighbor], 10-v);
                    lb[neighbor] = std::max(lb[neighbor], 10-v);
                }
            }
            solve(curr+1);
            if (found) return;
            unset(curr/9, curr%9, v);
            for (std::size_t i = 0; i<graph[curr].size(); i++) {
                lb[graph[curr][i].first] = prev_state[i].first;
                rb[graph[curr][i].first] = prev_state[i].second; 
            }
        }
    };
    solve(0);
    for (const auto& row : ret) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << '\n';
    }
}
