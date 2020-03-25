#pragma once

#include <cfloat>
#include <cmath>

#define EQUAL(x, y) \
  (std::abs((x) - (y)) <= (FLT_EPSILON * (1llu << static_cast<size_t>(std::log2(std::max(std::abs(x), std::abs(y))) + 1))))

namespace my_math
{
  static constexpr double pi = std::acos(-1.0);
  double tan_sum(double tan1, double tan2);
}

