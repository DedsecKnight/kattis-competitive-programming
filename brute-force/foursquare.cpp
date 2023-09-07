#include <bits/stdc++.h>

int main() {
    std::vector<std::pair<int, int>> squares(4);
    int total_area = 0;
    for (auto& [w, h] : squares) {
        std::cin >> w >> h;
        total_area += w * h;
    }
    const auto special_case = [&](int s) {
        std::vector<int> order(4);
        std::iota(order.begin(), order.end(), 0);
        do {
            for (int mask = 0; mask < (1 << 4); mask++) {
                std::vector<std::pair<int, int>> state;
                for (int i = 0; i<4; i++) {
                    if (mask & i) state.emplace_back(squares[order[i]].second, squares[order[i]].first);
                    else state.push_back(squares[order[i]]);
                } 
                if (state[0].first + state[1].first == s 
                && state[2].first + state[3].first == s
                && state[0].second + state[2].second == s
                && state[1].second + state[3].second == s) return true;

            }
        } while (std::next_permutation(order.begin(), order.end()));
        return false;
    };
    std::function<bool(int, int, int)> possible = [&](int w, int h, int mask) {
        if (h < 0 || w < 0) return false;
        if (mask == (1 << 4) - 1) return true;
        for (int i = 0;i<4; i++) {
            if (mask & (1 << i)) continue;
            if (squares[i].first == w && possible(w, h-squares[i].second, mask | (1 << i))) return true; 
            if (squares[i].second == h && possible(w-squares[i].first, h, mask | (1 << i))) return true;
            if (squares[i].first == h && possible(w-squares[i].second, h, mask | (1 << i))) return true;
            if (squares[i].second == w && possible(w, h-squares[i].first, mask | (1 << i))) return true;
        }
        if (mask == 0) return special_case(w);
        return false;
    };
    int x = int(sqrt(total_area));
    std::cout << (x * x == total_area && possible(x,x,0)) << '\n';
}