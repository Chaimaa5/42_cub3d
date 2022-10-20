#include "Point.hpp"

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(float x, float y)
{
    this->x = x;
    this->y = y;
}

Point::Point(Point const & P)
{
    (*this) = P;
}

Point & Point::operator=(Point const & P)
{

}

Point::~Point(){}
