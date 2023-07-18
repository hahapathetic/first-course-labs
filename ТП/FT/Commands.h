#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include "Dictionary.h"

struct Commands
{
public:
  Commands(std::wostream& out, std::wistream& in, Dictionary& dict);
  void help();
  void show();
  void add();
  void remove();
  void merge();
  void mergeUnique();
private:
  Dictionary dict_;
  std::wostream& out_;
  std::wistream& in_;
};

#endif
