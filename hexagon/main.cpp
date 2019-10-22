// Code for generating points (n, p1, p2, p3) that satisfies the condition
// p1 >= 0, p2 >= 0 p3 >= 0
// p1 + p2 <= n; p2 + p3 <= n; p3 + p1 <= n
// m = n^2 - p1^2 - p2^2 - p3^2

#include <iostream>
#include <vector>
#include <math.h>
#include <experimental/iterator>

template <typename T>
struct Point
{
  T n, p1, p2, p3;
  Point(T a, T b, T c, T d):n(a), p1(b), p2(c), p3(d)
  {};
};

template <typename T>
auto genPoints(T m)
{
  std::vector<Point<T>> pts;

  // At what point should I put my limit
  for(T n = std::sqrt(m); n <= 2*m; ++n)
    for(T p1 = 0; p1 <= n; ++p1)
      for(T p2 = 0; p2 + p1 <= n; ++p2)
        for(T p3 = 0; p3 + p1 <= n && p2 + p3 <= n; ++p3)
          if(m == n*n - p1*p1 - p2*p2 - p3*p3)
            pts.push_back(Point<T>(n, p1, p2, p3));

  return pts.size();
}

namespace std
{
  template <typename T, typename S>
  ostream& operator<<(ostream& out, const pair<T, S>& p)
  {
    return out<<"("<<p.first<<", "<<p.second<<")";
  }
}

int main()
{
  std::vector<std::pair<int, int>> outs;

  decltype(outs.size()) maxVal = 500;

  for(decltype(maxVal) i = 1; i < maxVal; ++i)
    {
      auto tmp = genPoints(i);
      outs.push_back(std::make_pair(i, tmp));
    }

  std::copy(outs.cbegin(), outs.cend(), std::experimental::make_ostream_joiner(std::cout, ", "));

  std::cout<<"\n";

  return 0;
}
