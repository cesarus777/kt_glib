#pragma once

#include <base.hpp>

namespace mygeo
{
  class Triangle : public Polygon
  {
  public:
    Triangle(Point p1, Point p2, Point p3) : Polygon({ p1, p2, p3 }, TRIANGLE) {}

    Triangle(std::vector<Point> v) : Polygon(v, TRIANGLE)
    {
      if(v.size() != 3)
        throw std::invalid_argument("Invalid Triangle : wrong number of points");
    }
  };
}
