#include "Circle.h"

double Circle::getArea() const
{
	return M_PI * pow(radius_,2);
}

Rectangle_t Circle::getFrameRect() const
{
	return rectangle_;
}

void Circle::move(const Point_t& point)
{
	center_ = point;
}

void Circle::move(double x, double y)
{
	center_.x_ += x;
	center_.y_ += y;
	rectangle_.pos_.x_ += x;
	rectangle_.pos_.y_ += y;
}

void Circle::scale(double k)
{
	if (k <= 0)
	{
		throw std::invalid_argument("Коэффициент масшатабирования должен быть больше нуля!\n");
	}
	else
	{
		radius_ = radius_ * k;

		rectangle_.height_ = rectangle_.height_ * (k - 1);
		rectangle_.width_ = rectangle_.width_ * (k - 1);
	}
}

std::string Circle::getName() const
{
	return "CIRCLE";
}

Shape* Circle::clone() const
{
	return new Circle(center_, radius_);
}

void Circle::scale(double x, double y, double k)
{
	if (k <= 0) {
		throw std::invalid_argument("Коэффициент масшатабирования должен быть больше нуля!\n");
	}
	else
	{
		Point_t a1 = { rectangle_.pos_.x_ - radius_, rectangle_.pos_.y_ - radius_ };
		this->move({ x, y });
		Point_t a2 = { rectangle_.pos_.x_ - radius_, rectangle_.pos_.y_ - radius_ };
		double diffX = a2.x_ - a1.x_;
		double diffY = a2.y_ - a1.y_;
		this->scale(k);
		double deltaX = diffX * k;
		double deltaY = diffY * k;
		this->move(deltaX, deltaY);
	}
}
