#ifndef BASESTRUCTS_H
#define BASESTRUCTS_H
#include <iosfwd>
#include <vector>

namespace mamonova
{
  struct Point
  {
    int x_;
    int y_;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  bool operator<(const Point& left, const Point& right);
  bool operator==(const Point& left, const Point& right);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
}

#endif
