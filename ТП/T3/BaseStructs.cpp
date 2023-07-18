#include "BaseStructs.h"
#include "DelimeterIO.h"
#include <iterator>
#include <algorithm>

std::istream& mamonova::operator>>(std::istream& in, mamonova::Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimeterIO('(');
  in >> point.x_;
  in >> DelimeterIO(';');
  in >> point.y_;
  in >> DelimeterIO(')');
  return in;
}

bool mamonova::operator<(const mamonova::Point& firstPoint, const mamonova::Point& secondPoint)
{
  if (firstPoint.x_ == secondPoint.x_)
  {
    return firstPoint.y_ < secondPoint.y_;
  }
  return firstPoint.x_ < secondPoint.x_;
}

bool mamonova::operator==(const mamonova::Point& left, const mamonova::Point& right)
{
  return left.x_ == right.x_ && left.y_ == right.y_;
}

std::istream& mamonova::operator>>(std::istream& in, mamonova::Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::size_t counter;
  in >> counter >> std::ws;

  mamonova::Polygon figure;

  std::copy_if(
    std::istream_iterator< mamonova::Point >(in),
    std::istream_iterator< mamonova::Point >(),
    std::back_inserter(figure.points),
    [&in](const mamonova::Point& point)
    {
      char c = in.get();
      in.putback(c);
      if (c == '\n')
      {
        in.setstate(std::ios_base::eofbit);
      }
      return point.x_ != 0.1;
    }
  );
  in.clear();
  in.ignore(256, '\n');

  if (counter != figure.points.size() || figure.points.size() < 3)
  {
    in.setstate(std::ios::failbit);
  }

  if (in)
  {
    polygon = figure;
  }

  return in;
}
