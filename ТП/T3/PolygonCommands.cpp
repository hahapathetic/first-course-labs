#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <set>
#include <cmath>
#include "PolygonCommands.h"

double mamonova::getArea(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    return 0.0;
  }
  return std::abs(accumulateTriangleArea(polygon, 0.0, 1));
}

void mamonova::getAreaEven(const std::vector< Polygon > polygons)
{
  double areaSum = 0;
  areaSum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
    [](double polygonArea, const Polygon& polygon)
    {
      if (polygon.points.size() % 2 == 0)
      {
        return polygonArea + getArea(polygon);
      }
      else
      {
        return polygonArea;
      }
    }
  );
  std::cout << std::fixed << std::setprecision(1) << areaSum << '\n';
}

void mamonova::getAreaOdd(const std::vector< Polygon > polygons)
{
  double areaSum = 0;
  areaSum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
    [](double polygonArea, const Polygon& polygon)
    {
      if (polygon.points.size() % 2 == 1)
      {
        return polygonArea + getArea(polygon);
      }
      else
      {
        return polygonArea;
      }
    }
  );
  std::cout << std::fixed << std::setprecision(1) << areaSum << '\n';
}

void mamonova::getAreaMean(const std::vector< Polygon > polygons)
{
  double areaSum = 0;
  areaSum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
    [](double polygonArea, const Polygon& polygon)
    {
      return polygonArea + getArea(polygon);
    }
  );
  std::cout << std::fixed << std::setprecision(1) << areaSum / polygons.size() << '\n';
}

void mamonova::getAreaNumOfVertexes(std::size_t vertexes, const std::vector< Polygon > polygons)
{
  double areaSum = 0;
  areaSum = std::accumulate(
    polygons.begin(),
    polygons.end(),
    0.0,
    [&vertexes](double polygonArea, const Polygon& polygon)
    {
      if (polygon.points.size() == vertexes)
      {
        return polygonArea + getArea(polygon);
      }
      else
      {
        return polygonArea;
      }
    }
  );
  std::cout << std::fixed << std::setprecision(1) << areaSum << '\n';
}

void mamonova::getMaxArea(const std::vector< Polygon > polygons)
{
  auto maxArea = std::max_element(polygons.begin(), polygons.end(),
    [](const Polygon& firstPolygon, const Polygon& secondPolygon)
    {
      return getArea(firstPolygon) < getArea(secondPolygon);
    }
  );
  std::cout << std::fixed << std::setprecision(1) << getArea(*maxArea) << '\n';
}

void mamonova::getMaxVertexes(const std::vector< Polygon > polygons)
{
  auto maxVertexes = std::max_element(polygons.begin(), polygons.end(),
    [](const Polygon& firstPolygon, const Polygon& secondPolygon)
    {
      return firstPolygon.points.size() < secondPolygon.points.size();
    }
  );
  std::cout << std::fixed << std::setprecision(1) << maxVertexes->points.size() << '\n';
}

void mamonova::getMinArea(const std::vector< Polygon > polygons)
{
  auto minArea = std::min_element(polygons.begin(), polygons.end(),
    [](const Polygon& firstPolygon, const Polygon& secondPolygon)
    {
      return getArea(firstPolygon) < getArea(secondPolygon);
    }
  );
  std::cout << std::fixed << std::setprecision(1) << getArea(*minArea) << '\n';
}

void mamonova::getMinVertexes(const std::vector< Polygon > polygons)
{
  auto minVertexes = std::min_element(polygons.begin(), polygons.end(),
    [](const Polygon& firstPolygon, const Polygon& secondPolygon)
    {
      return firstPolygon.points.size() < secondPolygon.points.size();
    }
  );
  std::cout << std::fixed << std::setprecision(1) << minVertexes->points.size() << '\n';
}

void mamonova::getCountEven(const std::vector< Polygon > polygons)
{
  size_t count = 0;
  count = std::count_if(polygons.begin(), polygons.end(),
    [](const Polygon& polygon)
    {
      return polygon.points.size() % 2 == 0;
    }
  );
  std::cout << std::fixed << std::setprecision(1) << count << '\n';
}

