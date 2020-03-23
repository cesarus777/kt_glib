#include <cmath>

#include <macro/math_macro.hpp>

namespace my_math
{
  double tan_sum(double tan1, double tan2)
  {
    return ((tan1 + tan2) / (1.0 - tan1 * tan2));
  }
}

