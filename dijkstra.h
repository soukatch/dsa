#include <array>
#include <queue>
#include <ranges>
#include <vector>

namespace dsa {

struct dijkstra_fn {
  template <std::size_t N>
  using adjacency_list = std::array<std::vector<std::pair<int, int>>, N>;

  template <std::size_t N, bool D = false>
  auto operator()(adjacency_list<N> a, int s = 0) const {
    std::array<int, N> d{};
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        q{};
    std::ranges::fill(d, std::numeric_limits<int>::max());

    q.emplace(0, s);

    for (; not empty(q);) {
      auto [x, y]{q.top()};
      q.pop();

      if (d[y] > x)
        for (d[y] = x; auto &&z : a[y])
          if (d[z.first] == std::numeric_limits<int>::max())
            q.emplace(d[y] + z.second, z.first);
    }

    return d;
  }
};

inline constexpr dijkstra_fn dijkstra{};
} // namespace dsa