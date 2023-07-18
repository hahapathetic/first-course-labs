#ifndef OTHERSTRUCTS_H
#define OTHERSTRUCTS_H
#include <string>
#include <DelimeterIO.h>

struct UnsignedLongLongIO
{
  unsigned long long& ref;
};
struct CharIO
{
  char& ref;
};
struct StringIO
{
  std::string& ref;
};
struct LabelIO
{
  std::string exp;
};

std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
std::istream& operator>>(std::istream& in, CharIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);

#endif
