#include <cmath>

#include <macro/math_macro.hpp>

namespace my_math
{
  double tan_sum(double tan1, double tan2)
  {
    if(tan1 == INFINITY)
      return 1 / tan2;
    if(tan2 == INFINITY)
      return 1 / tan1;
    return ((tan1 + tan2) / (1.0 - tan1 * tan2));
  }
}

