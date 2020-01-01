#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <set>

// For complex numbers
#include <boost/multiprecision/mpc.hpp>
#include <boost/multiprecision/mpfr.hpp>
#include <boost/multiprecision/debug_adaptor.hpp>

namespace mp = boost::multiprecision;

using complex = mp::mpc_complex;

namespace th
{
  // tolerance for comparisons
  const double tol = 1e-10;

  // We are interested in a certain space of 2x2 integer matrices with constant
  // determinant. I've chosen to simply represent the matrix with 4 integers
  //
  // | a  b |
  // | c  d |
  //
  // The structure lets you access the elements of the matrix by using ()
  // operators: For example c = mat(1, 0). On top of that, the function
  // toComplex() returns the representative of the matrix (c + d*omega)/(a +
  // b*omega) in the upper half space of the complex plane or the hyperbolic
  // plane. A comparison operator is also implemented. See comments next to it
  // for details.
  template <typename Z>
  struct matrix
  {
    Z a, b, c, d;

    // A constructor
    matrix(Z a0, Z b0, Z c0, Z d0): a(a0), b(b0), c(c0), d(d0)
    {
      ;
    }

    // operator ()
    Z& operator()(const bool i, const bool j)
        {
      if(i == 0 && j == 0) return a;
      else if(i == 0 && j == 1) return b;
      else if(i == 1 && j == 0) return c;
      else return d;
    }

    // operator ()
    const Z operator()(const bool i, const bool j) const
            {
      if(i == 0 && j == 0) return a;
      else if(i == 0 && j == 1) return b;
      else if(i == 1 && j == 0) return c;
      else return d;
    }

    // Returns a representative in the upper half space of the Complex plane or
    // the hyperbolic space.
    auto toComplex() const
    {
      const complex omega{0.5, std::sqrt(3)/2};
      complex z = (c + omega*d)/(a + omega*b);
      return z;
    }

    // Technically, such matrices do not have a comparison operators. But since
    // we are interested distinguishing between elements of the matrices upto a
    // SL_2(Z) x Z_6 action, this comparison operator comes in handy; in
    // particular when we build a std::set() of such matrices, this comparison
    // will remove duplicates upto such an action, provides that that each of
    // the matrices lie inside the fundamental region of PSL_2(Z).
    auto operator< (const matrix<Z> mat) const
    {
      auto x = mp::abs(this->toComplex());
      auto y = mp::abs(mat.toComplex());

      if(mp::abs(x - y) < tol)
          return false;
      else
          return x < y;
        }

    // Pretty print the operator to output stream.
    template <typename S>
    friend std::ostream& operator<< (std::ostream& out, const matrix<S>& mat)
    {
      out<<"["<<mat.a<<", "<<mat.b<<"], ["<<mat.c<<", "<<mat.d<<"] z:"<<mat.toComplex()<<"\n";
      return out;
    }

  };

  // The determinant of such a matrix; Simply (ad - bc)
  template <typename T>
  T det(const matrix<T> mat)
  {
    return mat.a*mat.d - mat.b*mat.c;
  }

}

#endif  // MATRIX_HPP
