#pragma once

namespace mygeo
{
  struct Point;

  class Line;

  double distance(Point p1, Point p2);

  bool isPolygon(std::vector<Point> vertices);

  bool is_continuation(Line l1, Line l2);

  bool turn_left(Line l1, Line l2);

  bool are_intersected(Line l1, Line l2);

  Point line_mid(Point p1, Point p2);

  Point line_mid(Line l);
}

