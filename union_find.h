#include <array>
#include <numeric>
#include <ranges>

namespace dsa {

template <std::size_t N> struct union_find {
  std::array<int, N> _p{}, _r{};

  constexpr union_find() { std::iota(std::begin(_p), std::end(_p), 0); }
  constexpr int find(int i_) noexcept {
    return _p[i_] == i_ ? i_ : _p[i_] = find(_p[i_]);
  }
  constexpr bool unite(int i_, int j_) noexcept {
    auto x{find(i_)}, y{find(j_)};

    if (x == y)
      return false;

    if (r[x] < r[y])
      std::swap(x, y);

    r[x] += static_cast<int>(r[x] == r[y]);
    p[y] = x;

    return true;
  }
};

} // namespace dsa