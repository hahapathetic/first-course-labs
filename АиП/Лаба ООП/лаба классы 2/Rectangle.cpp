#include "Rectangle.h"

double Rectangle::getArea() const
{
	return rectangle_.height_ * rectangle_.width_;
}

Rectangle_t Rectangle::getFrameRect() const
{
	return rectangle_;
}

void Rectangle::move(const Point_t& point)
{
	rectangle_.pos_.x_ = point.x_;
	rectangle_.pos_.y_ = point.y_; // смещение центра

	rightUpper_.x_ = point.x_ + (rectangle_.width_ / 2.0);
	rightUpper_.y_ = point.y_ + (rectangle_.height_ / 2.0); // смещение правой верхней точки

	leftLower_.x_ = point.x_ - (rectangle_.width_ / 2.0);
	leftLower_.y_ = point.y_ - (rectangle_.height_ / 2.0); // смещение левой нижней точки

}

void Rectangle::move(double x, double y)
{
	rectangle_.pos_.x_ += x;
	rectangle_.pos_.y_ += y; // смещение центра

	rightUpper_.x_ += x;
	rightUpper_.y_ += y;  // смещение правой верхней точки

	leftLower_.x_ += x;
	leftLower_.y_ += y;  // смещение левой нижней точки
}

void Rectangle::scale(double k)
{
	if (k <= 0) {
		throw std::invalid_argument("Коэффициент масшатабирования должен быть больше нуля!");
	}
	else
	{
		rightUpper_.x_ += rectangle_.width_ / 2.0 * (k - 1);
		rightUpper_.y_ += rectangle_.height_ / 2.0 * (k - 1);

		leftLower_.x_ -= rectangle_.width_ / 2.0 * (k - 1);
		leftLower_.y_ -= rectangle_.height_ / 2.0 * (k - 1);

		rectangle_.height_ *= k;
		rectangle_.width_ *= k;
	}
}

std::string Rectangle::getName() const
{
	return "RECTANGLE";
}

Shape* Rectangle::clone() const
{
	return new Rectangle(leftLower_, rightUpper_);
}

void Rectangle::scale(double x, double y, double k)
{
	if (k <= 0) {
		throw std::invalid_argument("Коэффициент масшатабирования должен быть больше нуля!");
	}
	Point_t a1 = leftLower_;
	this->move({ x, y });
	Point_t a2 = leftLower_;
	double diffX = a2.x_ - a1.x_;
	double diffY = a2.y_ - a1.y_;
	this->scale(k);
	double deltaX = diffX * k;
	double deltaY = diffY * k;
	this->move(deltaX, deltaY);
}
