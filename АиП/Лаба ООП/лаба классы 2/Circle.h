#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Circle : public Shape
{
public:
	Circle(Point_t center, double radius) :
		center_(center),
		radius_(radius),
		rectangle_(radius * 2.0, radius * 2.0, center)
	{
		if (radius_ <= 0)
		{
			throw std::invalid_argument("Неправильно задан радиус!\n");
		}
	}

	double getArea() const override;
	
	Rectangle_t getFrameRect() const override;

	void move(const Point_t& point) override;

	void move(double x, double y) override;

	void scale(double k) override;

	void scale(double x, double y, double k) override;

	std::string getName() const override;

	Shape* clone() const override;
	
private:
	Point_t center_;
	double radius_;
	Rectangle_t rectangle_;
};
#endif // !CIRCLE
