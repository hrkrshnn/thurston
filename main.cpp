#include <iostream>
#include <vector>
#include <assert.h>

// For the extended euclidean algorithm
#include <boost/integer/extended_euclidean.hpp>
// For matrices
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

// For complex numbers
#include <boost/multiprecision/mpc.hpp>
#include <boost/multiprecision/mpfr.hpp>

template <typename Z>
using matrix = boost::numeric::ublas::matrix<Z>;
namespace mp = boost::multiprecision;

// 6th root of unity
const mp::mpc_complex omega{0.5, std::sqrt(3)/2};
const std::size_t iterMax = 1000;

template <typename Z>
Z det(const matrix<Z>& mat)  // computes the determinant of a 2x2 matrix
{
  // TODO: asserts for dimension
  return (mat(0, 0) * mat(1,1) - mat(0, 1)*mat(1, 0));
}

template <typename Z>
auto matToComplex(const matrix<Z>& mat)
{
  mp::mpc_complex num = (mat(1, 0) + omega*mat(1, 1))/(mat(0, 0) + omega*mat(0, 1));
  std::cout<<"matrix: "<<mat<<" complex: "<<num<<std::endl;
}

template <typename Z>
auto fundTransform(matrix<Z>& mat)
{
  // Do an inversion operation on the matrix; Inversion in the hyperbolic sense
  auto inversion = [&mat]()
                {
                  matrix<Z> tmp = mat;
                  mat(0, 0) = -tmp(1, 0);
                  mat(0, 1) = -tmp(1, 1);
                  mat(1, 0) = tmp(0, 0);
                  mat(1, 1) = tmp(1, 0);
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
        }
      else if(z.real() < -0.5)
        {
          Z k = mp::floor(z.real() + 0.5); // TODO: check the calculation
          translate(-k);
          // do a translation
        }
      else if(z.real() > 0.5)
        {
          Z k = mp::floor(z.real() - 0.5);
          translate(-k);
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
void genPoints(Z M, Z range)
{
  std::vector<matrix<Z>> results;

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

          std::cout<<a1<<" "<<b1<<" "<<c<<" "<<d<<std::endl;

          matrix<Z> mat(2, 2);
          mat(0, 0) = a;
          mat(0, 1) = -b;
          mat(1, 0) = c;
          mat(1, 1) = d;

          assert(det(mat) == M);
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

  for(auto& v: results)
    {
      fundTransform(v);
    }

  std::cout<<"Transformed";
  for(auto& v: results)
    {
      std::cout<<v<<"\n";
      matToComplex(v);
    }

}



auto main() -> int
{
  // matrix<int> test(2, 2);
  // test(0, 0) = 2;
  // test(0, 1) = 0;
  // test(1, 0) = 0;
  // test(1, 1) = 1;

  // std::cout<<test<<"\n";
  // matToComplex(test);

  // fundTransform(test);
  // std::cout<<"After transform\n";
  // std::cout<<test;
  // matToComplex(test);
  genPoints(4, 0);
  return 0;
}

// [a b]
// [c d]
// ad - bc = M
