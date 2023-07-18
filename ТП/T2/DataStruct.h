#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <string>

struct Data
{
  unsigned long long key1;
  char key2;
  std::string key3;
};

std::istream& operator>>(std::istream& in, Data& dest);
std::ostream& operator<<(std::ostream& out, const Data& dest);
bool operator<(const Data& left, const Data& right);

#endif
