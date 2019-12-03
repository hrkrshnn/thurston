#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "matrix.hpp"

#include <string>
#include <fstream>
// For the extended euclidean algorithm
#include <boost/integer/extended_euclidean.hpp>
// For matrices
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace th
{
  const complex omega{0.5, std::sqrt(3)/2};
  const std::size_t iterMax = 10000;
  const double ctol = 1e-10;

  // Given a matrix mat, this applies the algorithm 2 from the thesis to
  // transform it to a fundamental region of the hyperbolic space.
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
                       complex num = (mat(1, 0) + omega*mat(1, 1))/(mat(0, 0) + omega*mat(0, 1));
                       return num;
                     };

    // Function that checks if the element is in the fundamental domain
    auto isFundamental = [&mat]()
                         {
                           auto z = mat.toComplex();
                           if(mp::abs(z) >= 1 - ctol && z.real() < 0.5 && z.real() >= -0.5)
                             {
                               return true;
                             }
                           else
                             {
                               return false;
                             }
                         };

    std::size_t iter = 0;
    while(iter < iterMax)
      {
        auto z = mat.toComplex();
        if(mp::abs(z) < 1 - ctol)
          {
            inversion();

            assert(det(mat) == oldDet);
          }
        else if(z.real() < -0.5)
          {
            Z k = mp::floor(z.real() - 0.5);
            translate(-k);

            assert(det(mat) == oldDet);
            // do a translation
          }
        else if(z.real() >= 0.5)
          {
            Z k = mp::floor(z.real() + 0.5);
            translate(-k);

            assert(det(mat) == oldDet);
          }
        else                      // the number is in the fundamental region
          {
            break;
          }

        std::cout<<mat;

        ++iter;
      }

    // An assert to verify that the determinant is unchanged
    assert(det(mat) == oldDet);
    // An assert to verify if the element is in the Fundamental region
    assert(isFundamental());
  }

  // The old "monte-carlo" style algorithm to generate the matrices. See
  // algorithm 3 in the thesis.
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

  // computes the GCD of two number.
  template <typename Z>
  auto gcd(Z a, Z b)
  {
    return boost::integer::extended_euclidean(a, b).gcd;
  }

  // Computes matrices of the form [a b][0 d] such that b < d and ad = M. This
  // implements Algorithm 1 and calls Algorithm 2 (from the thesis.)
  template <typename Z>
  auto genSpace(Z M)
  {
    std::vector<matrix<Z>> solSpace;

    for(Z i = 1; i <= M; ++i)
      {
        if(M % i == 0)
          {
            Z a = i, d = M/i;
            for(Z b = 0; b < d; ++b)
              {
                matrix<Z> tmp(a, b, 0, d);
                std::cout<<tmp;

                fundTransform(tmp); // Do a transformation to the
                // fundamental domain before pushing it
                std::cout<<std::endl;

                solSpace.push_back(tmp);
              }
          }
      }

    return solSpace;
  }

  // Since our algorithm may give us duplicates in the fundamental region, this
  // will remove it.
  template <typename Z>
  auto removeDuplicates(std::vector<matrix<Z>> mats)
  {
    // constructs a std::set and thereby removing the duplicates

    std::set<matrix<Z>> outs(std::cbegin(mats), std::cend(mats));

    return outs;
  }

  complex toDiscModel(const complex& z)
  {
    complex i = complex{0, 1};
    return (z - i)/(z + i);
  }

  // Write a data structure that is iterable to a file
  template <typename Z>
  auto writeFile(const std::set<matrix<Z>>& outs, const std::string& fname)
  {
    std::ofstream myfile("../out/" + fname);

    myfile<<"x, y\n";
    for(const auto& v:outs)
      {
        auto x = toDiscModel(v.toComplex());
        myfile<<x.real()<<","<<x.imag()<<"\n";
      }
  }



} // namespace th

#endif  // ALGORITHMS_HPP
