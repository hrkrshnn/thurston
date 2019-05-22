#include "iostream"
// For complex numbers
#include <boost/multiprecision/mpc.hpp>
#include <boost/multiprecision/mpfr.hpp>

namespace mp = boost::multiprecision;

// tolerance for comparisons
const double tol = 1e-10;

// A 2 by 2 matrix
template <typename Z>
struct matrix
{
  Z a, b, c, d;

  // operator ()
  Z& operator()(const std::size_t i, const std::size_t j)
  {
    if(i)                       // i = 1
      {
        if(j)                   // j = 1
          {
            return d;
          }
        else
          {
            return c;
          }
      }
    else                        // i = 0
      {
        if(j)
          {
            return b;
          }
        else
          {
            return a;
          }
      }
  }

  const Z operator()(const std::size_t i, const std::size_t j) const
  {
    if(i)                       // i = 1
      {
        if(j)                   // j = 1
          {
            return d;
          }
        else
          {
            return c;
          }
      }
    else                        // i = 0
      {
        if(j)
          {
            return b;
          }
        else
          {
            return a;
          }
      }
  }

  auto toComplex() const
  {
    const mp::mpc_complex omega{0.5, std::sqrt(3)/2};
    mp::mpc_complex z = (c + omega*d)/(a + omega*b);
    return z;
  }

  auto operator< (const matrix<Z> mat) const
  {
    auto x = mp::abs(this->toComplex());
    auto y = mp::abs(mat.toComplex());

    if(mp::abs(x - y) < tol)
      {
        return false;
      }
    else
      {
        return x < y;
      }

  }


  template <typename S>
  friend std::ostream& operator<< (std::ostream& out, const matrix<S>& mat)
  {
    out<<"["<<mat.a<<", "<<mat.b<<"], ["<<mat.c<<", "<<mat.d<<"] z:"<<mat.toComplex()<<std::endl;
    return out;
  }

};

template <typename T>
T det(const matrix<T> mat)
{
  return mat.a*mat.d - mat.b*mat.c;
}

