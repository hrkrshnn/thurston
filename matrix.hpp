#include "iostream"

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


  template <typename S>
  friend std::ostream& operator<< (std::ostream& out, const matrix<S>& mat)
  {
    out<<"["<<mat.a<<", "<<mat.b<<"], ["<<mat.c<<", "<<mat.d<<"]"<<std::endl;
    return out;
  }
};

template <typename T>
T det(const matrix<T> mat)
{
  return mat.a*mat.d - mat.b*mat.c;
}

