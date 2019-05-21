#include <iostream>
#include <vector>

// For the extended euclidean algorithm
#include <boost/integer/extended_euclidean.hpp>
// For matrices
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>



// [a b]
// [c d]
// ad - bc = M
template <typename Z>
auto genPoints(Z M, Z range = 20)
{
  std::vector<boost::numeric::ublas::matrix<Z>> results;

  for(Z a1 = 1; a1 < M + range; ++a1)
    {
      for(Z b1 = 1; b1 < M + range; ++b1)
        {
          auto res = boost::integer::extended_euclidean(a1, b1);

  auto c = res.x;
  auto d = res.y;

          auto gcd = res.gcd;

          auto a = a1*M/gcd;      // TODO Cautious about integer overflow?
          auto b = b1*M/gcd;

          boost::numeric::ublas::matrix<Z> mat(2, 2);
          mat(0, 0) = a;
          mat(0, 1) = -b;
          mat(1, 0) = c;
          mat(1, 1) = d;

          results.push_back(mat);
        }
    }

  // Now, a and b should become a*M/GCD(a, b) and b*M/GCD(a, b)

  // Create the matrix. I just need to have it.
  // I can transform the matrix if I need to do it.

  // Printing whatever we got
  for(auto& v: results)
    {
      std::cout<<v<<"\n";
    }
}

auto main() -> int
{
  genPoints(4, 20);
  return 0;
}
