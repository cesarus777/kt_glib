#pragma once

#include <cmath>
#include <stdexcept>
#include <vector>

#include <base.hpp>
#include <base_algorithm.hpp>
#include <macro/math_macro.hpp>

namespace mygeo
{
  class Rectangle : public Polygon
  {
  protected:
    Rectangle(Point p1, Point p3, double ratio, types type) : Polygon({p1, p1, p3, p3}, type)
    {
      Line diag(p1, p3);
      Line side(p1, my_math::tan_sum(diag.slope(), -ratio), diag.len() * std::cos(std::atan(ratio)));
      Point p2 = (side.end() == p1) ? side.start() : side.end();
      vertices[1] = p2;
      Point centre = line_mid(diag);
      Line another_diag(p2, (centre.y - p2.y) / (centre.x - p2.x), diag.len());
      Point p4 = (another_diag.end() == p2) ? another_diag.start() : another_diag.end();
      vertices[3] = p4;
    }
  public:
    Rectangle(Point p1, Point p3, double ratio) : Rectangle(p1, p3, ratio, RECTANGLE) {}

    Point center()
    {
      Line diag(vertices[0], vertices[2]);
      return line_mid(diag);
    }

    std::pair<Line, Line> diagonals()
    {
      Line diag1(vertices[0], vertices[2]);
      Line diag2(vertices[1], vertices[3]);
      return std::make_pair(diag1, diag2);
    }
  };
}

