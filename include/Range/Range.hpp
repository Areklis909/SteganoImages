#ifndef RANGE_HPP
#define RANGE_HPP

#include <algorithm>
#include <exception>
#include <functional>
#include <utility>
#include <vector>

namespace NsRange {

template <typename ColT, typename ColU> auto zip(ColT &col1, ColU &col2) {
  if (col1.size() != col2.size())
    throw std::runtime_error("zip(): Incorrect size!");
  std::vector<
      std::pair<typename ColT::value_type &, typename ColU::value_type &>>
      ret;
  ret.reserve(col1.size());
  std::transform(std::begin(col1), std::end(col1), std::begin(col2),
                 std::back_inserter(ret),
                 [](auto &it1, auto &it2) ->
                 typename decltype(ret)::value_type {
                   return {std::ref(it1), std::ref(it2)};
                 });
  return ret;
}

class Range {

public:
  const std::pair<int, int> range;
  Range(const int start, const int end) : range(std::make_pair(start, end)){};

  int start() const { return range.first; }

  int end() const { return range.second; }

  Range operator+(const int value) {
    return Range(range.first + value, range.second + value);
  }

  Range operator*(const int mul) {
    return Range(range.first * mul, range.second * mul);
  }
};

} // namespace NsRange

#endif