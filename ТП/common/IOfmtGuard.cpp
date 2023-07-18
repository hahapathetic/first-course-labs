#include "IOfmtGuard.h"

iofmtguard::iofmtguard(std::basic_ios< char >& s) :
  s_(s),
  ws_(*(static_cast<std::basic_ios<wchar_t>*>(nullptr))),
  fill_(s.fill()),
  wfill_(L'\0'),
  fmt_(s.flags()),
  wfmt_(std::ios_base::fmtflags(0))
{}

iofmtguard::iofmtguard(std::basic_ios< wchar_t >& s) :
  s_(*(static_cast<std::basic_ios<char>*>(nullptr))),
  ws_(s),
  fill_('\0'),
  wfill_(s.fill()),
  fmt_(std::ios_base::fmtflags(0)),
  wfmt_(s.flags())
{}

iofmtguard::~iofmtguard()
{
  if (&ws_ != static_cast<std::basic_ios<wchar_t>*>(nullptr))
  {
    ws_.fill(wfill_);
    ws_.flags(wfmt_);
  }
  else
  {
    s_.fill(fill_);
    s_.flags(fmt_);
  }
}
