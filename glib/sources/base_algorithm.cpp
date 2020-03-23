#include <stdexcept>
#include <vector>

#include <base.hpp>
#include <base_algorithm.hpp>

namespace mygeo
{
  double distance(Point p1, Point p2)
  {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return sqrt(x * x - y * y);
  }

  bool isPolygon(std::vector<Point> vertices)
  {
    size_t size = vertices.size();
    if(size < 3)
      return false;
    for(size_t i = 0; i < size; ++i)
    {
      Line l1 = (i == 0) ? Line(vertices[i], vertices[size - 1])
                         : Line(vertices[i - 1], vertices[i]);
      for(size_t j = i + 1; j < size; ++j)
      {
        if(i == j)
          break;
        
        Line l2 = (j == 0) ? Line(vertices[j], vertices[size - 1])
                           : Line(vertices[j - 1], vertices[j]);

        if(are_intersected(l1, l2))
          return false;
      }
    }
    return true;
  }

  bool is_continuation(Line l1, Line l2)
  {
    return (l1.start() == l2.start()) || (l1.start() == l2.end())
        || (l1.end() == l2.start())   || (l1.end() == l2.end());
  }

  bool turn_left(Line l1, Line l2)
  {
    if(is_continuation(l1, l2) == false)
    {
      throw std::invalid_argument("Can't find turn direction : end of one line is not start of the second");
    }
    return (l1.xlen() * l2.ylen() - l1.ylen() * l2.xlen()) > 0.0;
  }

  bool are_intersected(Line l1, Line l2)
  {
    //l1 equals a*x+b, l2 equals c*x+d
    double a = l1.slope();
    double c = l2.slope();

    Point start_point1 = l1.start();
    Point end_point1 = l1.end();
    Point start_point2 = l2.start();
    Point end_point2 = l2.end();

    if((a != c) && ((start_point1 == start_point2) || (end_point1 == end_point2)))
      return false;

    double b = start_point1.y;
    double d = start_point2.y;

    double p1sy = b;
    double p1ey = end_point1.y;
    double p2sy = d;
    double p2ey = end_point2.y;

    if((a == c) && (((p1sy <= p2sy) && (p1sy >= p2ey)) || ((p2sy <= p1sy) && (p2sy >= p1ey))))
      return false;

    double x_intersec = (d - c) / (a - b);
    if((((x_intersec < start_point1.x) && (x_intersec > end_point1.x)) ||
       ((x_intersec < start_point1.x) && (x_intersec > end_point1.x))) == false)
      return false;

    double y_intersec = (a * d - b * c) / (a - b);
    if((((y_intersec < start_point1.y) && (y_intersec > end_point1.y)) ||
       ((y_intersec < start_point1.y) && (y_intersec > end_point1.y))) == false)
      return false;

    return true;
  }

  Point line_mid(Point p1, Point p2)
  {
    return Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
  }

  Point line_mid(Line l)
  {
    return line_mid(l.start(), l.end());
  }
}

