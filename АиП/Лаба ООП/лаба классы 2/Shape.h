#ifndef SHAPE_H
#define SHAPE_H
#include "base-types.h"
#include <string>
#include <iostream>

class Shape
{
public:
	virtual ~Shape() = default;

	virtual double getArea() const = 0;

	virtual Rectangle_t getFrameRect() const = 0;

	virtual void move(const Point_t& point) = 0;

	virtual void move(double x, double y) = 0;

	virtual void scale(double k) = 0;

	virtual void scale(double x, double y, double k) = 0;

	virtual std::string getName() const = 0;

	virtual Shape* clone() const = 0;

	friend std::ostream& operator<< (std::ostream& out, Shape& shape);

};
#endif //SHAPE_H

