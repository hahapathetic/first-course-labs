#ifndef IOFMTGUARD_H
#define IOFMTGUARD_H
#include <ios>

class iofmtguard
{
public:
  iofmtguard(std::basic_ios< char >& s);
  iofmtguard(std::basic_ios< wchar_t >& s);
  ~iofmtguard();
private:
  std::basic_ios< char >& s_;
  std::basic_ios< wchar_t >& ws_;
  char fill_;
  wchar_t wfill_;
  std::basic_ios< char >::fmtflags fmt_;
  std::basic_ios< wchar_t >::fmtflags wfmt_;
};

#endif
