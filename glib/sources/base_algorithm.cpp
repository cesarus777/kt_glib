#include <stdexcept>
#include <vector>

#include <base.hpp>
#include <base_algorithm.hpp>
#include <macro/math_macro.hpp>

namespace mygeo
{
  double distance(Point p1, Point p2)
  {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return std::sqrt(x * x + y * y);
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

  Point intersect(Line l1, Line l2)
  {
    //l1 equals a*(x-x1)+b, l2 equals c*(x-x2)+d
    double a = l1.slope();
    double c = l2.slope();

    if(EQUAL(a, c))
      return Point(INFINITY, INFINITY);

    double b = l1.start().y;
    double d = l2.start().y;
    double x1 = l1.start().x;
    double x2 = l2.start().x;

    if(a == INFINITY)
      return Point(x1, c * (x1 - x2) + b);

    if(c == INFINITY)
      return Point(x2, a * (x2 - x1) + d);

    double x_intersect = (d - b - c * x2 + a * x1) / (a - c);

    double y_intersect = (a * d - b * c) / (a - c) + (x2 - x1) / (1.0 / a - 1.0 / c);

    return Point(x_intersect, y_intersect);
  }

  bool turn_left(Line l1, Line l2)
  {
    if(is_continuation(l1, l2) == false)
    {
      throw std::invalid_argument("Can't find turn direction : end of one line is not start of the second");
    }
    Point start = (l1.end() == intersect(l1, l2) ? l1.start() : l1.end());
    Point end = (l2.end() == intersect(l1, l2) ? l2.start() : l2.end());
    bool res = (((end.x - start.x) * l1.slope() + (start.y - end.y)) > 0.0);
    if(start == l1.end())
      res = !res;
    return res;
  }

  bool belongs_to(Point p, Line l)
  {
    Point sp = l.start();
    double k = (p.y - sp.y) / (p.x - sp.x);
    if((EQUAL(l.slope(), k)) == false)
      return false;
    Point ep = l.end();
    double dist1 = distance(p, sp);
    double dist2 = distance(p, ep);
    if((dist1 > l.len()) || (dist2 > l.len()))
      return false;

    return true;
  }

  bool are_intersected(Line l1, Line l2)
  {
    Point inter = intersect(l1, l2);
    return belongs_to(inter, l1) && belongs_to(inter, l2);
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

