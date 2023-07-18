#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

class CompositeShape : public Shape
{
public:
	CompositeShape(int maxSize): 
		maxSize_(maxSize),
		realSize_(0),
		shapes_(new Shape* [maxSize])
	{
		if (maxSize <= 0) {
			throw std::invalid_argument("Число фигур должно быть больше чем 0");
		}
	}

	CompositeShape(const CompositeShape& other):
		maxSize_(other.maxSize_),
		realSize_(other.realSize_),
		shapes_(new Shape* [other.maxSize_])
	{
		
		for (int i = 0; i < other.realSize_; i++)
		{
			shapes_[i] = *(new Shape * (other.shapes_[i]->clone()));
		}
	}
	CompositeShape(CompositeShape&& other) noexcept :
		maxSize_(other.maxSize_),
		realSize_(other.realSize_),
		shapes_(other.shapes_)
	{
		other.shapes_ = nullptr;
		other.maxSize_ = 0;
		other.realSize_ = 0;
	}

	~CompositeShape() override
	{
		if (shapes_ != nullptr)
		{
			for (int i = 0; i < realSize_; i++) {
				delete shapes_[i];
			}
			delete[] shapes_;
		}
	}

	double getArea() const override;

	Rectangle_t getFrameRect() const override;

	void move(const Point_t& point) override;

	void move(double x, double y) override;

	void scale(double k) override;

	void scale(double x, double y, double k) override;

	void add(Shape* shape);

	std::string getName() const override;

	Shape* clone() const override;

	CompositeShape& operator=(const CompositeShape& other);

	CompositeShape& operator=(CompositeShape&& other) noexcept;

private:
	int maxSize_;
	int realSize_;
	Shape** shapes_;
};
#endif //COMPOSITESHAPE_H
