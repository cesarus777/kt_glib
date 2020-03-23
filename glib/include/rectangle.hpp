#pragma once

#include <stdexcept>
#include <vector>

#include <base.hpp>
#include <base_algorithm.hpp>

namespace mygeo
{
  class Rectangle : public Polygon
  {
  protected:
    double short_side, long_side;
  public:
    Rectangle(std::vector<Point> v, double ratio) : Polygon(v, RECTANGLE)
    {
      if(v.size() != 2)
        throw std::invalid_argument("Invalid Rectange : wrong number of points");
    }
  };
}

