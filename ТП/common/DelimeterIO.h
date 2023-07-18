#ifndef DELIMETERIO_H
#define DELIMETERIO_H
#include <iomanip>

struct DelimeterIO
{
  explicit DelimeterIO(char exp);
  char exp;
};
std::istream& operator>>(std::istream& in, DelimeterIO&& dest);

#endif
