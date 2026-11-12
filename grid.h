#include <vector>
#include <optional>
#include <iostream>

template<typename T>
struct Grid {
  private:
  std::vector<T> content;
  
  public:
  const std::size_t width;
  const std::size_t height;

  Grid (std::size_t width, std::size_t height, T const& init = T{}):
    width{width}, height{height}, content{std::vector(width * height, init)} {} 

  T& operator()(std::size_t i, std::size_t j) { return content[i * width + j]; }

  T const& operator()(std::size_t i, std::size_t j) const { return content[i * width + j]; }

  bool in_grid(std::size_t i, std::size_t j) const { return i < height && j < width; }

  T* north_west(std::size_t i, std::size_t j) {
    if (i == 0 || j == 0 || !in_grid(i-1, j-1)) return nullptr;
    return &this->operator()(i-1, j-1);
  }

  T* north(std::size_t i, std::size_t j) {
    if (i == 0 || !in_grid(i-1, j)) return nullptr;
    return &this->operator()(i-1, j);
  }

  T* north_east(std::size_t i, std::size_t j) {
    if (i == 0 || !in_grid(i-1, j+1)) return nullptr;
    return &this->operator()(i-1, j+1);
  }

  T* west(std::size_t i, std::size_t j) {
    if (j == 0 || !in_grid(i, j-1)) return nullptr;
    return &this->operator()(i, j-1);
  }
  
  T* east(std::size_t i, std::size_t j) {
    if (!in_grid(i, j+1)) return nullptr;
    return &this->operator()(i, j+1);
  }
  
  T* south_west(std::size_t i, std::size_t j) {
    if (j == 0 || !in_grid(i+1, j-1)) return nullptr;
    return &this->operator()(i+1, j-1);
  }

  T* south(std::size_t i, std::size_t j) {
    if (!in_grid(i+1, j)) return nullptr;
    return &this->operator()(i+1, j);
  }

  T* south_east(std::size_t i, std::size_t j) {
    if (!in_grid(i+1, j+1)) return nullptr;
    return &this->operator()(i+1, j+1);
  }

  template <typename Pred>
  bool exists(Pred pred) const {
    return std::any_of(content.begin(), content.end(), pred);
  }

  template <typename Pred>
  T const* find_if(Pred pred) const {
    auto it = std::find_if(content.begin(), content.end(), pred);
    if (it == content.end()) return nullptr;
    return &*it;
  }

  template <typename F>
  void print_grid(F print_T, std::ostream& out = std::cout) const {
    for (std::size_t i = 0; i < height; i++) {
      for (std::size_t j = 0; j < width; j++) {
        print_T(this->operator()(i, j), out);
      }
      out << '\n';
    }
  }
};

