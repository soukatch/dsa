#pragma once

#include <array>

namespace dsa {
template <typename T, std::size_t N, typename Compare = std::less<T>>
struct constepxr_priority_queue final {
  /// NB: there is no protection against invalid operations (i.e. pushing beyond
  ///     max size or popping from an empty queue).

  constexpr void push(const T &v) {
    elems_[size_++] = v;
    std::push_heap(std::begin(elems_), std::begin(elems_) + size_, Compare{});
  }
  constexpr void push(T &&v) {
    elems_[size_++] = v;
    std::push_heap(std::begin(elems_), std::begin(elems_) + size_, Compare{});
  }
  template <typename... Args> constexpr void emplace(Args &&...args) {
    elems_[size_++] = T(std::forward<Args>(args)...);
    std::push_heap(std::begin(elems_), std::begin(elems_) + size_, Compare{});
  }
  constexpr T top() const noexcept { return elems_.front(); }
  constexpr void pop() {
    std::pop_heap(std::begin(elems_), std::begin(elems_) + size_, Compare{});
    --size_;
  }
  constexpr bool empty() const noexcept { return size_ == 0; }

private:
  std::array<T, N> elems_{};
  std::size_t size_{};
  Compare comp_{};
};
};