void mamonova::getCountOdd(const std::vector< Polygon > polygons)
{
  size_t count = 0;
  count = std::count_if(polygons.begin(), polygons.end(),
    [](const Polygon& polygon)
    {
      return polygon.points.size() % 2 == 1;
    }
  );
  std::cout << std::fixed << std::setprecision(1) << count << '\n';
}

void mamonova::getCountNumOfVertexes(std::size_t vertexes, const std::vector< Polygon > polygons)
{
  size_t count = 0;
  count = std::count_if(polygons.begin(), polygons.end(),
    [&vertexes](const Polygon& polygon)
    {
      return polygon.points.size() == vertexes;
    }
  );
  std::cout << std::fixed << std::setprecision(1) << count << '\n';
}

bool mamonova::isRectangle(const Polygon& polygon)
{
  bool check = false;
  if (polygon.points.size() == 4)
  {
    Point p1 = polygon.points[0];
    Point p2 = polygon.points[1];
    Point p3 = polygon.points[2];
    Point p4 = polygon.points[3];
    check = (((p2.x_ - p1.x_) == (p3.x_ - p4.x_)) && ((p4.y_ - p1.y_) == (p3.y_ - p2.y_))) ||
      (((p2.y_ - p1.y_) == (p3.y_ - p4.y_)) && ((p4.x_ - p1.x_) == (p3.x_ - p2.x_)));
    return check && (((p2.x_ - p1.x_) * (p2.x_ - p1.x_) + (p4.y_ - p1.y_) * (p4.y_ - p1.y_)) ==
        ((p3.y_ - p2.y_) * (p3.y_ - p2.y_) + (p3.x_ - p4.x_) * (p3.x_ - p4.x_)));
  }
  return false;
}

size_t mamonova::countPerms(const Polygon& polygon)
{
  std::set<Point> unique_points(polygon.points.begin(), polygon.points.end());
  if (unique_points.size() == polygon.points.size())
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

bool mamonova::isMatch(const Polygon& example, const Polygon& polygon)
{
  if (polygon.points.size() != example.points.size())
  {
    return false;
  }
  std::vector< Point > sortedPolygonPoints = polygon.points;
  std::sort(sortedPolygonPoints.begin(), sortedPolygonPoints.end());
  std::vector< Point > sortedExamplePoints = example.points;
  std::sort(sortedExamplePoints.begin(), sortedExamplePoints.end());
  return std::equal(sortedPolygonPoints.begin(), sortedPolygonPoints.end(), sortedExamplePoints.begin());
};

void mamonova::getPerms(const Polygon& example, const std::vector< Polygon > polygons)
{
  size_t count = std::count_if(
    polygons.begin(),
    polygons.end(),
    [&example](const Polygon& polygon)
      {
        return isMatch(example, polygon) && countPerms(polygon);
      }
    );
  std::cout << std::fixed << std::setprecision(1) << count << '\n';
}

void mamonova::getRects(const std::vector< Polygon > polygons)
{
  size_t count = 0;
  count = std::count_if(polygons.begin(), polygons.end(),
    [](const Polygon& polygon)
    {
      return isRectangle(polygon);
    }
  );
  std::cout << std::fixed << std::setprecision(1) << count << '\n';
}

double mamonova::calculateTriangleArea(const Point& point1, const Point& point2, const Point& point3)
{
  return 0.5 * (point1.x_ * point2.y_ - point2.x_ * point1.y_ + point2.x_ *
    point3.y_ - point3.x_ * point2.y_ + point3.x_ * point1.y_ - point1.x_ * point3.y_);
}

double mamonova::accumulateTriangleArea(const Polygon& polygon, double total, size_t i)
{
  if (i + 1 < polygon.points.size())
  {
    const Point& p1 = polygon.points[0];
    const Point& p2 = polygon.points[i];
    const Point& p3 = polygon.points[i + 1];
    double triangleArea = calculateTriangleArea(p1, p2, p3);
    return accumulateTriangleArea(polygon, total + triangleArea, i + 1);
  }
  return total;
}
