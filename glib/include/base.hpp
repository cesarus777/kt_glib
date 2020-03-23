#pragma once

#include <cmath>
#include <stdexcept>
#include <vector>

#include <base_algorithm.hpp>

namespace mygeo
{
  enum types { SHAPE, POLYGON, ELLIPSE, CIRCLE, RECTANGLE, SQUARE, TRIANGLE };

  struct Point
  {
    double x, y;

    Point(double a, double b) : x(a), y(b) {}
    Point(const Point& p) : x(p.x), y(p.y) {}

    Point& operator=(const Point &another)
    {
      x = another.x;
      y = another.y;
      return *this;
    }

    bool operator==(const Point &another) const
    {
      return (x == another.x) && (y == another.y);
    }

    bool operator!=(const Point &another) const
    {
      return (x != another.x) || (y != another.y);
    }

  };

  class Line
  {
    Point a, b;
    double length;
    double k;
  public:
    Line(Point p1, Point p2) : a(p1), b(p2)
    {
      if(a == b)
      {
        throw std::invalid_argument("Invalid Line : its ends match");
      }
      double y_len = b.y - a.y;
      if(y_len < 0)
      {
        std::swap(a, b);
        y_len *= (-1);
      }
      double x_len = b.x - a.x;
      if((y_len == 0) && (x_len < 0))
      {
        std::swap(a, b);
        x_len *= (-1);
      }
      length = std::sqrt(x_len * x_len + y_len * y_len);
      k = y_len / x_len;
    }

    Line(Point p, double koeff, double dist) : a(p), b(p), k(koeff), length(dist)
    {
      if(length == 0)
      {
        throw std::invalid_argument("Invalid Line : length == 0");
      }
      if(k == 0)
      {
        b.x = a.x + length;
        b.y = a.y;
      } else {
        double add_to_x = length / std::sqrt(1 + k * k) * ((k >= 0) ? 1 : -1);
        b.x = a.x + length / add_to_x;
        b.y = a.y + add_to_x * k;
      }
    }

    Line(const Line& another) : a(another.start()),
                                b(another.end()),
                                length(another.len()),
                                k(another.slope()) {}

    Line& operator=(const Line& another)
    {
      a = another.start();
      b = another.end();
      length = another.len();
      k = another.slope();
      return *this;
    }

    Point start() const { return a; }
    Point end() const { return b; }
    double slope() const { return k; }
    double len() const { return length; }
    double xlen() const { return std::abs(a.x - b.x); }
    double ylen() const { return std::abs(a.y - b.y); }

    bool operator==(const Line& another) const
    {
      return (a == another.a) && (b == another.b);
    }

    bool operator!=(const Line& another) const
    {
      return (a != another.a) || (b != another.b);
    }
  };

  class Shape
  {
  protected:
    const types type;
    Shape(types t) : type(t) {};
  public:
    Shape() : type(SHAPE) {}
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    size_t get_type() const { return type; }
    virtual bool operator==(const Shape& another) const = 0;
    virtual bool isCongruentTo(const Shape& another) const
    {
      return type == another.get_type();
    }
    virtual bool containsPoint(Point point) const = 0;
  };
}

