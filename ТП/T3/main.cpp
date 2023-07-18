#include <fstream>
#include <iostream>
#include <map>
#include <functional>
#include <iterator>
#include "Commands.h"
#include "BaseStructs.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid arguments." << '\n';
    return 1;
  }

  std::ifstream in(argv[1]);

  if (!in)
  {
    std::cerr << "File opening error." << '\n';
    return 2;
  }

  std::vector< mamonova::Polygon > figures;
  while (!in.eof())
  {
    in.clear();
    std::copy(
      std::istream_iterator< mamonova::Polygon >(in),
      std::istream_iterator< mamonova::Polygon >(),
      std::back_inserter(figures)
    );
  }
  mamonova::Commands command;
  command.polygons_ = figures;
  std::map < std::string, std::function< void() > > cmdMap
  {
    {"AREA", std::bind(&mamonova::Commands::areaCommand, std::ref(command))},
    { "MAX", std::bind(&mamonova::Commands::maxCommand, std::ref(command)) },
    { "MIN", std::bind(&mamonova::Commands::minCommand, std::ref(command)) },
    { "COUNT", std::bind(&mamonova::Commands::countCommand, std::ref(command)) },
    { "PERMS", std::bind(&mamonova::Commands::permsCommand, std::ref(command)) },
    { "RECTS", std::bind(&mamonova::Commands::rectsCommand, std::ref(command)) }
  };
  std::string cmd = "";
  std::cin >> cmd;
  while (!std::cin.eof())
  {
    auto it = cmdMap.find(cmd);
    if (it != cmdMap.end())
    {
      it->second();
    }
    else
    {
      command.invalidCommand(std::cout);
      std::cin.ignore(256, '\n');
    }
    std::cin.clear();
    std::cin >> cmd;
  }
  in.close();
  return 0;
}
