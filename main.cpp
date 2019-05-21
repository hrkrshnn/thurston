#include <iostream>
#include <vector>

// For the extended euclidean algorithm
#include <boost/integer/extended_euclidean.hpp>

// ad - bc = M
template <typename Z>
auto genPoint(std::pair<Z, Z> ab, Z M)
{
  auto res = boost::integer::extended_euclidean(ab.first, ab.second);
  auto c = res.x;
  auto d = res.y;

  // s
}

auto main -> int
{
  return 0;
}
