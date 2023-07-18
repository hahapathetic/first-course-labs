#include "CompositeShape.h"
#include "base-types.h"


CompositeShape& CompositeShape::operator=(const CompositeShape& other) {
    if (&other == this)
    {
        return *this;
    }
    if (shapes_ != nullptr) {
        for (int i = 0; i < realSize_; i++) {
            delete shapes_[i];
        }
        delete[] shapes_;
    }

    maxSize_ = other.maxSize_;
    realSize_ = other.realSize_;
    shapes_ = new Shape * [other.maxSize_];
    for (int i = 0; i < other.realSize_; i++)
    {
        shapes_[i] = *(new Shape * (other.shapes_[i]->clone()));
    }
    return *this;
}



CompositeShape& CompositeShape::operator=(CompositeShape&& other) noexcept 
{

    if (&other == this)
        return *this;
    for (int i = 0; i < realSize_; i++)
    {
        delete shapes_[i];
    }
    delete[] shapes_;

    shapes_ = other.shapes_;
    other.shapes_ = nullptr;
    other.realSize_ = 0;
    return *this;
}
double CompositeShape::getArea() const
{
	double sum = 0;
	for (int i = 0; i < realSize_; i++)
	{
		sum += shapes_[i]->getArea();
	}
	return sum;
}

Rectangle_t CompositeShape::getFrameRect() const
{
    if (shapes_ == nullptr) {
        throw std::invalid_argument("Нет фигур в составной фигуре!");
    }
    else {
        double leftDownX = shapes_[0]->getFrameRect().pos_.x_ - (shapes_[0]->getFrameRect().width_ / 2.0);
        double leftDownY = shapes_[0]->getFrameRect().pos_.y_ - (shapes_[0]->getFrameRect().height_ / 2.0);
        double rightUpX = shapes_[0]->getFrameRect().pos_.x_ + (shapes_[0]->getFrameRect().width_ / 2.0);
        double rightUpY = shapes_[0]->getFrameRect().pos_.y_ + (shapes_[0]->getFrameRect().height_ / 2.0);
        for (int i = 0; i < realSize_; i++) {
            {
                double curLeftDownX = shapes_[i]->getFrameRect().pos_.x_ - (shapes_[i]->getFrameRect().width_ / 2.0);
                double curLeftDownY = shapes_[i]->getFrameRect().pos_.y_ - (shapes_[i]->getFrameRect().height_ / 2.0);
                double curRightUpX = shapes_[i]->getFrameRect().pos_.x_ + (shapes_[i]->getFrameRect().width_ / 2.0);
                double curRightUpY = shapes_[i]->getFrameRect().pos_.y_ + (shapes_[i]->getFrameRect().height_ / 2.0);
                if (curLeftDownX < leftDownX)
                    leftDownX = curLeftDownX;
                if (curLeftDownY < leftDownY)
                    leftDownY = curLeftDownY;
                if (curRightUpX > rightUpX)
                    rightUpX = curRightUpX;
                if (curRightUpY > rightUpY)
                    rightUpY = curRightUpY;
            }
        }
        double width = rightUpX - leftDownX;
        double height = rightUpY - leftDownY;
        return { height, width, {leftDownX + (width / 2.0), leftDownY + (height / 2.0)} };
    }
}

void CompositeShape::move(const Point_t& point)
{
    double diffX = abs(this->getFrameRect().pos_.x_ - point.x_);
    double diffY = abs(this->getFrameRect().pos_.y_ - point.y_);
    for (int i = 0; i < realSize_; i++)
    {
        double shapeX = shapes_[i]->getFrameRect().pos_.x_;
        double shapeY = shapes_[i]->getFrameRect().pos_.y_;
        shapes_[i]->move({ diffX + shapeX, diffY + shapeY });
    }
}

void CompositeShape::move(double x, double y)
{
    for (int i = 0; i < realSize_; i++)
    {
        shapes_[i]->move(x, y);
    }
}

void CompositeShape::scale(double k)
{
    double x = this->getFrameRect().pos_.x_;
    double y = this->getFrameRect().pos_.y_;
    for (int i = 0; i < realSize_; i++) {
        shapes_[i]->scale(x, y, k);
    }
}

void CompositeShape::scale(double x, double y, double k)
{
    Point_t a1 = { this->getFrameRect().pos_.x_ - this->getFrameRect().width_ / 2.0,
                  this->getFrameRect().pos_.y_ - this->getFrameRect().height_ / 2.0 };
    this->move({ x, y });
    Point_t a2 = { this->getFrameRect().pos_.x_ - this->getFrameRect().width_ / 2.0,
                  this->getFrameRect().pos_.y_ - this->getFrameRect().height_ / 2.0 };
    double diffX = a1.x_ - a2.x_;
    double diffY = a1.y_ - a2.y_;
    this->scale(k);
    double deltaX = diffX * k;
    double deltaY = diffY * k;
    this->move(deltaX, deltaY);
}

void CompositeShape::add(Shape* shape)
{
    if (shapes_ == nullptr)
    {
        throw std::invalid_argument("Нет фигур в составной фигуре!\n");
    }
     else if (realSize_ < maxSize_)
    {
        shapes_[realSize_] = shape->clone();
        realSize_++;
    }
    else
    {
        throw std::out_of_range("Составная фигура переполнена!\n");
    }
}

std::string CompositeShape::getName() const
{
    return "COMPLEX";
}

Shape* CompositeShape::clone() const {
    CompositeShape* cloned = new CompositeShape(*this);
    return cloned;
}


