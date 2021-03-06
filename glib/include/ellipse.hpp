#pragma once

#include <cmath>
#include <stdexcept>

#include <base.hpp>
#include <base_algorithm.hpp>
#include <macro/math_macro.hpp>

namespace mygeo
{
  class Ellipse : public Shape
  {
  protected:
    Point x1, x2;
    double a;

    Ellipse(Point p1, Point p2, double dist, types t) : Shape(t), x1(p1), x2(p2), a(dist/2)
    {
      if(dist <= distance(x1, x2))
        throw std::invalid_argument("Invalid Ellipse : semi-major axis <= linear eccentricity");
    }
  public:
    Ellipse(Point p1, Point p2, double dist) : Shape(ELLIPSE), x1(p1), x2(p2), a(dist / 2)
    {
      if(dist <= distance(x1, x2))
        throw std::invalid_argument("Invalid Ellipse : semi-major axis <= linear eccentricity");
    }

    std::pair<Point, Point> focuses() const
    {
      return std::make_pair(x1, x2);
    }

    double fdistance() const
    {
      return distance(x1, x2);
    }

    double eccentricity() const
    {
      return fdistance() / (2 * a);
    }

    Point center() const
    {
      return line_mid(x1, x2);
    }

    virtual double perimeter() const
    {
      double d = fdistance() / 2;
      double b = std::sqrt(a * a - d * d);
      double q = (a - b) * (a - b);
      return 4 * (my_math::pi * a * b + q) / (a + b);
    }

    virtual double area() const
    {
      double d = fdistance() / 2;
      double b = std::sqrt(a * a - d * d);
      return my_math::pi * a * b;
    }

    virtual bool operator==(const Shape& another) const
    {
      if(type != another.get_type())
        return false;

      return (*this == another);
    }
    
    virtual bool operator==(const Ellipse& another) const
    {
      return (focuses() == another.focuses()) && (eccentricity() == another.eccentricity());
    }


    virtual bool isCongruentTo(const Shape& another) const
    {
      if(another.get_type() != type)
        return false;

      return isCongruentTo(another);;
    } 

    virtual bool isCongruentTo(const Ellipse& another) const
    {
      return (eccentricity() == another.eccentricity()) && (fdistance() == another.fdistance());
    }

    virtual bool containsPoint(Point point) const
    {
      double d1 = distance(x1, point);
      double d2 = distance(x2, point);
      return (d1 + d2) <= (2 * a);
    }
  };
}

