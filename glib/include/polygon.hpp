#pragma once

#include <stdexcept>
#include <vector>

#include <base_algorithm.hpp>

namespace mygeo
{
  class Polygon : public Shape
  {
  protected:
    std::vector<Point> vertices;

    Polygon(const std::vector<Point>& points, types t) : Shape(t)
    {
      if(isPolygon(points) == false)
      {
        throw std::invalid_argument("Invalid Polygon : bad point set");
      }
      vertices = points;  
    }
  public:
    Polygon(const std::vector<Point>& points) : Shape(POLYGON)
    {
      if(isPolygon(points) == false)
      {
        throw std::invalid_argument("Invalid Polygon : bad point set");
      }
      vertices = points;
    }

    Polygon(const std::vector<Line>& lines) : Shape(POLYGON)
    {
      for(size_t i = 0; i < lines.size(); ++i)
      {
        if(i == (lines.size() - 1))
        {
          if(is_continuation(lines[0], lines[i]) == false)
          {
            throw std::invalid_argument("Invalid Polygon : bad line set::end of one line is not start of the second");
          }
        } else if(is_continuation(lines[i], lines[i + 1]) == false)
        {
          throw std::invalid_argument("Invalid Polygon : bad line set::end of one line is not start of the second");
        }
        for(size_t j = i + 1; j < lines.size(); ++j)
        {
          if(are_intersected(lines[i], lines[j]))
          {
            throw std::invalid_argument("Invalid Polygon : bad line set::lines intersect");
          }
        }
        if((i != 0) && (lines[i].start() == vertices[i - 1]))
          vertices.push_back(lines[i].end());
        else
          vertices.push_back(lines[i].start());
      }

    }

    virtual double perimeter()
    {
      size_t size = vertices.size();
      double result = 0;
      for(size_t i = 0; i < size; ++i)
      {
        if(i == 0)
          result += distance(vertices[0], vertices[size - 1]);
        else
          result += distance(vertices[i - 1], vertices[i]);
      }
      return result;
    }

    virtual double area()
    {
      double result = 0;
      size_t size  = vertices.size() - 1;
      for(size_t i = 0; i < size; ++i)
      {
        result += vertices[i].x * vertices[i + 1].y;
        result -= vertices[i + 1].x * vertices[i].y;
      }
      result += vertices[size].x * vertices[0].y;
      result -= vertices[0].x * vertices[size].y;
      result = std::abs(result);
      return result / 2;
    }

    size_t verticesCount() const { return vertices.size(); }

    std::vector<Point> getVertices() const { return vertices; }

    bool isConvex() const
    {
      size_t size = vertices.size();
      bool turn;
      for(size_t i = 0; i < size; ++i)
      {
        if(i == 0)
        {
          Line AB(vertices[size - 1], vertices[0]);
          Line BC(vertices[1], vertices[0]);
          turn = turn_left(AB, BC);
        } else if(i == size - 1) {
          Line AB(vertices[size - 2], vertices[i - 1]);
          Line BC(vertices[size - 1], vertices[0]);
          if(turn != turn_left(AB, BC))
            return false;
        } else {
          Line AB(vertices[i - 1], vertices[i]);
          Line BC(vertices[i + 1], vertices[i]);
          if(turn != turn_left(AB, BC))
            return false;
        }
      }
      return true;
    }
  };
}

