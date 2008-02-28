#include "Point.h"

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(double a, double b)
{
    x = a;
    y = b;
}

Point Point::operator =(Point toEqual)
{
    x = toEqual.x;
    y = toEqual.y;
    return *this;
}

bool Point::operator ==(Point toEqual)
{
    return ((x == toEqual.x) && (y == toEqual.y));
}

bool Point::operator !=(Point toEqual)
{
    return !(toEqual == *this);
}
