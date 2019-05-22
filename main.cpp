#include <iostream>
#include <vector>
#include <set>
#include <assert.h>

// For the extended euclidean algorithm
#include <boost/integer/extended_euclidean.hpp>
// For matrices
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


#include "matrix.hpp"

// template <typename Z>
// using matrix = boost::numeric::ublas::matrix<Z>;
namespace mp = boost::multiprecision;

// 6th root of unity
const mp::mpc_complex omega{0.5, std::sqrt(3)/2};
const std::size_t iterMax = 1000;

template <typename Z>
auto fundTransform(matrix<Z>& mat)
{

  const auto oldDet = det(mat);           // used as an invarient
  // Do an inversion operation on the matrix; Inversion in the hyperbolic sense
  // Performs a -1/z
  auto inversion = [&mat]()
                {
                  matrix<Z> tmp{mat};
                  mat(0, 0) = -tmp(1, 0); // a = -c
                  mat(0, 1) = -tmp(1, 1); // b = -d
                  mat(1, 0) = tmp(0, 0);  // c = a
                  mat(1, 1) = tmp(0, 1);  // d = b
                };

  // Do a z \-> z + k
  // Do translation by k
  auto translate = [&mat](Z k)
                   {
                     mat(1, 0) += mat(0, 0) * k;
                     mat(1, 1) += mat(0, 1) * k;
                   };

  // Converts matrix into a complex number (c + d*omega)/(a + b*omega)
  auto toComplex = [&mat]()
                   {
                     mp::mpc_complex num = (mat(1, 0) + omega*mat(1, 1))/(mat(0, 0) + omega*mat(0, 1));
                     return num; // std::move(num)?
                   };

  std::size_t iter = 0;
  while(iter < iterMax)
    {
      auto z = toComplex();
      if(mp::abs(z) < 1)
        {
          inversion();

          assert(det(mat) == oldDet);
        }
      else if(z.real() < -0.5)
        {
          Z k = mp::floor(z.real() + 0.5); // TODO: check the calculation
          translate(-k);

          assert(det(mat) == oldDet);
          // do a translation
        }
      else if(z.real() > 0.5)
        {
          Z k = mp::floor(z.real() - 0.5);
          translate(-k);

          assert(det(mat) == oldDet);
        }
      else                      // the number is in the fundamental region
        {
          break;
        }

      ++iter;
    }


      // I don't need to return anything, whatever matrix was called, got transformed
}

template <typename Z>
auto genPoints(Z M, Z range)
{
  // a set because it handles the duplicates
  std::vector<matrix<Z>> vec;
  std::set<matrix<Z>> results;

  for(Z a1 = 1; a1 < M + range; ++a1)
    {
      for(Z b1 = 1; b1 < M + range; ++b1)
        {
          auto res = boost::integer::extended_euclidean(a1, b1);


          auto d = res.x;
          auto c = res.y;

          auto gcd = res.gcd;

          auto a = a1*M/gcd;      // TODO Cautious about integer overflow?
          auto b = b1*M/gcd;

          matrix<Z> mat;
          mat(0, 0) = a;
          mat(0, 1) = -b;
          mat(1, 0) = c;
          mat(1, 1) = d;

          assert(det(mat) == M);
          vec.push_back(mat);
        }
    }

  for(auto& v: vec)
    {
      fundTransform(v);
    }

  for(const auto& v: vec)
    {
      results.insert(v);
    }

  return results;
}



auto main() -> int
{
  auto ans = genPoints(4, 0);

  for(auto& v: ans)
    {
      std::cout<<v;
    }
  return 0;
}

// [a b]
// [c d]
// ad - bc = M
