#include "DataStruct.h"
#include "OtherStructs.h"
#include "IOfmtGuard.h"
#include <iomanip>

std::istream& operator>>(std::istream& in, Data& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Data input;
  {
    using sep = DelimeterIO;
    using ull = UnsignedLongLongIO;
    using chr = CharIO;
    using str = StringIO;
    std::string temp = "";
    in >> sep{ '(' };
    in >> sep{ ':' };
    for (int i = 0; i < 3; i++)
    {
      in >> temp;
      if (temp == "key1")
      {
        in >> ull{ input.key1 };
        in >> sep{ ':' };
      }
      else if (temp == "key2")
      {
        in >> chr{ input.key2 };
        in >> sep{ ':' };
      }
      else if (temp == "key3")
      {
        in >> str{ input.key3 };
        in >> sep{ ':' };
      }
    }
    in >> sep{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Data& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:";
  out << "key1 " << std::fixed << std::setprecision(1) << src.key1 << "ull:";
  out << "key2 " << "\'" << src.key2 << "\'" << ":";
  out << "key3 " << "\"" << src.key3 << "\"";
  out << ":)";
  return out;
}

bool operator<(const Data& left, const Data& right)
{
  if (left.key1 == right.key1)
  {
    if (left.key2 == right.key2)
      return left.key3 < right.key3;
    else
      return left.key2 < right.key2;
  }
  else
    return left.key1 < right.key1;
}
