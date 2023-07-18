#define _USE_MATH_DEFINES
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <set>
#include "Commands.h"
#include "BaseStructs.h"
#include "PolygonCommands.h"

void mamonova::Commands::areaCommand()
{
  std::string command = "";
  std::cin >> command;
  int num = 0;
  try
  {
    num = std::stoi(command);
  }
  catch (const std::invalid_argument& e)
  {
    num = -1;
  }
  if (command == "ODD")
  {
    getAreaOdd(polygons_);
  }
  else if (command == "EVEN")
  {
    getAreaEven(polygons_);
  }
  else if (command == "MEAN" && polygons_.size() != 0)
  {
    getAreaMean(polygons_);
  }
  else if (num > 2)
  {
    getAreaNumOfVertexes(num, polygons_);
  }
  else
  {
    invalidCommand(std::cout);
  }
}

void mamonova::Commands::maxCommand()
{
  std::string command = "";
  std::cin >> command;
  if (command == "AREA" && polygons_.size() != 0)
  {
    getMaxArea(polygons_);
  }
  else if (command == "VERTEXES" && polygons_.size() != 0)
  {
    getMaxVertexes(polygons_);
  }
  else
  {
    invalidCommand(std::cout);
  }
}

void mamonova::Commands::minCommand()
{
  std::string command = "";
  std::cin >> command;
  if (command == "AREA" && polygons_.size() != 0)
  {
    getMinArea(polygons_);
  }
  else if (command == "VERTEXES" && polygons_.size() != 0)
  {
    getMinVertexes(polygons_);
  }
  else
  {
    invalidCommand(std::cout);
  }
}

void mamonova::Commands::countCommand()
{
  std::string command = "";
  std::cin >> command;
  int num = 0;
  try
  {
    num = std::stoi(command);
  }
  catch (const std::invalid_argument& e)
  {
    num = -1;
  }
  if (command == "EVEN")
  {
    getCountEven(polygons_);
  }
  else if (command == "ODD")
  {
    getCountOdd(polygons_);
  }
  else if (num > 2)
  {
    getCountNumOfVertexes(num, polygons_);
  }
  else
  {
    invalidCommand(std::cout);
  }
}

void mamonova::Commands::permsCommand()
{
  Polygon polygon;
  std::cin >> polygon;
  if (!polygon.points.empty())
  {
    getPerms(polygon, polygons_);
  }
  else
  {
    invalidCommand(std::cout);
  }
}

void mamonova::Commands::rectsCommand()
{
  if (polygons_.size() != 0)
  {
    getRects(polygons_);
  }
  else
  {
    invalidCommand(std::cout);
  }
}

void mamonova::Commands::invalidCommand(std::ostream& os)
{
  os << "<INVALID COMMAND>\n";
}

void mamonova::Commands::emptyMessage(std::ostream& os)
{
  os << "<EMPTY>\n";
}
