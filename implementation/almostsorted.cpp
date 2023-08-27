#include <algorithm>
#include <cstddef>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using ui = unsigned int;
using ll = long long;
using ld = long double;

template <typename K, typename V>
using umap = std::unordered_map<K, V>;

#define null NULL
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)

constexpr ll inf = 1000000000000000000;
constexpr int MAXN = 1001;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    uint32_t n; std::cin >> n;
    std::vector<int32_t> a(n);
    for (std::size_t i = 0;i<n; i++) std::cin >> a[i]; 
    int32_t target; std::cin >> target;
    std::vector<int32_t> sorted_a(a.begin(), a.end());
    std::sort(sorted_a.begin(), sorted_a.end());
    std::unordered_map<int32_t, std::size_t> index_mp{};
    std::set<std::size_t> remain;
    std::for_each(sorted_a.begin(), sorted_a.end(), [i = 0ul, &index_mp, &remain, &a](auto elem) mutable {
        index_mp.emplace(elem, i);
        if (a[i] != elem) remain.insert(i);
        i++;
    });
    std::size_t target_pos{index_mp[target]};
    while (remain.find(target_pos) != remain.end()) {
        auto it = remain.begin();
        auto move_to = index_mp[a[*it]];
        std::swap(a[*it], a[move_to]);
        remain.erase(move_to);
    }
    for (const auto& elem : a) {
        std::cout << elem << " ";
    }
    std::cout << '\n';
}   

