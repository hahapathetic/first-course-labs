#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include "Commands.h"
#include "Dictionary.h"
#include "CommonCommands.h"

int main()
{
  Dictionary dictionary;
  readFile(L"count.txt", dictionary);
  Commands inCommand(std::wcout, std::wcin, dictionary);
  std::map< std::wstring, std::function< void() > > commandMap =
  {
    {L"HELP", std::bind(&Commands::help, std::ref(inCommand))},
    {L"SHOW", std::bind(&Commands::show, std::ref(inCommand))},
    {L"ADD", std::bind(&Commands::add, std::ref(inCommand))},
    {L"DELETE", std::bind(&Commands::remove, std::ref(inCommand))},
    {L"MERGE", std::bind(&Commands::merge, std::ref(inCommand))},
    {L"MERGEUNIQUE", std::bind(&Commands::mergeUnique, std::ref(inCommand))}
  };
  std::wstring command = L"";
  std::getline(std::wcin, command);
  while (!std::wcin.eof())
  {
    try
    {
      auto it = commandMap.find(command);
      if (it != commandMap.end())
      {
        it->second();
      }
      else
      {
        getInvalidMessage(std::wcin, std::wcout);
        std::wcin.ignore(1024, L'\n');
      }
      std::wcin.clear();
      std::getline(std::wcin, command);
    }
    catch (const std::invalid_argument& e)
    {
      std::wcout << e.what() << std::endl;
    }
  }
  return 0;
}
