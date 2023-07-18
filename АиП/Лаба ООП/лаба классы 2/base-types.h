#ifndef BASE_TYPES_H
#define BASE_TYPES_H
struct Point_t
{
	Point_t(double x, double y) :
		x_(x),
		y_(y)
	{}
	double x_;
	double y_;
};

struct Rectangle_t
{
	Rectangle_t(double height, double width, Point_t pos) :
		height_(height),
		width_(width),
		pos_(pos)
	{}
	double height_;
	double width_;
	Point_t pos_;
};
#endif // BASE_TYPES_H