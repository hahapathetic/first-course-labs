#include "Shape.h"

std::ostream& operator<< (std::ostream& out, Shape& shape)
{
    double leftDownX = shape.getFrameRect().pos_.x_ - (shape.getFrameRect().width_ / 2);
    double leftDownY = shape.getFrameRect().pos_.y_ - (shape.getFrameRect().height_ / 2);
    double rightUpX = shape.getFrameRect().pos_.x_ + (shape.getFrameRect().width_ / 2);
    double rightUpY = shape.getFrameRect().pos_.y_ + (shape.getFrameRect().height_ / 2);
    out << shape.getName() << " " << round(shape.getArea() * 10.0) / 10.0 << " "
        << round(leftDownX * 10.0) / 10.0 << " "
        << round(leftDownY * 10.0) / 10.0 << " "
        << round(rightUpX * 10.0) / 10.0 << " "
        << round(rightUpY * 10.0) / 10.0 << std::endl;
    return out;
}

bool operator<(const Shape& sh1, const Shape& sh2)
{
    return (sh1.getArea() < sh2.getArea());
}

void shapeSort(Shape** figures, size_t size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++)
        {
            if (*figures[j] < *figures[i])
            {
                Shape* t = figures[i];
                figures[i] = figures[j];
                figures[j] = t;
            }
        }
    }
}

