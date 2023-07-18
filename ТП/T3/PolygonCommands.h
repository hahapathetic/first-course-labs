#ifndef POLYGONCOMMANDS_H
#define POLYGONCOMMANDS_H

#include "BaseStructs.h"
namespace mamonova
{
  double getArea(const Polygon& polygons);
  void getAreaEven(const std::vector< Polygon > polygons);
  void getAreaOdd(const std::vector< Polygon > polygons);
  void getAreaMean(const std::vector< Polygon > polygons);
  void getAreaNumOfVertexes(std::size_t vertexes, const std::vector< Polygon > polygons);
  void getMaxArea(const std::vector< Polygon > polygons);
  void getMaxVertexes(const std::vector< Polygon > polygons);
  void getMinArea(const std::vector< Polygon > polygons);
  void getMinVertexes(const std::vector< Polygon > polygons);
  void getCountEven(const std::vector< Polygon > polygons);
  void getCountOdd(const std::vector< Polygon > polygons);
  void getCountNumOfVertexes(std::size_t vertexes, const std::vector< Polygon > polygons);
  bool isRectangle(const Polygon& polygon);
  size_t countPerms(const Polygon& polygon);
  bool isMatch(const Polygon& example, const Polygon& polygon);
  void getPerms(const Polygon& example, const std::vector< Polygon > polygons);
  void getRects(const std::vector< Polygon > polygons);
  double calculateTriangleArea(const Point& p1, const Point& p2, const Point& p3);
  double accumulateTriangleArea(const Polygon& polygon, double total, size_t i);
}

#endif
