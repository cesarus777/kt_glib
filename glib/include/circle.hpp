#pragma once

#include <base.hpp>
#include <base_algorithm.hpp>
#include <ellipse.hpp>

namespace mygeo
{
  class Circle : public Ellipse
  {
  public:
    Circle(Point p, double r) : Ellipse(p, p, r) {}

    double radius() { return a; }
  };
}

