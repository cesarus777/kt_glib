#pragma once

#include <vector>

#include <base.hpp>

namespace mygeo
{
  struct Point;

  class Line;

  double distance(Point p1, Point p2);

  bool isPolygon(std::vector<Point> vertices);

  Point intersect(Line l1, Line l2);

  bool is_continuation(Line l1, Line l2);

  bool turn_left(Line l1, Line l2);

  bool are_intersected(Line l1, Line l2);

  bool belongs_to(Point p, Line l);

  Point line_mid(Point p1, Point p2);

  Point line_mid(Line l);
}

