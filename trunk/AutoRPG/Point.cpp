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

Point Point::operator +(Point toAdd)
{
    return Point(x + toAdd.x, y + toAdd.y);
}

Point Point::operator -(Point toSubtract)
{
    return Point(x - toSubtract.x, y - toSubtract.y);
}

Point Point::fakeFunc(int fake)
{
    return *this;
}
