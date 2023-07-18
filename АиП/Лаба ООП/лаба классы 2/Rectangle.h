#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(Point_t x, Point_t y) :
		leftLower_(x),
		rightUpper_(y),
		rectangle_(y.y_ - x.y_, y.x_ - x.x_, { (x.x_ + y.x_) / 2, (y.y_ + x.y_) / 2 })

	{
		if ((x.x_ >= y.x_) || (x.y_ >= y.y_)) {
			throw std::invalid_argument("Неправильные координаты!\n");
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
	Point_t leftLower_;
	Point_t rightUpper_;
	Rectangle_t rectangle_;

};

#endif // RECTANGLE_H
