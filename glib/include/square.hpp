#pragma once

#include <base.hpp>
#include <base_algorithm.hpp>
#include <circle.hpp>
#include <rectangle.hpp>

namespace mygeo
{
  class Square : public Rectangle
  {
  public:
    Square(Point p1, Point p3) : Rectangle(p1, p3, 1.0, SQUARE) {}

    Circle circumscribedCircle()
    {
      Point c = center();
      double r = distance(c, vertices[0]);
      return Circle(c, r);
    }

    Circle inscribedCircle()
    {
      Point c = center();
      double r = distance(vertices[0], vertices[1]) / 2;
      return Circle(c, r);
    }
  };
}
